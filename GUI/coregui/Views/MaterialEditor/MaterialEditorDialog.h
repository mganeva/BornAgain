// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorDialog.h
//! @brief     Defines class MaterialEditorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORDIALOG_H
#define MATERIALEDITORDIALOG_H

#include <QDialog>

#include "MaterialProperty.h"
#include "WinDllMacros.h"

class MaterialModel;
class MaterialEditorWidget;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorDialog : public QDialog
{
    Q_OBJECT

public:
    MaterialEditorDialog(MaterialModel *materialModel, QWidget *parent = 0);

    MaterialProperty getSelectedMaterialProperty();

public slots:
    void onSelectButton();
    void onCancelButton();

private:
    MaterialEditorWidget *m_materialEditor;
};

#endif
