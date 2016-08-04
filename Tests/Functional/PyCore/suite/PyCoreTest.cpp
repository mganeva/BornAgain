// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyCoreTest.cpp
//! @brief     Implements class PyCoreTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyCoreTest.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "TestConfig.h"
#include "Utils.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

PyCoreTest::PyCoreTest(
    const std::string& name, const std::string& description,
    GISASSimulation* reference_simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
    , m_pyscript_filename( BUILD_TMP_DIR + "/pysuite_" + name + ".py" )
    , m_output_filename( BUILD_TMP_DIR + "/pysuite_" + name + ".int" )
{
}

PyCoreTest::~PyCoreTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void PyCoreTest::runTest()
{
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();

    // Generate Python script
    std::ostringstream ostr;
    ostr << "# Functional test settings, generated by PyCoreTest::runTest():\n"
         << "import sys, os\n"
         << "sys.path.append('" << BUILD_LIB_DIR << "')\n\n"
         << "# Simulation script, generated by PythonFormatting::simulationToPython(..):\n"
         << PythonFormatting::simulationToPython(m_reference_simulation);
    std::ofstream pythonFile(m_pyscript_filename);
    pythonFile << ostr.str();
    pythonFile.close();

    // Run Python script
    std::remove( m_output_filename.c_str() );
    std::string command = std::string(BORNAGAIN_PYTHON_EXE) + " " + m_pyscript_filename +
        " " + m_output_filename;
    std::cout << "Core simulation will be compared with " << m_output_filename <<
        " generated by command '" << command << "'" << std::endl /* sic: flush */;
    int ret = std::system(command.c_str()); // run python script

    // Analyse results:
    if (ret!=0) {
        std::cerr << "Command '" << command << "' returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(m_output_filename));
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    if (m_result != SUCCESS) {
        // Move failed Python script to failed tests directory
        Utils::FileSystem::CreateDirectory(FAILED_TESTS_DIR);
        std::rename( m_pyscript_filename.c_str(), getPySuiteFileNameAndPath().c_str());
    }
}

void PyCoreTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
    if (m_result != SUCCESS)
        ostr << "--> " << getPySuiteFileNameAndPath();
}

std::string PyCoreTest::getPySuiteFileNameAndPath() const
{
    std::string result = Utils::FileSystem::GetJoinPath(FAILED_TESTS_DIR, m_pyscript_filename);
    return result;
}
