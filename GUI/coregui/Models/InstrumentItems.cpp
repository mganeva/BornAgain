// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItems.cpp
//! @brief     Implements InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentItems.h"
#include "BackgroundItems.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "SessionModel.h"
#include "GroupItem.h"
#include "MaskItems.h"
#include "ParameterTranslators.h"
#include "Instrument.h"
#include "IDetector2D.h"
#include "AxesItems.h"

namespace {
const QString background_group_label = "Type";
}

const QString InstrumentItem::P_IDENTIFIER = "Identifier";

InstrumentItem::InstrumentItem(const QString& modelType) : SessionItem(modelType)
{
    setItemName(modelType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

}

const QString Instrument2DItem::P_BEAM = "Beam";
const QString Instrument2DItem::P_DETECTOR = "Detector";
const QString Instrument2DItem::P_BACKGROUND = "Background";

Instrument2DItem::Instrument2DItem(const QString& modelType)
    : InstrumentItem(modelType)
{
    addGroupProperty(P_BEAM, Constants::BeamType);

    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);

    auto item = addGroupProperty(P_BACKGROUND, Constants::BackgroundGroup);
    item->setDisplayName(background_group_label);
    item->setToolTip("Background type");
}

Instrument2DItem::~Instrument2DItem() = default;

BeamItem *Instrument2DItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

DetectorItem* Instrument2DItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* Instrument2DItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

BackgroundItem* Instrument2DItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* Instrument2DItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
}

void Instrument2DItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void Instrument2DItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void Instrument2DItem::importMasks(MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}

QStringList Instrument2DItem::translateList(const QStringList& list) const
{
    QStringList result;
    // Add constant background directly to simulation
    if (list.back().startsWith(P_BACKGROUND) && list.size()==2) {
        result << list[0] << QString::fromStdString(BornAgain::ConstantBackgroundType);
    } else {
        // TODO Consider usage of ModelTypeTranslator in IntrusmentItem's constructor
        // after the refactoring of SessionItem::translateList
        result = SessionItem::translateList(list);
        if (result.back() == Constants::GISASInstrumentType) {
            result.removeLast();
            result << QStringLiteral("Instrument");
        }
    }
    return result;
}

std::unique_ptr<Instrument> Instrument2DItem::createInstrument() const
{
    std::unique_ptr<Instrument> result(new Instrument);

    auto beam = beamItem()->createBeam();
    result->setBeam(*beam);

    auto detector = detectorItem()->createDetector();
    result->setDetector(*detector);

    return result;
}

GISASInstrumentItem::GISASInstrumentItem()
    : Instrument2DItem(Constants::GISASInstrumentType)
{
}

const QString OffSpecInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

OffSpecInstrumentItem::OffSpecInstrumentItem()
    : Instrument2DItem(Constants::OffSpecInstrumentType)
{
    auto item = addGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    item->setToolTip("Incoming alpha range [deg]");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value [deg]");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value [deg]");

    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 10.0);
}
