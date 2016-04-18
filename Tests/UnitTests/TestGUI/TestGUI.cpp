#include <QtTest>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include "TestMapperCases.h"
#include "TestPropertyAttributes.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItem.h"
#include "TestLayerRoughnessItems.h"
#include "TestParaCrystalItems.h"
#include "TestSessionModel.h"
#include "TestSessionItem.h"
#include "TestGUICoreObjectCorrespondence.h"
#include "TestMapperForItem.h"
#include "TestParticleDistributionItem.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

////    TestPropertyAttributes testPropertyAttributes;
    TestFormFactorItems testFormFactorItems;
    TestFTDistributionItems testFTDistributionItems;
    TestParameterizedItem testParameterizedItem;
    TestParticleItem testParticleItem;
    TestLayerRoughnessItems testLayerRoughnessItems;
    TestParaCrystalItems testParaCrystalItems;
    TestSessionModel testSessionModel;
    TestGUICoreObjectCorrespondence testGUICoreObjectCorrespondence;
    TestSessionItem testSessionItem;
    TestMapperCases testMapperCases;
    TestMapperForItem testMapperForItem;
    TestParticleDistributionItem testParticleDistributionItem;

    bool status(false);

    status |= QTest::qExec(&testFormFactorItems, argc, argv);
    status |= QTest::qExec(&testFTDistributionItems, argc, argv);
    status |= QTest::qExec(&testParameterizedItem, argc, argv);
    status |= QTest::qExec(&testParticleItem, argc, argv);
    status |= QTest::qExec(&testLayerRoughnessItems, argc, argv);
    status |= QTest::qExec(&testParaCrystalItems, argc, argv);
    status |= QTest::qExec(&testSessionModel, argc, argv);
    status |= QTest::qExec(&testGUICoreObjectCorrespondence, argc, argv);
    status |= QTest::qExec(&testSessionItem);
    //status |= QTest::qExec(&testPropertyAttributes, argc, argv);
    status |= QTest::qExec(&testMapperCases, argc, argv);
    status |= QTest::qExec(&testSessionModel, argc, argv);
    status |= QTest::qExec(&testMapperForItem, argc, argv);
    status |= QTest::qExec(&testParticleDistributionItem, argc, argv);


    return status;
}
