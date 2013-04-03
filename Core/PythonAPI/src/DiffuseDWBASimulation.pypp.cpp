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
#include "IResolutionFunction2D.h"
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
#include "OutputDataIOFactory.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Rotate3D.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "IStochasticParameter.h"
#include "ResolutionFunction2DSimple.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "ITransform3D.h"
#include "Types.h"
#include "Units.h"
#include "DiffuseDWBASimulation.pypp.h"

namespace bp = boost::python;

struct DiffuseDWBASimulation_wrapper : DiffuseDWBASimulation, bp::wrapper< DiffuseDWBASimulation > {

    DiffuseDWBASimulation_wrapper( )
    : DiffuseDWBASimulation( )
      , bp::wrapper< DiffuseDWBASimulation >(){
        // null constructor
    
    }

    virtual void run(  ) {
        if( bp::override func_run = this->get_override( "run" ) )
            func_run(  );
        else{
            this->DiffuseDWBASimulation::run(  );
        }
    }
    
    void default_run(  ) {
        DiffuseDWBASimulation::run( );
    }

    virtual ::LayerDWBASimulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->LayerDWBASimulation::clone(  );
        }
    }
    
    ::LayerDWBASimulation * default_clone(  ) const  {
        return LayerDWBASimulation::clone( );
    }

};

void register_DiffuseDWBASimulation_class(){

    bp::class_< DiffuseDWBASimulation_wrapper, bp::bases< LayerDWBASimulation >, boost::noncopyable >( "DiffuseDWBASimulation", bp::init< >() )    
        .def( 
            "getSize"
            , (::size_t ( ::DiffuseDWBASimulation::* )(  ) const)( &::DiffuseDWBASimulation::getSize ) )    
        .def( 
            "rescaleAbundances"
            , (void ( ::DiffuseDWBASimulation::* )( double ) )( &::DiffuseDWBASimulation::rescaleAbundances )
            , ( bp::arg("factor") ) )    
        .def( 
            "run"
            , (void ( ::DiffuseDWBASimulation::* )(  ) )(&::DiffuseDWBASimulation::run)
            , (void ( DiffuseDWBASimulation_wrapper::* )(  ) )(&DiffuseDWBASimulation_wrapper::default_run) )    
        .def( 
            "setRefractiveIndex"
            , (void ( ::DiffuseDWBASimulation::* )( ::complex_t ) )( &::DiffuseDWBASimulation::setRefractiveIndex )
            , ( bp::arg("n") ) )    
        .def( 
            "setSurfaceDensity"
            , (void ( ::DiffuseDWBASimulation::* )( double ) )( &::DiffuseDWBASimulation::setSurfaceDensity )
            , ( bp::arg("surface_density") ) )    
        .def( 
            "clone"
            , (::LayerDWBASimulation * ( ::LayerDWBASimulation::* )(  ) const)(&::LayerDWBASimulation::clone)
            , (::LayerDWBASimulation * ( DiffuseDWBASimulation_wrapper::* )(  ) const)(&DiffuseDWBASimulation_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() );

}
