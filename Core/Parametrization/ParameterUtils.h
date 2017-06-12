// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterUtils.h
//! @brief     Defines namespace ParameterUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERUTILS_H
#define PARAMETERUTILS_H

#include "WinDllMacros.h"
#include <string>

class ParameterDistribution;

namespace ParameterUtils
{

//! Returns true if given parameter name is related to angles.
BA_CORE_API_ bool isAngleRelated(const std::string& par_name);

//! Returns true if given ParameterDistribution is intended for angles (based on
//! main parameter name).
BA_CORE_API_ bool isAngleRelated(const ParameterDistribution& distr);

}

#endif // PARAMETERPATTERN_H
