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
#include "FTDistribution2DCauchy.pypp.h"

namespace bp = boost::python;

struct FTDistribution2DCauchy_wrapper : FTDistribution2DCauchy, bp::wrapper< FTDistribution2DCauchy > {

    FTDistribution2DCauchy_wrapper(FTDistribution2DCauchy const & arg )
    : FTDistribution2DCauchy( arg )
      , bp::wrapper< FTDistribution2DCauchy >(){
        // copy constructor
        
    }

    FTDistribution2DCauchy_wrapper(double omega_x, double omega_y )
    : FTDistribution2DCauchy( omega_x, omega_y )
      , bp::wrapper< FTDistribution2DCauchy >(){
        // constructor
    
    }

    virtual ::FTDistribution2DCauchy * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FTDistribution2DCauchy::clone(  );
        }
    }
    
    ::FTDistribution2DCauchy * default_clone(  ) const  {
        return FTDistribution2DCauchy::clone( );
    }

    virtual double evaluate( double qx, double qy ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( qx, qy );
        else{
            return this->FTDistribution2DCauchy::evaluate( qx, qy );
        }
    }
    
    double default_evaluate( double qx, double qy ) const  {
        return FTDistribution2DCauchy::evaluate( qx, qy );
    }

    virtual void transformToStarBasis( double qX, double qY, double alpha, double a, double b, double & qa, double & qb ) const  {
        if( bp::override func_transformToStarBasis = this->get_override( "transformToStarBasis" ) )
            func_transformToStarBasis( qX, qY, alpha, a, b, qa, qb );
        else{
            this->FTDistribution2DCauchy::transformToStarBasis( qX, qY, alpha, a, b, qa, qb );
        }
    }
    
    void default_transformToStarBasis( double qX, double qY, double alpha, double a, double b, double & qa, double & qb ) const  {
        FTDistribution2DCauchy::transformToStarBasis( qX, qY, alpha, a, b, qa, qb );
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

void register_FTDistribution2DCauchy_class(){

    bp::class_< FTDistribution2DCauchy_wrapper, bp::bases< IFTDistribution2D > >( "FTDistribution2DCauchy", bp::init< double, double >(( bp::arg("omega_x"), bp::arg("omega_y") )) )    
        .def( 
            "clone"
            , (::FTDistribution2DCauchy * ( ::FTDistribution2DCauchy::* )(  ) const)(&::FTDistribution2DCauchy::clone)
            , (::FTDistribution2DCauchy * ( FTDistribution2DCauchy_wrapper::* )(  ) const)(&FTDistribution2DCauchy_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "evaluate"
            , (double ( ::FTDistribution2DCauchy::* )( double,double ) const)(&::FTDistribution2DCauchy::evaluate)
            , (double ( FTDistribution2DCauchy_wrapper::* )( double,double ) const)(&FTDistribution2DCauchy_wrapper::default_evaluate)
            , ( bp::arg("qx"), bp::arg("qy") ) )    
        .def( 
            "transformToStarBasis"
            , (void ( ::FTDistribution2DCauchy::* )( double,double,double,double,double,double &,double & ) const)(&::FTDistribution2DCauchy::transformToStarBasis)
            , (void ( FTDistribution2DCauchy_wrapper::* )( double,double,double,double,double,double &,double & ) const)(&FTDistribution2DCauchy_wrapper::default_transformToStarBasis)
            , ( bp::arg("qX"), bp::arg("qY"), bp::arg("alpha"), bp::arg("a"), bp::arg("b"), bp::arg("qa"), bp::arg("qb") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( FTDistribution2DCauchy_wrapper::* )(  ) )(&FTDistribution2DCauchy_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( FTDistribution2DCauchy_wrapper::* )(  ) const)(&FTDistribution2DCauchy_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( FTDistribution2DCauchy_wrapper::* )(  ) const)(&FTDistribution2DCauchy_wrapper::default_printParameters) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( FTDistribution2DCauchy_wrapper::* )(  ) )(&FTDistribution2DCauchy_wrapper::default_setParametersAreChanged) );

}
