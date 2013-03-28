// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Bin.h"
#include "Crystal.h"
#include "DiffuseParticleInfo.h"
#include "FTDistributions.h"
#include "FormFactorBox.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorParallelepiped.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Instrument.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "Lattice2DIFParameters.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "Lattice2DIFParameters.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "ParticleDecoration.h"
#include "OutputData.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "IStochasticParameter.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Transform3D.h"
#include "Types.h"
#include "Units.h"
#include "LayerDecoratorDWBASimulation.pypp.h"

namespace bp = boost::python;

struct LayerDecoratorDWBASimulation_wrapper : LayerDecoratorDWBASimulation, bp::wrapper< LayerDecoratorDWBASimulation > {

    virtual ::LayerDecoratorDWBASimulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->LayerDecoratorDWBASimulation::clone(  );
        }
    }
    
    ::LayerDecoratorDWBASimulation * default_clone(  ) const  {
        return LayerDecoratorDWBASimulation::clone( );
    }

    virtual void init( ::Simulation const & simulation ) {
        if( bp::override func_init = this->get_override( "init" ) )
            func_init( boost::ref(simulation) );
        else{
            this->LayerDecoratorDWBASimulation::init( boost::ref(simulation) );
        }
    }
    
    void default_init( ::Simulation const & simulation ) {
        LayerDecoratorDWBASimulation::init( boost::ref(simulation) );
    }

    virtual void run(  ) {
        if( bp::override func_run = this->get_override( "run" ) )
            func_run(  );
        else{
            this->LayerDecoratorDWBASimulation::run(  );
        }
    }
    
    void default_run(  ) {
        LayerDecoratorDWBASimulation::run( );
    }

};

void register_LayerDecoratorDWBASimulation_class(){

    bp::class_< LayerDecoratorDWBASimulation_wrapper, bp::bases< LayerDWBASimulation >, boost::noncopyable >( "LayerDecoratorDWBASimulation", bp::no_init )    
        .def( 
            "clone"
            , (::LayerDecoratorDWBASimulation * ( ::LayerDecoratorDWBASimulation::* )(  ) const)(&::LayerDecoratorDWBASimulation::clone)
            , (::LayerDecoratorDWBASimulation * ( LayerDecoratorDWBASimulation_wrapper::* )(  ) const)(&LayerDecoratorDWBASimulation_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "init"
            , (void ( ::LayerDecoratorDWBASimulation::* )( ::Simulation const & ) )(&::LayerDecoratorDWBASimulation::init)
            , (void ( LayerDecoratorDWBASimulation_wrapper::* )( ::Simulation const & ) )(&LayerDecoratorDWBASimulation_wrapper::default_init)
            , ( bp::arg("simulation") ) )    
        .def( 
            "run"
            , (void ( ::LayerDecoratorDWBASimulation::* )(  ) )(&::LayerDecoratorDWBASimulation::run)
            , (void ( LayerDecoratorDWBASimulation_wrapper::* )(  ) )(&LayerDecoratorDWBASimulation_wrapper::default_run) );

}
