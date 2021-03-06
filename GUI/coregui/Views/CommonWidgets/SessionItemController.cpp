// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemController.h
//! @brief     Implements class SessionItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SessionItemController.h"
#include "SessionItem.h"
#include "GUIHelpers.h"

SessionItemController::SessionItemController(QObject* prt)
    : QObject(prt)
    , m_item(nullptr)
    , m_parent_subscribed(false)
{
    Q_ASSERT(parent());
}

SessionItemController::~SessionItemController()
{
    onControllerDestroy();
}

void SessionItemController::setItem(SessionItem* item)
{
    if(m_item == item)
        return;

    if (m_item) {
        m_item->mapper()->unsubscribe(this);
        unsubscribe();
    }

    m_item = item;
    if (!m_item)
        return;

    m_item->mapper()->setOnItemDestroy([this](SessionItem*) { onItemDestroy(); }, this);
}

SessionItem* SessionItemController::currentItem()
{
    return m_item;
}

void SessionItemController::setSubscribeCallback(callback_t fun)
{
    m_subscribe_callback = fun;
}

void SessionItemController::setUnsubscribeCallback(callback_t fun)
{
    m_unsubscribe_callback = fun;
}

//! Subscribe parent to item's signals.

void SessionItemController::subscribe()
{
    if (!m_item)
        return;

    if (!m_parent_subscribed)
        subscribeParent();
}

//! Fully unsubscribes the parent from listening item's signals.
//! Controller stays active to track item destruction.

void SessionItemController::unsubscribe()
{
    if (!m_item)
        return;

    if (m_parent_subscribed)
        unsubscribeParent();

    m_item->mapper()->unsubscribe(parent());
}

void SessionItemController::onItemDestroy()
{
    if (m_parent_subscribed)
        unsubscribeParent();
    m_item = nullptr;
}

void SessionItemController::onControllerDestroy()
{
    if (m_item) {
        m_item->mapper()->unsubscribe(this);
        m_item->mapper()->unsubscribe(parent());
    }
}

void SessionItemController::subscribeParent()
{
    Q_ASSERT(m_subscribe_callback);
    Q_ASSERT(m_parent_subscribed == false);
    m_subscribe_callback();
    m_parent_subscribed = true;
}

//! Calls additional callback on un

void SessionItemController::unsubscribeParent()
{
    Q_ASSERT(m_unsubscribe_callback);
    Q_ASSERT(m_parent_subscribed == true);
    m_unsubscribe_callback();
    m_parent_subscribed = false;
}



