// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/IParameterized.cpp
//! @brief     Implements class IParameterized,
//!               mainly by including IParameterized.h.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "IParameterized.h"
#include "Utils.h"

IParameterized &IParameterized::operator=(const IParameterized &other)
{
    if( this != &other)
    {
        INamed::operator=(other);
        // parameters are not copied
    }
    return *this;
}

//! Creates new parameter pool, with all local parameter and parameters of children

//! User has to delete it.
//!
ParameterPool *IParameterized::createParameterTree() const
{
    ParameterPool *newpool = new ParameterPool;
    std::string path("/");
    addParametersToExternalPool(path, newpool);
    return newpool;
}

//! Adds parameters from local pool to external pool and call recursion over direct children.

std::string IParameterized::addParametersToExternalPool(
    std::string path, ParameterPool *external_pool, int copy_number) const
{
    // adding trailing slash, if it is not already there
    if( path[path.length()-1] != '/' ) path += "/";

    // constructing new path, using object name and copy number
    std::ostringstream osCopyNumber;
    if(copy_number >=0) osCopyNumber << copy_number;
    path =  path + getName() + osCopyNumber.str() + "/";

    // copy local parameter to external pool
    m_parameters.copyToExternalPool(path, external_pool);

    return path;
}

void IParameterized::printParameters() const
{
    ParameterPool *p_pool = createParameterTree();
    std::cout << *p_pool << std::endl;
    delete p_pool;
}

//! Throw non-implemented exception (needed for Python).

//! No pure virtual function here,
//! due to problems in exporting abstract classes to python
//!
void IParameterized::init_parameters()
{
    throw NotImplementedException("IParameterized::init_parameters() -> "
                                  "Error! Method is not implemented");
}
