// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCompositionItem.cpp
//! @brief     Implements class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleCompositionItem.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
#include "ModelPath.h"
#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "Particle.h"
#include "TransformToDomain.h"
#include "ParticleCoreShell.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";

const QString position_tooltip =
    "Relative position of the particle's reference point \n"
    "in the coordinate system of the parent (nm)";
}

const QString ParticleCompositionItem::T_PARTICLES = "Particle Tag";

// TODO make ParticleCoreShellItem and ParticleItem to derive from common base.

ParticleCompositionItem::ParticleCompositionItem()
    : SessionGraphicsItem(Constants::ParticleCompositionType)
{
    setToolTip(QStringLiteral("Composition of particles with fixed positions"));

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3).setToolTip(abundance_tooltip);

    addGroupProperty(ParticleItem::P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_PARTICLES, 0, -1, QStringList() << Constants::ParticleType
                                                  << Constants::ParticleCoreShellType
                                                  << Constants::ParticleCompositionType
                                                  << Constants::MesoCrystalType);
    setDefaultTag(T_PARTICLES);
    registerTag(ParticleItem::T_TRANSFORMATION, 0, 1,
                QStringList() << Constants::RotationType);

    addTranslator(VectorParameterTranslator(ParticleItem::P_POSITION, BornAgain::Position));
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange(
                [this](SessionItem *parent) {
        if (parent && parent->modelType() != Constants::ParticleLayoutType) {
            setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        } else {
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        }
    });
}

std::unique_ptr<ParticleComposition> ParticleCompositionItem::createParticleComposition() const
{
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    auto P_composition = std::make_unique<ParticleComposition>();
    P_composition->setAbundance(abundance);
    QVector<SessionItem *> childlist = children();
    for (int i = 0; i < childlist.size(); ++i) {
        if (childlist[i]->modelType() == Constants::ParticleType) {
            auto *particle_item = static_cast<ParticleItem*>(childlist[i]);
            auto P_particle = particle_item->createParticle();
            if (P_particle) {
                P_composition->addParticle(*P_particle);
            }
        } else if (childlist[i]->modelType() == Constants::ParticleCoreShellType) {
            auto *particle_coreshell_item = static_cast<ParticleCoreShellItem*>(childlist[i]);
            auto P_particle_coreshell = particle_coreshell_item->createParticleCoreShell();
            if (P_particle_coreshell) {
                P_composition->addParticle(*P_particle_coreshell);
            }
        } else if (childlist[i]->modelType() == Constants::ParticleCompositionType) {
            auto *particlecomposition_item = static_cast<ParticleCompositionItem*>(childlist[i]);
            auto P_child_composition = particlecomposition_item->createParticleComposition();
            if (P_child_composition) {
                P_composition->addParticle(*P_child_composition);
            }
        } else if (childlist[i]->modelType() == Constants::MesoCrystalType) {
            auto *mesocrystal_item = static_cast<MesoCrystalItem*>(childlist[i]);
            auto P_child_meso = mesocrystal_item->createMesoCrystal();
            if (P_child_meso) {
                P_composition->addParticle(*P_child_meso);
            }
        }
    }
    TransformToDomain::setTransformationInfo(P_composition.get(), *this);

    return P_composition;
}
