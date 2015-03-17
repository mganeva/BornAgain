// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/ParameterDistribution.cpp
//! @brief     Implements class ParameterDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterDistribution.h"

#include "Exceptions.h"
#include "Distributions.h"


ParameterDistribution::ParameterDistribution(const std::string &par_name,
    const IDistribution1D &distribution, size_t nbr_samples,
    double sigma_factor, const AttLimits &limits)
    : IParameterized("ParameterDistribution")
    , m_name(par_name)
    , m_nbr_samples(nbr_samples)
    , m_sigma_factor(sigma_factor)
    , m_limits(limits)
{
    mP_distribution.reset(distribution.clone());
    if (m_sigma_factor < 0.0) {
        throw Exceptions::RuntimeErrorException(
                "ParameterDistribution::setDistribution: "
                "sigma factor cannot be negative");
    }
    init_parameters();
}

ParameterDistribution::ParameterDistribution(const ParameterDistribution& other)
: IParameterized("ParameterDistribution")
    , m_name(other.m_name)
    , m_nbr_samples(other.m_nbr_samples)
    , m_sigma_factor(other.m_sigma_factor)
    , m_linked_par_names(other.m_linked_par_names)
    , m_limits(other.m_limits)
{
    mP_distribution.reset(other.mP_distribution->clone());
    init_parameters();
}

ParameterDistribution::~ParameterDistribution()
{
}

ParameterDistribution& ParameterDistribution::operator=(
        const ParameterDistribution& other)
{
    if (this != &other) {
        this->m_name = other.m_name;
        m_nbr_samples = other.m_nbr_samples;
        m_sigma_factor = other.m_sigma_factor;
        mP_distribution.reset(other.mP_distribution->clone());
        m_linked_par_names = other.m_linked_par_names;
        m_limits = other.m_limits;
        init_parameters();
    }
    return *this;
}

ParameterDistribution &ParameterDistribution::linkParameter(std::string par_name)
{
    m_linked_par_names.push_back(par_name);
    return *this;
}

std::vector<ParameterSample> ParameterDistribution::generateSamples() const
{
    return mP_distribution->generateSamples(m_nbr_samples, m_sigma_factor, m_limits);
}

void ParameterDistribution::init_parameters()
{
    clearParameterPool();
//    registerParameter("sigma_factor", &m_sigma_factor);
}
