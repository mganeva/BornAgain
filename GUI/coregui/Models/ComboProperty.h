// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.h
//! @brief     Declares class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMBOPROPERTY_H
#define COMBOPROPERTY_H

#include <QVariant>
#include <QStringList>

//! The ComboProperty defines SessionItem's property with a value
//! from predefined list.
//!
//! This is a light version of GroupProperty without SubItem mechanism
class BA_CORE_API_ ComboProperty
{
public:

    ComboProperty(const QStringList &values = QStringList(),
                  const QString &current_value = QString("Undefined"));
    virtual ~ComboProperty() {}
    QString getValue() const;

    void setValue(const QString &name);
    bool operator!=(const ComboProperty &other);
    bool isDefined();

    QStringList getValues() const;

    QStringList getToolTips() const;
    void setToolTips(const QStringList &tooltips);

    int index() const;
    int toIndex(const QString &value) const;
    QString toString(int index) const;

    inline ComboProperty &operator<<(const QString &str);

    inline ComboProperty &operator<<(const QStringList &str);

    QVariant getVariant() const;

    int getIndex() const;

    QString getCachedValue() const;
    void setCachedValue(const QString &name);

    bool cacheContainsGUIValue() const;
    void setCacheContainsGUIFlag(bool flag=true);

private:
    QStringList m_values;
    QStringList m_values_tooltips;
    QString m_current_value;
    QString m_cached_value;  // for comboboxes with dynamically generated value lists
    bool m_cache_contains_GUI_value;
};

inline QString ComboProperty::getValue() const
{
    return m_current_value;
}

inline bool ComboProperty::operator!=(const ComboProperty &other)
{
    return (getValue() != other.getValue());
}

inline bool ComboProperty::isDefined()
{
    return m_current_value != QStringLiteral("Undefined");
}

inline QStringList ComboProperty::getValues() const
{
    return m_values;
}

inline ComboProperty &ComboProperty::operator<<(const QString &str)
{
    m_values.append(str);
    if(m_values.size()) m_current_value=m_values.at(0);
    return *this;
}

inline ComboProperty &ComboProperty::operator<<(const QStringList &str)
{
    m_values.append(str);
    if(m_values.size()) m_current_value=m_values.at(0);
    return *this;
}

inline QVariant ComboProperty::getVariant() const {
    QVariant result;
    result.setValue(*this);
    return result;
}

inline int ComboProperty::getIndex() const
{
    return toIndex(m_current_value);
}

inline QString ComboProperty::getCachedValue() const
{
    return m_cached_value;
}

inline bool ComboProperty::cacheContainsGUIValue() const
{
    return m_cache_contains_GUI_value;
}

inline void ComboProperty::setCacheContainsGUIFlag(bool flag)
{
    m_cache_contains_GUI_value = flag;
}

Q_DECLARE_METATYPE(ComboProperty)



#endif // COMBOPROPERTY_H
