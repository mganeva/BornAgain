// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/FitSuite.h
//! @brief     Defines class FitSuite.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITE_H
#define FITSUITE_H

#include "AttFitting.h"
#include "ChiSquaredModule.h"
#include "FitSuiteFunctions.h"
#include "FitSuiteObjects.h"
#include "FitSuiteParameters.h"
#include "FitSuiteStrategies.h"
#include "IMinimizer.h"
#include "IObserver.h"
#include <string>

class Simulation;
class ParameterPool;

//! Main class to perform fitting

class FitSuite : public IObservable
{
public:
    FitSuite();
    virtual ~FitSuite();

    //! clear all and prepare for the next fit
    void clear();

    //! add pair of (simulation, real data) for consecutive simulation
    void addSimulationAndRealData(const Simulation &simulation, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module=ChiSquaredModule());

    //! add fit parameter
    void addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless(), double error=0.0);
    void addFitParameter(const std::string &name, double value, const AttLimits &attlim=AttLimits::limitless(), double error=0.0);

    //! add fit strategy
    void addFitStrategy(IFitSuiteStrategy *strategy);

    //! set minimizer
    void setMinimizer(IMinimizer *minimizer) { delete m_minimizer;  m_minimizer = minimizer; }
    //! get minimizer
    IMinimizer *getMinimizer() { return m_minimizer; }

    //! link fitting parameters to parameters defined in simulations
    virtual void link_fit_parameters();

    //! run fitting which may consist of several minimization rounds
    virtual void runFit();

    //! run single minimization round
    virtual void minimize();

    //! return reference to the kit with data
    FitSuiteObjects *getFitObjects() { return &m_fit_objects; }

    //! return reference to fit parameters
    FitSuiteParameters *getFitParameters() { return &m_fit_parameters; }

    //! return reference to fit parameters
    FitSuiteStrategies *getFitStrategies() { return &m_fit_strategies; }

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const { return m_is_last_iteration; }

    //! get current number of minimization function calls
    size_t getNCalls() const;

    //! get the number of current strategy
    size_t getNStrategy() const { return m_fit_strategies.getNStrategy(); }

    //! print results of the screen
    void printResults() const;

    AttFitting &getAttributes() { return m_fit_attributes; }
    void setAttributes(const AttFitting &fit_attributes) { m_fit_attributes = fit_attributes; }

private:
    //! disabled copy constructor and assignment operator
    FitSuite &operator=(const FitSuite &);
    FitSuite(const FitSuite &);

    //! check if all prerequisites to run fit fit are filled
    bool check_prerequisites() const;

    AttFitting m_fit_attributes; //! general fit attributes
    FitSuiteObjects m_fit_objects; //! kit which contains sets of <simulation,real_data,chi_module> to fit
    FitSuiteParameters m_fit_parameters; //! collection of fit parameters
    FitSuiteStrategies m_fit_strategies; //! collection of strategies which drives multiple minimization rounds
    IMinimizer  *m_minimizer; //! minimization engine
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;

    bool m_is_last_iteration; //! set to true after last iteration complete
};

#endif // FITSUITE_H
