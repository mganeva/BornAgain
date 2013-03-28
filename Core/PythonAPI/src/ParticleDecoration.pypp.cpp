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
#include "ParticleDecoration.pypp.h"

namespace bp = boost::python;

struct ParticleDecoration_wrapper : ParticleDecoration, bp::wrapper< ParticleDecoration > {

    ParticleDecoration_wrapper( )
    : ParticleDecoration( )
      , bp::wrapper< ParticleDecoration >(){
        // null constructor
    
    }

    virtual ::ParticleDecoration * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->ParticleDecoration::clone(  );
        }
    }
    
    ::ParticleDecoration * default_clone(  ) const  {
        return ParticleDecoration::clone( );
    }

    virtual double getAbundanceFractionOfParticle( ::size_t index ) const  {
        if( bp::override func_getAbundanceFractionOfParticle = this->get_override( "getAbundanceFractionOfParticle" ) )
            return func_getAbundanceFractionOfParticle( index );
        else{
            return this->ParticleDecoration::getAbundanceFractionOfParticle( index );
        }
    }
    
    double default_getAbundanceFractionOfParticle( ::size_t index ) const  {
        return ParticleDecoration::getAbundanceFractionOfParticle( index );
    }

    virtual ::SafePointerVector< IInterferenceFunction > getInterferenceFunctions(  ) const  {
        if( bp::override func_getInterferenceFunctions = this->get_override( "getInterferenceFunctions" ) )
            return func_getInterferenceFunctions(  );
        else{
            return this->ParticleDecoration::getInterferenceFunctions(  );
        }
    }
    
    ::SafePointerVector< IInterferenceFunction > default_getInterferenceFunctions(  ) const  {
        return ParticleDecoration::getInterferenceFunctions( );
    }

    virtual ::size_t getNumberOfInterferenceFunctions(  ) const  {
        if( bp::override func_getNumberOfInterferenceFunctions = this->get_override( "getNumberOfInterferenceFunctions" ) )
            return func_getNumberOfInterferenceFunctions(  );
        else{
            return this->ParticleDecoration::getNumberOfInterferenceFunctions(  );
        }
    }
    
    ::size_t default_getNumberOfInterferenceFunctions(  ) const  {
        return ParticleDecoration::getNumberOfInterferenceFunctions( );
    }

    virtual ::size_t getNumberOfParticles(  ) const  {
        if( bp::override func_getNumberOfParticles = this->get_override( "getNumberOfParticles" ) )
            return func_getNumberOfParticles(  );
        else{
            return this->ParticleDecoration::getNumberOfParticles(  );
        }
    }
    
    ::size_t default_getNumberOfParticles(  ) const  {
        return ParticleDecoration::getNumberOfParticles( );
    }

    virtual ::ParticleInfo const * getParticleInfo( ::size_t index ) const  {
        if( bp::override func_getParticleInfo = this->get_override( "getParticleInfo" ) )
            return func_getParticleInfo( index );
        else{
            return this->ParticleDecoration::getParticleInfo( index );
        }
    }
    
    ::ParticleInfo const * default_getParticleInfo( ::size_t index ) const  {
        return ParticleDecoration::getParticleInfo( index );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void print_structure(  ) {
        if( bp::override func_print_structure = this->get_override( "print_structure" ) )
            func_print_structure(  );
        else{
            this->ISample::print_structure(  );
        }
    }
    
    void default_print_structure(  ) {
        ISample::print_structure( );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_ParticleDecoration_class(){

    bp::class_< ParticleDecoration_wrapper, bp::bases< IDecoration >, boost::noncopyable >( "ParticleDecoration", bp::init< >() )    
        .def( 
            "addInterferenceFunction"
            , (void ( ::ParticleDecoration::* )( ::IInterferenceFunction const & ) )( &::ParticleDecoration::addInterferenceFunction )
            , ( bp::arg("interference_function") ) )    
        .def( 
            "addParticle"
            , (void ( ::ParticleDecoration::* )( ::Particle const &,::Geometry::Transform3D const &,double,double ) )( &::ParticleDecoration::addParticle )
            , ( bp::arg("particle"), bp::arg("transform"), bp::arg("depth")=0, bp::arg("abundance")=1.0e+0 ) )    
        .def( 
            "addParticle"
            , (void ( ::ParticleDecoration::* )( ::Particle const &,double,double ) )( &::ParticleDecoration::addParticle )
            , ( bp::arg("particle"), bp::arg("depth")=0.0, bp::arg("abundance")=1.0e+0 ) )    
        .def( 
            "addParticleInfo"
            , (void ( ::ParticleDecoration::* )( ::ParticleInfo const & ) )( &::ParticleDecoration::addParticleInfo )
            , ( bp::arg("info") ) )    
        .def( 
            "clone"
            , (::ParticleDecoration * ( ::ParticleDecoration::* )(  ) const)(&::ParticleDecoration::clone)
            , (::ParticleDecoration * ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getAbundanceFractionOfParticle"
            , (double ( ::ParticleDecoration::* )( ::size_t ) const)(&::ParticleDecoration::getAbundanceFractionOfParticle)
            , (double ( ParticleDecoration_wrapper::* )( ::size_t ) const)(&ParticleDecoration_wrapper::default_getAbundanceFractionOfParticle)
            , ( bp::arg("index") ) )    
        .def( 
            "getInterferenceFunction"
            , (::IInterferenceFunction const * ( ::ParticleDecoration::* )( ::size_t ) const)( &::ParticleDecoration::getInterferenceFunction )
            , ( bp::arg("index") )
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getInterferenceFunctions"
            , (::SafePointerVector< IInterferenceFunction > ( ::ParticleDecoration::* )(  ) const)(&::ParticleDecoration::getInterferenceFunctions)
            , (::SafePointerVector< IInterferenceFunction > ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_getInterferenceFunctions) )    
        .def( 
            "getNumberOfInterferenceFunctions"
            , (::size_t ( ::ParticleDecoration::* )(  ) const)(&::ParticleDecoration::getNumberOfInterferenceFunctions)
            , (::size_t ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_getNumberOfInterferenceFunctions) )    
        .def( 
            "getNumberOfParticles"
            , (::size_t ( ::ParticleDecoration::* )(  ) const)(&::ParticleDecoration::getNumberOfParticles)
            , (::size_t ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_getNumberOfParticles) )    
        .def( 
            "getParticleInfo"
            , (::ParticleInfo const * ( ::ParticleDecoration::* )( ::size_t ) const)(&::ParticleDecoration::getParticleInfo)
            , (::ParticleInfo const * ( ParticleDecoration_wrapper::* )( ::size_t ) const)(&ParticleDecoration_wrapper::default_getParticleInfo)
            , ( bp::arg("index") )
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( ParticleDecoration_wrapper::* )(  ) )(&ParticleDecoration_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample * ( ::ICompositeSample::* )(  ) )(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample * ( ParticleDecoration_wrapper::* )(  ) )(&ParticleDecoration_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample const * ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample const * ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( ParticleDecoration_wrapper::* )(  ) )(&ParticleDecoration_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( ParticleDecoration_wrapper::* )(  ) )(&ParticleDecoration_wrapper::default_setParametersAreChanged) )    
        .def( 
            "size"
            , (::size_t ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::size)
            , (::size_t ( ParticleDecoration_wrapper::* )(  ) const)(&ParticleDecoration_wrapper::default_size) );

}
