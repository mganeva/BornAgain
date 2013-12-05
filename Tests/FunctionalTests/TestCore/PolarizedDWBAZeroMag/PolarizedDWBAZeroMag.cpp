#include "PolarizedDWBAZeroMag.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"
#include "Units.h"
#include "Types.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"

using namespace FunctionalTests;



PolarizedDWBAZeroMag::PolarizedDWBAZeroMag()
: m_name("PolarizedDWBAZeroMag")
, m_description("PolarizedDWBAZeroMag simulation")
, m_result(0)
, m_reference(0)
{ }


void PolarizedDWBAZeroMag::PolarizedDWBAZeroMag::run(const std::string &path_to_data)
{
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("PolarizedDWBAZeroMag");

    // loading reference data
    std::string filename = path_to_data + "isgi_cylinder_DWBA.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();
	//OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(),
    //        "this_cylinder_DWBA_pol.ima");

    m_result = simulation->getIntensityData();
    delete simulation;
}


int PolarizedDWBAZeroMag::analyseResults()
{
    const double threshold(1e-10);

    // calculating average relative difference
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << m_name << " " << m_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}



#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    //return Utils::FileSystem::GetPathToData("../../../ReferenceData/BornAgain/", argv[0]);
    return Utils::FileSystem::GetPathToData("../../../ReferenceData/IsGISAXS/ex-3/", argv[0]);
}

int main(int argc, char **argv)
{
    FunctionalTests::PolarizedDWBAZeroMag test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif
