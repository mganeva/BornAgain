#include "SpecularInstrumentEditor.h"
#include "SpecularBeamEditor.h"
#include "EnvironmentEditor.h"
#include "PolarizationAnalysisEditor.h"
#include "InstrumentItems.h"
#include "ColumnResizer.h"
#include "StyleUtils.h"
#include <QVBoxLayout>

SpecularInstrumentEditor::SpecularInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new SpecularBeamEditor(m_columnResizer))
    , m_environmentEditor(new EnvironmentEditor(m_columnResizer))
    , m_polarizationAnalysisEditor(nullptr)
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_beamEditor, "Beam parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_environmentEditor, "Environment",
                                                          /*expanded*/false));
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void SpecularInstrumentEditor::subscribeToItem()
{
    m_beamEditor->setItem(instrumentItem());
    m_environmentEditor->setItem(instrumentItem());
//    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

SpecularInstrumentItem* SpecularInstrumentEditor::instrumentItem()
{
    auto result = dynamic_cast<SpecularInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

