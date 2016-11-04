// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.cpp
//! @brief     Implements subclasses of IParameterTranslator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTranslators.h"
#include "BornAgainNamespace.h"
#include "ParticleItem.h"
#include "RotationItems.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "LatticeTypeItems.h"
#include <QDebug>

using std::string;

QStringList PositionTranslator::split(const QString& par_name) const
{
    QStringList result;
    string position_name = translate(par_name);
    if (!position_name.empty()) {
        result << par_name;
    }
    return result;
}

string PositionTranslator::translate(const QString& name) const
{
    QStringList name_list = name.split("/");
    if (name_list.size() > 2) return {};
    if (name_list.size() > 1 && name_list[0] == ParticleItem::P_POSITION) {
        if (name_list[1] == VectorItem::P_X) {
            return BornAgain::PositionX;
        }
        if (name_list[1] == VectorItem::P_Y) {
            return BornAgain::PositionY;
        }
        if (name_list[1] == VectorItem::P_Z) {
            return BornAgain::PositionZ;
        }
    }
    return {};
}

QStringList LatticeTypeTranslator::split(const QString& par_name) const
{
    QStringList result;
    string position_name = translate(par_name);
    if (!position_name.empty()) {
        result << par_name;
    }
    return result;
}

string LatticeTypeTranslator::translate(const QString& name) const
{
    QStringList name_list = name.split("/");
    if (name_list.size() != 2) return {};
    if (name_list[0] == Constants::BasicLatticeType) {

        if (name_list[1] == BasicLatticeTypeItem::P_LATTICE_LENGTH1) {
            return BornAgain::LatticeLength1;
        }
        if (name_list[1] == BasicLatticeTypeItem::P_LATTICE_LENGTH2) {
            return BornAgain::LatticeLength2;
        }

        if (name_list[1] == BasicLatticeTypeItem::P_LATTICE_ANGLE) {
            return BornAgain::LatticeAngle;
        }
    }

    else if(name_list[0] == Constants::SquareLatticeType
            || name_list[0] == Constants::HexagonalLatticeType) {
        if (name_list[1] == SquareLatticeTypeItem::P_LATTICE_LENGTH) {
            return SquareLatticeTypeItem::P_LATTICE_LENGTH.toStdString() + std::string("*");
        }
    }
    return {};
}

QStringList RotationTranslator::split(const QString& par_name) const
{
    QStringList result;
    string rotation_name = translate(par_name);
    if (!rotation_name.empty()) {
        result << par_name;
    }
    return result;
}

string RotationTranslator::translate(const QString& name) const
{
    QStringList name_list = name.split("/");
    string separator {"/"};
    if (name_list.size() > 3) return {};
    if (name_list.size() == 3 && name_list[0] == Constants::TransformationType) {
        if (name_list[1] == Constants::XRotationType) {
            return BornAgain::XRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::YRotationType) {
            return BornAgain::YRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::ZRotationType) {
            return BornAgain::ZRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::EulerRotationType) {
            if (name_list[2] == EulerRotationItem::P_ALPHA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Alpha;
            } else if (name_list[2] == EulerRotationItem::P_BETA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Beta;
            } else if (name_list[2] == EulerRotationItem::P_GAMMA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Gamma;
            }
        }
    }
    return {};
}
