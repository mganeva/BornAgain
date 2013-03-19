// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/IResolutionFunction2D.h
//! @brief     Defines class IResolutionFunction2D.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IRESOLUTIONFUNCTION2D_H_
#define IRESOLUTIONFUNCTION2D_H_

#include "IParameterized.h"

class IResolutionFunction2D : public IParameterized
{
public:
    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const=0;
    virtual IResolutionFunction2D *clone() const = 0;
};

#endif /* IRESOLUTIONFUNCTION2D_H_ */
