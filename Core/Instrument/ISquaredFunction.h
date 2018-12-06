// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.h
//! @brief     Defines classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IVARIANCEFUNCTION_H
#define IVARIANCEFUNCTION_H

#include "WinDllMacros.h"

//! Variance function interface.
//! @ingroup fitting_internal

class BA_CORE_API_ IVarianceFunction
{
public:
    IVarianceFunction();
    virtual ~IVarianceFunction();
    virtual IVarianceFunction* clone() const = 0;
    virtual double variance(double real_value, double simulated_value) const = 0;

    IVarianceFunction(const IVarianceFunction&) = delete;
    IVarianceFunction& operator=(const IVarianceFunction&) = delete;
};

//! Returns 1.0 as variance value
//! @ingroup fitting

class BA_CORE_API_ VarianceDefaultFunction : public IVarianceFunction
{
public:
    VarianceDefaultFunction* clone() const override;
    double variance(double, double) const override;
};

//! Returns max(sim, epsilon)
//! @ingroup fitting

class BA_CORE_API_ VarianceSimFunction : public IVarianceFunction
{
public:
    explicit VarianceSimFunction(double epsilon = 1.0);
    VarianceSimFunction* clone() const override;
    double variance(double exp, double sim) const override;

private:
    double m_epsilon;
};

#endif // IVARIANCEFUNCTION_H
