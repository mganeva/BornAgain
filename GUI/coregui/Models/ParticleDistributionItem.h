// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleDistributionItem.h
//! @brief     Declares class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONITEM_H
#define PARTICLEDISTRIBUTIONITEM_H

#include "SessionGraphicsItem.h" // inheriting from
#include "ParticleDistribution.h"



class BA_CORE_API_ ParticleDistributionItem : public SessionGraphicsItem
{

public:
    static const QString P_DISTRIBUTED_PARAMETER;
    static const QString P_DISTRIBUTION;
    static const QString NO_SELECTION;
    static const QString T_PARTICLES;
    explicit ParticleDistributionItem();
    virtual ~ParticleDistributionItem();

    std::unique_ptr<ParticleDistribution> createParticleDistribution() const;

public slots:
    void updateParameterList();

private:
    QStringList getChildParameterNames() const;
    QStringList extractFromParameterPool(const ParameterPool *pool) const;
};

#endif // PARTICLEDISTRIBUTIONITEM_H

