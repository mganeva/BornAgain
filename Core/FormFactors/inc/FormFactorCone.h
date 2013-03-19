// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/FormFactorCone.h 
//! @brief     Defines class FormFactorCone.
//
// ************************************************************************** //

#ifndef FORMFACTORCONE_H
#define FORMFACTORCONE_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of cone.

class FormFactorCone : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param height of Conee
    //! @param radius half of Cone's base
    //! @param angle in radians between base and facet
    FormFactorCone(double radius, double height,  double alpha);

    ~FormFactorCone();
    virtual FormFactorCone* clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q (const cvector_t &q) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    //    double ConeIntegral(double Z, void* params) const;
    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double ConeIntegralReal(double Z, void* params) const;
    double ConeIntegralImaginary(double Z, void* params) const;

    double m_radius;
    double m_height;
    double m_alpha;
    mutable cvector_t m_q;

};

#endif // FORMFACTORCONE_H
