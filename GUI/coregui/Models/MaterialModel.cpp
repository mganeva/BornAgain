// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialModel.cpp
//! @brief     Implements class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaterialModel.h"
#include "MaterialItemUtils.h"
#include "GUIHelpers.h"
#include "MaterialDataItems.h"
#include "AppSvc.h"

MaterialModel::MaterialModel(QObject* parent) : SessionModel(SessionXML::MaterialModelTag, parent)
{
    setObjectName(SessionXML::MaterialModelTag);
    if (AppSvc::materialModel() == nullptr)
        AppSvc::subscribe(this);
}

MaterialModel::~MaterialModel()
{
    if (AppSvc::materialModel() == this)
        AppSvc::unsubscribe(this);
}

MaterialModel* MaterialModel::createCopy(SessionItem* parent)
{
    MaterialModel* result = new MaterialModel();
    result->initFrom(this, parent);
    return result;
}

MaterialItem* MaterialModel::addRefractiveMaterial(const QString& name, double delta, double beta)
{
    auto materialItem = createMaterial(name);
    materialItem->setRefractiveData(delta, beta);
    return materialItem;
}

void MaterialModel::removeMaterial(MaterialItem* item)
{
    QModelIndex materialIndex = indexOfItem(item);
    removeRows(materialIndex.row(), 1, materialIndex.parent());
}

MaterialItem* MaterialModel::getMaterial(const QModelIndex& index)
{
    return dynamic_cast<MaterialItem*>(itemForIndex(index));
}

//! Returns clone of material with given index.

MaterialItem* MaterialModel::cloneMaterial(const QModelIndex& index)
{
    const MaterialItem* origMaterial = getMaterial(index);
    if (!origMaterial)
        return nullptr;

    SessionItem* clonedMaterial = copyItem(origMaterial, 0);
    clonedMaterial->setItemValue(MaterialItem::P_IDENTIFIER, GUIHelpers::createUuid());
    clonedMaterial->setItemName(origMaterial->itemName() + " (clone)");
    return dynamic_cast<MaterialItem*>(clonedMaterial);
}

MaterialItem* MaterialModel::materialFromName(const QString& material_name)
{
    for(auto materialItem : topItems<MaterialItem>()) {
        if (materialItem->itemName() == material_name)
            return materialItem;
    }

    return nullptr;
}

MaterialItem* MaterialModel::materialFromIdentifier(const QString& identifier)
{
    for(auto materialItem : topItems<MaterialItem>()) {
        if (materialItem->getIdentifier() == identifier)
            return materialItem;
    }

    return nullptr;
}

//! Creates material with name and color. Material data remains uninitialized.

MaterialItem* MaterialModel::createMaterial(const QString& name)
{
    auto result  = dynamic_cast<MaterialItem*>(insertNewItem(Constants::MaterialType));
    result->setItemName(name);

    QColor color = MaterialItemUtils::suggestMaterialColor(name);
    result->setItemValue(MaterialItem::P_COLOR, MaterialItemUtils::colorProperty(color).variant());

    return result;
}
