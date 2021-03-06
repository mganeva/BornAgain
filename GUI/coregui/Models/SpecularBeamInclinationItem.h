// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularBeamInclinationItem.h
//! @brief     Declares the class SpecularBeamInclinationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARBEAMINCLINATIONITEM_H
#define SPECULARBEAMINCLINATIONITEM_H

#include "BeamDistributionItem.h"

//! BeamInclinationAxisItem contains inclination angle axis for specular/off-specular
//! simulations and also provides distribution functionality.
//! Considering distribution, differs from BeamInclinationAngleItem
//! by any distribution mean value being always zero.

class BA_CORE_API_ SpecularBeamInclinationItem : public BeamDistributionItem
{
public:
    static const QString P_ALPHA_AXIS;

    SpecularBeamInclinationItem();
    ~SpecularBeamInclinationItem() override;

    double scaleFactor() const override;

    void updateFileName(const QString& filename);

private:
    void setupAxisGroup();
    static const bool m_show_mean = false;
};

#endif // SPECULARBEAMINCLINATIONITEM_H
