// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Implements a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Beam.h"
#include "DetectorElement.h"
#include "IPixel.h"
#include "OutputData.h"
#include "SimulationArea.h"
#include "SpecularDetector1D.h"
#include "SpecularSimulationElement.h"
#include "Units.h"

SpecularDetector1D::SpecularDetector1D(const IAxis& axis)
{
    initialize();
    addAxis(axis);
}

SpecularDetector1D::SpecularDetector1D(const SpecularDetector1D& detector) : IDetector(detector)
{
    initialize();
}

SpecularDetector1D::~SpecularDetector1D() = default;

SpecularDetector1D* SpecularDetector1D::clone() const {
    return new SpecularDetector1D(*this);
}

AxesUnits SpecularDetector1D::defaultAxesUnits() const {
    return AxesUnits::RADIANS;
}

std::vector<DetectorElement> SpecularDetector1D::createDetectorElements(const Beam&)
{
    throw std::runtime_error(
        "Error in SpecularDetector1D::createDetectorElements: not implemented.");
    return std::vector<DetectorElement>();
}

std::string SpecularDetector1D::axisName(size_t index) const
{
    if (index == 0) {
        return BornAgain::U_AXIS_NAME;
    } else
        throw std::runtime_error(
            "SpecularDetector1D::getAxisName(size_t index) -> Error! index > 0");
}

void SpecularDetector1D::initialize()
{
    setName(BornAgain::SpecularDetectorType);
}
