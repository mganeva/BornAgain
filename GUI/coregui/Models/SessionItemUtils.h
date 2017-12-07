// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemUtils.h
//! @brief     Defines namespace SessionItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke, Dmitry Yurov
//
// ************************************************************************** //

#ifndef SESSIONITEMUTILS_H
#define SESSIONITEMUTILS_H

#include "Vectors3D.h"
#include "WinDllMacros.h"
#include <QString>
#include <QVariant>

class SessionItem;
class GroupInfo;

namespace SessionItemUtils
{
//! Returns the index of the given item within its parent. Returns -1 when no parent is set.
BA_CORE_API_ int ParentRow(const SessionItem& item);

//! Returns a VectorType group property's value as a kvector_t.
BA_CORE_API_ kvector_t GetVectorItem(const SessionItem& item, const QString& name);

//! Returns a VectorType group property's value as a kvector_t.
BA_CORE_API_ void SetVectorItem(const SessionItem& item, const QString& name, kvector_t value);

//! Returns the row of the given item within its parent not accounting for all hidden items
//! above. Returns -1 when no parent set or item is hidden.
BA_CORE_API_ int ParentVisibleRow(const SessionItem& item);

//! Returns text color for given item.
BA_CORE_API_ QVariant TextColorRole(const SessionItem& item);

//! Returns tooltip for given item.
BA_CORE_API_ QVariant ToolTipRole(const SessionItem& item, int ncol=0);

//! Returns tooltip for given item.
BA_CORE_API_ QVariant DecorationRole(const SessionItem& item);

//! Returns check state for given item.
BA_CORE_API_ QVariant CheckStateRole(const SessionItem& item);

//! Returns true if there is registered group.
BA_CORE_API_ bool IsValidGroup(const QString& group_type);

//! Returns GroupInfo for group property construction
BA_CORE_API_ GroupInfo GetGroupInfo(const QString& group_type);

}  // namespace SessionItemUtils

#endif // SESSIONITEMUTILS_H
