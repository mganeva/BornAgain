// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/ConvolutionDetectorResolution.cpp
//! @brief     Implements class ConvolutionDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ConvolutionDetectorResolution.h"
#include "Convolve.h"

#include <iostream>
#include <cassert>

ConvolutionDetectorResolution::ConvolutionDetectorResolution(
        cumulative_DF_1d res_function_1d)
: m_dimension(1)
, m_res_function_1d(res_function_1d)
, mp_res_function_2d(0)
{
    setName("ConvolutionDetectorResolution");
}

ConvolutionDetectorResolution::ConvolutionDetectorResolution(
        IResolutionFunction2D *p_res_function_2d)
: m_dimension(2)
, m_res_function_1d(0)
, mp_res_function_2d(p_res_function_2d)
{
    setName("ConvolutionDetectorResolution");
}

ConvolutionDetectorResolution::ConvolutionDetectorResolution(
        const IResolutionFunction2D &p_res_function_2d)
: m_dimension(2)
, m_res_function_1d(0)
, mp_res_function_2d(p_res_function_2d.clone())
{
    setName("ConvolutionDetectorResolution");
}


ConvolutionDetectorResolution::~ConvolutionDetectorResolution()
{
    delete mp_res_function_2d;
}

ConvolutionDetectorResolution::ConvolutionDetectorResolution(const ConvolutionDetectorResolution& other) : IDetectorResolution()
//    : IDetectorResolution(other)
{
    m_dimension = other.m_dimension;
    m_res_function_1d=other.m_res_function_1d;
    mp_res_function_2d = other.mp_res_function_2d->clone();
    setName(other.getName());

}

//! clone object
ConvolutionDetectorResolution *ConvolutionDetectorResolution::clone() const
{
    return new ConvolutionDetectorResolution(*this);
}

void ConvolutionDetectorResolution::applyDetectorResolution(
        OutputData<double>* p_intensity_map) const
{
    if (p_intensity_map->getRank() != m_dimension) {
        throw RuntimeErrorException("ConvolutionDetectorResolution::applyDetectorResolution() -> Error! Intensity map must have same dimension as detector resolution function.");
    }
    switch (m_dimension) {
    case 1:
        apply1dConvolution(p_intensity_map);
        break;
    case 2:
        apply2dConvolution(p_intensity_map);
        break;
    default:
        throw LogicErrorException("ConvolutionDetectorResolution::applyDetectorResolution() -> Error! Class ConvolutionDetectorResolution must be initialized with dimension 1 or 2.");
    }
}

std::string ConvolutionDetectorResolution::addParametersToExternalPool(
        std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the 2D resolution function
    if (mp_res_function_2d) {
        mp_res_function_2d->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void ConvolutionDetectorResolution::init_parameters()
{
}

void ConvolutionDetectorResolution::apply1dConvolution(OutputData<double>* p_intensity_map) const
{
    if (m_res_function_1d==0) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply1dConvolution() -> Error! No 1d resolution function present for convolution of 1d data.");
    }
    if (p_intensity_map->getRank() != 1) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply1dConvolution() -> Error! Number of axes for intensity map does not correspond to the dimension of the map.");
    }
    const IAxis *p_axis = p_intensity_map->getAxis(0);
    // Construct source vector from original intensity map
    std::vector<double> source_vector = p_intensity_map->getRawDataVector();
    size_t data_size = source_vector.size();
    if (data_size < 2) {
        return; // No convolution for sets of zero or one element
    }
    // Construct kernel vector from resolution function
    if (p_axis->getSize() != data_size) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply1dConvolution() -> Error! Size of axis for intensity map does not correspond to the size of the data in the map.");
    }
    double step_size = std::abs((*p_axis)[0]-(*p_axis)[p_axis->getSize()-1])/(data_size-1);
    double mid_value = (*p_axis)[p_axis->getSize()/2];  // Needed because Convolve class expects zero at midpoint
    std::vector<double> kernel;
    for (size_t index=0; index<data_size; ++index) {
        kernel.push_back(getIntegratedPDF1d((*p_axis)[index] - mid_value, step_size));
    }
    // Calculate convolution
    std::vector<double> result;
    MathFunctions::Convolve cv;
    cv.fftconvolve(source_vector, kernel, result);
    // Populate intensity map with results
    p_intensity_map->setRawDataVector(result);
}

