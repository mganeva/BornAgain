// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/inc/Vectors3D.h
//! @brief     Defines basic vectors in R^3 and C^3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VECTORS3D_H
#define VECTORS3D_H

#include "BasicVector3D.h"

typedef std::complex<double> complex_t;

typedef Geometry::BasicVector3D<double> kvector_t;
typedef Geometry::BasicVector3D<complex_t> cvector_t;

#endif // VECTORS3D_H
