// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItemController.cpp
//! @brief     Implements class GroupItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupItemController.h"
#include "ItemFactory.h"
#include "ComboProperty.h"

GroupItemController::GroupItemController(SessionItem* groupItem, GroupInfo groupInfo)
    : m_groupItem(groupItem)
    , m_groupInfo(groupInfo)
{
    m_current_type = m_groupInfo.defaultType();
    m_groupItem->insertItem(-1, createCorrespondingItem());
}

SessionItem* GroupItemController::currentItem()
{
    return m_groupItem ? m_groupItem->getChildOfType(currentType()) : nullptr;
}

QString GroupItemController::currentType() const
{
    return m_current_type;
}

void GroupItemController::setCurrentType(const QString& type)
{
    if (type == currentType())
        return;

    auto prevItem = currentItem();
    m_current_type = type;

    if (m_groupItem) {
        if (auto item = m_groupItem->getChildOfType(m_current_type)) {
            item->setVisible(true);
            item->setEnabled(true);
        } else {
            m_groupItem->insertItem(-1, createCorrespondingItem());
        }
        if (prevItem) {
            prevItem->setVisible(false);
            prevItem->setEnabled(false);
        }
    }
}

//! Returns item of give type. If it doesn't exist, it will be created.
//! Method do _not_ change current item.

SessionItem* GroupItemController::getItemOfType(const QString& type)
{
    if (m_groupItem) {
        if (auto item = m_groupItem->getChildOfType(type)) {
            return item;
        } else {
            SessionItem* new_item = addItem(type);
            if (type != currentType()) {
                new_item->setVisible(false);
                new_item->setEnabled(false);
            }
            m_groupItem->insertItem(-1, new_item);
            return new_item;
        }
    }
    return nullptr;
}

int GroupItemController::currentIndex() const
{
    return toIndex(m_current_type);
}

void GroupItemController::setCurrentIndex(int index)
{
    setCurrentType(toString(index));
}

QString GroupItemController::currentLabel() const
{
    return itemLabels().at(currentIndex());
}

QStringList GroupItemController::itemTypes() const
{
    return m_groupInfo.itemTypes();
}

QStringList GroupItemController::itemLabels() const
{
    return m_groupInfo.itemLabels();
}

QVariant GroupItemController::createCombo() const
{
    ComboProperty result;
    result.setValues(itemLabels());
    result.setCurrentIndex(currentIndex());
    return result.variant();
}

SessionItem* GroupItemController::addItem(const QString& item_type)
{
    return ItemFactory::createItem(item_type);
}

SessionItem* GroupItemController::createCorrespondingItem()
{
    return addItem(currentType());
}

int GroupItemController::toIndex(const QString& type) const
{
    return itemTypes().indexOf(type);
}

QString GroupItemController::toString(int index) const
{
    return itemTypes().at(index);
}