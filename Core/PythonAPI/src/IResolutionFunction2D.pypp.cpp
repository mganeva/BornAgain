// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
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
#include "IResolutionFunction2D.pypp.h"

namespace bp = boost::python;

struct IResolutionFunction2D_wrapper : IResolutionFunction2D, bp::wrapper< IResolutionFunction2D > {

    IResolutionFunction2D_wrapper()
    : IResolutionFunction2D()
      , bp::wrapper< IResolutionFunction2D >(){
        // null constructor
        
    }

    virtual ::IResolutionFunction2D * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual double evaluateCDF( double x, double y ) const {
        bp::override func_evaluateCDF = this->get_override( "evaluateCDF" );
        return func_evaluateCDF( x, y );
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

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
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

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< IResolutionFunction2D_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
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

};

void register_IResolutionFunction2D_class(){

    bp::class_< IResolutionFunction2D_wrapper, bp::bases< IParameterized >, boost::noncopyable >( "IResolutionFunction2D" )    
        .def( 
            "clone"
            , bp::pure_virtual( (::IResolutionFunction2D * ( ::IResolutionFunction2D::* )(  ) const)(&::IResolutionFunction2D::clone) )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "evaluateCDF"
            , bp::pure_virtual( (double ( ::IResolutionFunction2D::* )( double,double ) const)(&::IResolutionFunction2D::evaluateCDF) )
            , ( bp::arg("x"), bp::arg("y") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( IResolutionFunction2D_wrapper::* )(  ) )(&IResolutionFunction2D_wrapper::default_areParametersChanged) )    
        .def( 
            "clearParameterPool"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::clearParameterPool)
            , (void ( IResolutionFunction2D_wrapper::* )(  ) )(&IResolutionFunction2D_wrapper::default_clearParameterPool) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( IResolutionFunction2D_wrapper::* )(  ) const)(&IResolutionFunction2D_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( IResolutionFunction2D_wrapper::* )(  ) const)(&IResolutionFunction2D_wrapper::default_printParameters) )    
        .def( 
            "registerParameter"
            , (void (*)( ::IParameterized &,::std::string const &,long unsigned int ))( &IResolutionFunction2D_wrapper::default_registerParameter )
            , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) )    
        .def( 
            "setParameterValue"
            , (bool ( ::IParameterized::* )( ::std::string const &,double ) )(&::IParameterized::setParameterValue)
            , (bool ( IResolutionFunction2D_wrapper::* )( ::std::string const &,double ) )(&IResolutionFunction2D_wrapper::default_setParameterValue)
            , ( bp::arg("name"), bp::arg("value") ) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( IResolutionFunction2D_wrapper::* )(  ) )(&IResolutionFunction2D_wrapper::default_setParametersAreChanged) );

}
