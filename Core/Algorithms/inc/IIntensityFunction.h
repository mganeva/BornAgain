// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/IIntensityFunction.h 
//! @brief     Defines classes IIntensityFunction, ..Log, ..Sqrt.
//
// ************************************************************************** //

#ifndef IINTENSITYFUNCTION_H
#define IINTENSITYFUNCTION_H

#include <cmath>

class IIntensityFunction
{
public:
    virtual ~IIntensityFunction() {}
    virtual IIntensityFunction *clone() const=0;

    virtual double evaluate(double value) const=0;

};

class IntensityFunctionLog : public IIntensityFunction
{
public:
    virtual ~IntensityFunctionLog() {}
    virtual IntensityFunctionLog *clone() const { return new IntensityFunctionLog(); }
    virtual double evaluate(double value) const { return (value > 0 ? std::log(value) : 0); }
};

class IntensityFunctionSqrt : public IIntensityFunction
{
public:
    virtual ~IntensityFunctionSqrt() {}
    virtual IntensityFunctionSqrt *clone() const { return new IntensityFunctionSqrt(); }
    virtual double evaluate(double value) const { return (value > 0 ? std::sqrt(value) : 0); }
};

#endif // IINTENSITYFUNCTION_H
