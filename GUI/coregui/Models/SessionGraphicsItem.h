// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionGraphicsItem.h
//! @brief     Defines class SessionGraphicsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SESSIONGRAPHICSITEM_H
#define SESSIONGRAPHICSITEM_H

#include "SessionItem.h"

class BA_CORE_API_ SessionGraphicsItem : public SessionItem
{

public:
    static const QString P_XPOS;
    static const QString P_YPOS;

protected:
    explicit SessionGraphicsItem(const QString &model_type=QString());
};

#endif // SESSIONGRAPHICSITEM_H
