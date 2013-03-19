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
//! @file      FormFactors/FormFactorPyramid.h 
//! @brief     Defines class FormFactorPyramid.
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of pyramid.

class FormFactorPyramid : public IFormFactorBorn
{
public:
    //! @brief pyramid constructor
    //! @param height of pyramide
    //! @param half_side half of pyramid's base
    //! @param angle in radians between base and facet
    FormFactorPyramid(double height, double half_side, double alpha);

    ~FormFactorPyramid();
    virtual FormFactorPyramid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_height;
    double m_half_side;
    double m_alpha;
};

#endif // FORMFACTORPYRAMID_H
