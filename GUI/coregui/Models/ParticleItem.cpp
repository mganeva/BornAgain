// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "BornAgainNamespace.h"
#include "FormFactorItems.h"
#include "MaterialItemUtils.h"
#include "ModelPath.h"
#include "Particle.h"
#include "ParticleCoreShellItem.h"
#include "SessionItemUtils.h"
#include "TransformToDomain.h"
#include "VectorItem.h"

using SessionItemUtils::SetVectorItem;

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";

const QString position_tooltip =
    "Relative position of the particle's reference point \n"
    "in the coordinate system of the parent (nm)";
}

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = QString::fromStdString(BornAgain::Abundance);
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";
const QString ParticleItem::T_TRANSFORMATION = "Transformation Tag";

ParticleItem::ParticleItem()
    : SessionGraphicsItem(Constants::ParticleType)
{
    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    addProperty(P_MATERIAL, MaterialItemUtils::defaultMaterialProperty().variant())
        ->setToolTip(QStringLiteral("Material of particle"))
        .setEditorType(Constants::MaterialEditorExternalType);

    addProperty(P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0)).setDecimals(3)
        .setToolTip(abundance_tooltip);
    addGroupProperty(P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::RotationType);
    setDefaultTag(T_TRANSFORMATION);

    addTranslator(VectorParameterTranslator(P_POSITION, BornAgain::Position));
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange([this](SessionItem* newParent) {
        updatePropertiesAppearance(newParent);
    });
}

std::unique_ptr<Particle> ParticleItem::createParticle() const
{
    auto P_material = TransformToDomain::createDomainMaterial(*this);
    auto P_particle = std::make_unique<Particle>(*P_material);

    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    P_particle->setAbundance(abundance);

    auto& ffItem = groupItem<FormFactorItem>(ParticleItem::P_FORM_FACTOR);
    P_particle->setFormFactor(*ffItem.createFormFactor());

    TransformToDomain::setTransformationInfo(P_particle.get(), *this);

    return P_particle;
}

QVector<SessionItem*> ParticleItem::materialPropertyItems()
{
    auto item = getItem(P_MATERIAL);
    if (!item)
        return {};
    return {item};
}

//! Updates enabled/disabled for particle position and particle abundance depending on context.

void ParticleItem::updatePropertiesAppearance(SessionItem* newParent)
{
    if (newParent && !parentIsParticleLayout()) {
        setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
        getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        if (isShellParticle()) {
            kvector_t zero_vector;
            SetVectorItem(*this, ParticleItem::P_POSITION, zero_vector);
            SessionItem *positionItem = getItem(ParticleItem::P_POSITION);
            positionItem->setEnabled(false);
        }
    } else {
        getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        getItem(ParticleItem::P_POSITION)->setEnabled(true);
    }
}

//! Returns true if this particle is a shell particle.

bool ParticleItem::isShellParticle() const
{
    if (!parent())
        return false;

    return parent()->modelType() == Constants::ParticleCoreShellType
            && parent()->tagFromItem(this) == ParticleCoreShellItem::T_SHELL;
}

//! Returns true if this particle is directly connected to a ParticleLayout

bool ParticleItem::parentIsParticleLayout() const
{
    if (!parent())
        return false;

    return parent()->modelType() == Constants::ParticleLayoutType;
}