void ConvolutionDetectorResolution::apply2dConvolution(OutputData<double>* p_intensity_map) const
{
    if (mp_res_function_2d==0) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply2dConvolution() -> Error! No 2d resolution function present for convolution of 2d data.");
    }
    if (p_intensity_map->getRank() != 2) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply2dConvolution() -> Error! Number of axes for intensity map does not correspond to the dimension of the map.");
    }
    const IAxis *p_axis_1 = p_intensity_map->getAxis(0);
    const IAxis *p_axis_2 = p_intensity_map->getAxis(1);
    size_t axis_size_1 = p_axis_1->getSize();
    size_t axis_size_2 = p_axis_2->getSize();
    if (axis_size_1 < 2 || axis_size_2 < 2) {
        return; // No 2d convolution for 1d data
    }
    // Construct source vector array from original intensity map
    std::vector<double> raw_source_vector = p_intensity_map->getRawDataVector();
    std::vector<std::vector<double> > source;
    size_t raw_data_size = raw_source_vector.size();
    if (raw_data_size != axis_size_1*axis_size_2) {
        throw LogicErrorException("ConvolutionDetectorResolution::apply2dConvolution() -> Error! Intensity map data size does not match the product of its axes' sizes");
    }
    for (std::vector<double>::const_iterator it=raw_source_vector.begin(); it != raw_source_vector.end();it+=axis_size_2) {
        std::vector<double> row_vector(it, it+axis_size_2);
        source.push_back(row_vector);
    }
    // Construct kernel vector from resolution function
    std::vector<std::vector<double> > kernel;
    kernel.resize(axis_size_1);
    double mid_value_1 = (*p_axis_1)[axis_size_1/2];  // Needed because Convolve class expects zero at midpoint
    double mid_value_2 = (*p_axis_2)[axis_size_2/2];  // Needed because Convolve class expects zero at midpoint
    double step_size_1 = std::abs((*p_axis_1)[0]-(*p_axis_1)[axis_size_1-1])/(axis_size_1-1);
    double step_size_2 = std::abs((*p_axis_2)[0]-(*p_axis_2)[axis_size_2-1])/(axis_size_2-1);
    for (size_t index_1=0; index_1<axis_size_1; ++index_1) {
        double value_1 = (*p_axis_1)[index_1]-mid_value_1;
        std::vector<double> row_vector;
        row_vector.resize(axis_size_2, 0.0);
        for (size_t index_2=0; index_2<axis_size_2;++index_2) {
            double value_2 = (*p_axis_2)[index_2]-mid_value_2;
            double z_value = getIntegratedPDF2d(value_1, step_size_1, value_2, step_size_2);
            row_vector[index_2] = z_value;
        }
        kernel[index_1] = row_vector;
    }
    // Calculate convolution
    std::vector<std::vector<double> > result;
    MathFunctions::Convolve cv;
    cv.fftconvolve(source, kernel, result);
    // Populate intensity map with results
    std::vector<double> result_vector;
    for (size_t index_1=0; index_1<axis_size_1; ++index_1) {
        for (size_t index_2=0; index_2<axis_size_2;++index_2) {
            double value = result[index_1][index_2];
            result_vector.push_back(value);
        }
    }
    for(OutputData<double>::iterator it=p_intensity_map->begin(); it!=p_intensity_map->end(); ++it) {
        (*it) = result_vector[it.getIndex()];
    }
//    p_intensity_map->setRawDataVector(result_vector);
}

double ConvolutionDetectorResolution::getIntegratedPDF1d(double x,
        double step) const
{
    double halfstep = step/2.0;
    double xmin = x - halfstep;
    double xmax = x + halfstep;
    assert(m_res_function_1d != nullptr);
    return m_res_function_1d(xmax) - m_res_function_1d(xmin);
}

double ConvolutionDetectorResolution::getIntegratedPDF2d(double x,
        double step_x, double y, double step_y) const
{
    double halfstepx = step_x/2.0;
    double halfstepy = step_y/2.0;
    double xmin = x - halfstepx;
    double xmax = x + halfstepx;
    double ymin = y - halfstepy;
    double ymax = y + halfstepy;
    double result = mp_res_function_2d->evaluateCDF(xmax, ymax) - mp_res_function_2d->evaluateCDF(xmax, ymin)
            - mp_res_function_2d->evaluateCDF(xmin, ymax) + mp_res_function_2d->evaluateCDF(xmin, ymin);
    return result;
}