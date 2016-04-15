// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ApplicationModels.h
//! @brief     Defines class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#include "ApplicationModels.h"
#include "GUIObjectBuilder.h"
#include "DocumentModel.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "JobModel.h"
#include "FitModel.h"
#include "IconProvider.h"
#include "SampleBuilderFactory.h"

ApplicationModels::ApplicationModels(QObject *parent)
    : QObject(parent)
    , m_documentModel(0)
    , m_materialModel(0)
    , m_materialSvc(0)
    , m_instrumentModel(0)
    , m_sampleModel(0)
    , m_jobModel(0)
    , m_fitModel(0)
{
    createModels();
    testGUIObjectBuilder();
}

ApplicationModels::~ApplicationModels()
{
    delete m_materialSvc;
}

DocumentModel *ApplicationModels::documentModel()
{
    return m_documentModel;
}

MaterialModel *ApplicationModels::materialModel()
{
    return m_materialModel;
}

InstrumentModel *ApplicationModels::instrumentModel()
{
    return m_instrumentModel;
}

SampleModel *ApplicationModels::sampleModel()
{
    return m_sampleModel;
}

JobModel *ApplicationModels::jobModel()
{
    return m_jobModel;
}

FitModel *ApplicationModels::fitModel()
{
    return m_fitModel;
}

//! reset all models to initial state
void ApplicationModels::resetModels()
{
    m_documentModel->clear();
    m_documentModel->insertNewItem(Constants::SimulationOptionsType);

    m_materialModel->clear();
    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addMaterial("Air", 0.0, 0.0);
    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    SessionItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));

    /*m_fitModel->clear();
    m_fitModel->insertNewItem(Constants::FitParameterContainerType, QModelIndex());
    SessionItem *selection = m_fitModel->insertNewItem(Constants::FitSelectionType, QModelIndex());
    selection->setRegisteredProperty(FitSelectionItem::P_SAMPLE, "MultiLayer");
    selection->setRegisteredProperty(FitSelectionItem::P_INSTRUMENT, "Instrument0");
    m_fitModel->insertNewItem(Constants::MinimizerSettingsType, QModelIndex());
    m_fitModel->insertNewItem(Constants::InputDataType, QModelIndex());*/

}

//! creates and initializes models, order is important
void ApplicationModels::createModels()
{
    createDocumentModel();

    createMaterialModel();

    createSampleModel();

    createInstrumentModel();

    createJobModel();

    //createFitModel();

    resetModels();
}

void ApplicationModels::createDocumentModel()
{
    delete m_documentModel;
    m_documentModel = new DocumentModel(this);
    connectModel(m_documentModel);
}

void ApplicationModels::createMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
    connectModel(m_materialModel);
    m_materialSvc = new MaterialSvc(m_materialModel);
}

void ApplicationModels::createSampleModel()
{
    Q_ASSERT(m_materialModel);
    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);
    connectModel(m_sampleModel);
    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_sampleModel, SLOT(onMaterialModelChanged(QModelIndex,QModelIndex)));
}

void ApplicationModels::createJobModel()
{
    delete m_jobModel;
    m_jobModel = new JobModel(this);
    connectModel(m_jobModel);
}

void ApplicationModels::createInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    connectModel(m_instrumentModel);
    m_instrumentModel->setIconProvider(new IconProvider());
}

void ApplicationModels::createFitModel()
{
    delete m_fitModel;
    m_fitModel = new FitModel(m_sampleModel, m_instrumentModel, this);
    connectModel(m_fitModel);
}

void ApplicationModels::testGUIObjectBuilder()
{
    SampleBuilderFactory factory;
    const std::unique_ptr<ISample> P_sample(factory.createSample("CylindersAndPrismsBuilder"));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sampleModel, *P_sample);

//    SimulationRegistry simRegistry;
//    const std::unique_ptr<GISASSimulation> simulation(simRegistry.createSimulation("RectDetectorPerpToReflectedBeamDpos"));
//    guiBuilder.populateInstrumentModel(m_instrumentModel, *simulation);
}

void ApplicationModels::disconnectModel(SessionModel *model)
{
    if(model) {
        disconnect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SIGNAL(modelChanged()));
        disconnect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SIGNAL(modelChanged()));
        disconnect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SIGNAL(modelChanged()));
    }
}

void ApplicationModels::connectModel(SessionModel *model)
{
    if(model) {
        connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
        connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
        connect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
    }
}
