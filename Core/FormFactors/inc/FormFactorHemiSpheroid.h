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
//! @file      FormFactors/FormFactorHemiSpheroid.h 
//! @brief     Defines class FormFactorHemiSpheroid.
//
// ************************************************************************** //

#ifndef FORMFACTORHEMISPHEROID_H
#define FORMFACTORHEMISPHEROID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of a ??

class FormFactorHemiSpheroid : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param height of Conee
    //! @param radius half of Cone's base
    //! @param angle in radians between base and facet
    FormFactorHemiSpheroid(double radius,  double width, double height);
    double HemiSpheroidIntegral(double Z, void* params) const;

    ~FormFactorHemiSpheroid();
    virtual FormFactorHemiSpheroid* clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q (const cvector_t &q) const;

private:
    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double HemiSpheroidIntegralReal(double Z, void* params) const;

    double HemiSpheroidIntegralImaginary(double Z, void* params) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    double m_radius;
    double m_width;
    double m_height;
    mutable cvector_t m_q;
};

#endif // FormFactorHemiSpheroid_H
