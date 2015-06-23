// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.cpp
//! @brief     Implements class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdvancedFunctionalTest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "Exceptions.h"
#include "FunctionalTestComponentService.h"
#include "IComponentService.h"
#include "Utils.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include <boost/scoped_ptr.hpp>
#include <iostream>

namespace {

std::map<IAdvancedFunctionalTest::ETestResult, std::string>  InitTestResultToString() {
    std::map<IAdvancedFunctionalTest::ETestResult, std::string> result;
    result[IAdvancedFunctionalTest::SUCCESS] = "[SUCCESS]";
    result[IAdvancedFunctionalTest::FAILED_DIFF] = "[FAILED_DIFF]";
    result[IAdvancedFunctionalTest::FAILED_NOREF] = "[FAILED_NOREF]";
    result[IAdvancedFunctionalTest::FAILED] = "[FAILED]";
    return result;
}

}

std::map<IAdvancedFunctionalTest::ETestResult, std::string> IAdvancedFunctionalTest::m_result_to_string = InitTestResultToString();

IAdvancedFunctionalTest::IAdvancedFunctionalTest(const std::string &name, const std::string &description)
    : m_name(name)
    , m_description(description)
    , m_difference(0.0)
    , m_result(SUCCESS)
{

}

void IAdvancedFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr <<  Utils::AdjustStringLength(getName(), 20);
    if(getDescription().size()) ostr <<  Utils::AdjustStringLength(getDescription(), 40);
    ostr << Utils::AdjustStringLength(getTestResultString(), 15);
    ostr << "\n";
}


// -------------------------------------------------------------------------------------------------


AdvancedFunctionalTest::AdvancedFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *simulation, OutputData<double> *reference, double threshold)
    : IAdvancedFunctionalTest(name, description)
    , m_simulation(simulation)
    , m_reference(reference)
    , m_threshold(threshold)
{

}

AdvancedFunctionalTest::~AdvancedFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void AdvancedFunctionalTest::runTest()
{
    if(!m_simulation) {
        throw NullPointerException("AdvancedFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }
    m_simulation->runSimulation();
}

int AdvancedFunctionalTest::analyseResults()
{
    if(!m_reference)  {
        m_result = FAILED_NOREF;
    } else {
        m_difference = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(), *m_reference);
        m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    }

    //printResults(std::cout);

    return m_result;
}

const OutputData<double> *AdvancedFunctionalTest::getOutputData() const
{
    if(m_simulation) {
        return m_simulation->getOutputData();
    }
    return 0;
}


// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

AdvancedFunctionalMultiTest::AdvancedFunctionalMultiTest(const std::string &name, const std::string &description, FunctionalTestComponentService *service)
    : IAdvancedFunctionalTest(name, description)
    , m_componentService(service)
{

}

AdvancedFunctionalMultiTest::~AdvancedFunctionalMultiTest()
{
    delete m_componentService;
    for(std::vector<AdvancedFunctionalTest *>::iterator it=m_tests.begin(); it!=m_tests.end(); ++it) {
        delete (*it);
    }
}

void AdvancedFunctionalMultiTest::runTest()
{
    for(size_t i=0; i<m_componentService->getNumberOfComponents(); ++i) {
        std::cout << "AdvancedFunctionalMultiTest::runTest() -> " << i<< " " << m_name << std::endl;
        m_componentService->setComponent(i);

        AdvancedFunctionalTest *test = new AdvancedFunctionalTest(
            m_componentService->getCurrentComponentName(), std::string(), m_componentService->getSimulation(), m_componentService->getReferenceData(),
            m_componentService->getThreshold());

        m_test_to_reference_fname[test] = m_componentService->getReferenceFileName();

        test->runTest();
        test->analyseResults();

        m_tests.push_back(test);

        std::cout << "AAA " << m_componentService->getReferenceFileName() << std::endl;
    }
}

int AdvancedFunctionalMultiTest::analyseResults()
{
    for(size_t i=0; i<m_tests.size(); ++i)
        if(m_tests[i]->getTestResult() != SUCCESS) m_result = FAILED;

    printResults(std::cout);

    if(getTestResult() != SUCCESS)
        saveReferenceDataForFailedTests();

    return m_result;
}

void AdvancedFunctionalMultiTest::printResults(std::ostream &ostr) const
{
    int number_of_failed_tests(0);
    for(size_t i=0; i<m_tests.size(); ++i) {
        if(m_tests[i]->getTestResult() != SUCCESS) ++number_of_failed_tests;
    }

    ostr <<  Utils::AdjustStringLength(getName(), 20);
    if(getDescription().size()) ostr <<  Utils::AdjustStringLength(getDescription(), 40);
    ostr << Utils::AdjustStringLength(getTestResultString(), 15);
    ostr << " [" << number_of_failed_tests << " failed out of " << m_tests.size() << "]";
    ostr << "\n";

    for(size_t i=0; i<m_tests.size(); ++i) {
        ostr << Utils::AdjustStringLength(std::string(), 20)
             << Utils::AdjustStringLength(m_tests[i]->getName(), 40)
             << Utils::AdjustStringLength(m_tests[i]->getTestResultString(), 15)
             << m_tests[i]->getDifference()
             << "\n";
    }

}

void AdvancedFunctionalMultiTest::saveReferenceDataForFailedTests()
{
    std::string dir_path("00_failed_tests");
    Utils::FileSystem::CreateDirectory(dir_path);

    for(size_t i=0; i<m_tests.size(); ++i) {
        AdvancedFunctionalTest *test = m_tests[i];
        if(test->getTestResult() != SUCCESS) {
            std::string file_name = Utils::FileSystem::GetFileMainName(m_test_to_reference_fname[test]);
            file_name = Utils::FileSystem::GetJoinPath(dir_path, file_name);
            IntensityDataIOFactory::writeIntensityData(*test->getOutputData(), file_name);
        }
    }

}


