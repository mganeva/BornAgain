// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDistributionItems.cpp
//! @brief     Implements FTDistribution1DItem's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FTDistributionItems.h"
#include "Units.h"
#include "BornAgainNamespace.h"

const QString FTDistribution1DItem::P_OMEGA = QString::fromStdString(BornAgain::Omega);

FTDistribution1DItem::FTDistribution1DItem(const QString& name)
    : SessionItem(name)
{

}

void FTDistribution1DItem::add_omega_property()
{
    addProperty(P_OMEGA, 1.0)
        ->setToolTip(QStringLiteral("Half-width of the distribution in nanometers"));
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DCauchyItem::FTDistribution1DCauchyItem()
    : FTDistribution1DItem(Constants::FTDistribution1DCauchyType)
{
    setToolTip(QStringLiteral("One-dimensional Cauchy probability distribution"));
    add_omega_property();
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DCauchyItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DCauchy>(getItemValue(P_OMEGA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DGaussItem::FTDistribution1DGaussItem()
    : FTDistribution1DItem(Constants::FTDistribution1DGaussType)
{
    setToolTip(QStringLiteral("One-dimensional Gauss probability distribution"));
    add_omega_property();
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DGaussItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DGauss>(getItemValue(P_OMEGA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DGateItem::FTDistribution1DGateItem()
    : FTDistribution1DItem(Constants::FTDistribution1DGateType)
{
    setToolTip(QStringLiteral("One-dimensional Gate probability distribution"));
    add_omega_property();
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DGateItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DGate>(getItemValue(P_OMEGA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DTriangleItem::FTDistribution1DTriangleItem()
    : FTDistribution1DItem(Constants::FTDistribution1DTriangleType)
{
    setToolTip(QStringLiteral("One-dimensional triangle probability distribution"));
    add_omega_property();
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DTriangleItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DTriangle>(
                getItemValue(P_OMEGA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DCosineItem::FTDistribution1DCosineItem()
    : FTDistribution1DItem(Constants::FTDistribution1DCosineType)
{
    setToolTip(QStringLiteral("One-dimensional Cosine probability distribution"));
    add_omega_property();
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DCosineItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DCosine>(getItemValue(P_OMEGA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution1DVoigtItem::P_ETA = QString::fromStdString(BornAgain::Eta);

FTDistribution1DVoigtItem::FTDistribution1DVoigtItem()
    : FTDistribution1DItem(Constants::FTDistribution1DVoigtType)
{
    setToolTip(QStringLiteral("One-dimensional pseudo-Voigt probability distribution"));
    add_omega_property();
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0)).setToolTip(QStringLiteral(
        "Parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)"));
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DVoigtItem::createFTDistribution() const
{
    return std::make_unique<FTDistribution1DVoigt>(getItemValue(P_OMEGA).toDouble(),
                                                          getItemValue(P_ETA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution2DItem::P_OMEGA_X = QString::fromStdString(BornAgain::OmegaX);
const QString FTDistribution2DItem::P_OMEGA_Y = QString::fromStdString(BornAgain::OmegaY);
const QString FTDistribution2DItem::P_GAMMA = QString::fromStdString(BornAgain::Gamma);

FTDistribution2DItem::FTDistribution2DItem(const QString& name)
    : SessionItem(name)
{
}

void FTDistribution2DItem::add_omega_properties()
{
    addProperty(P_OMEGA_X, 1.0)->setToolTip(
        QStringLiteral("Half-width of the distribution along its x-axis in nanometers"));
    addProperty(P_OMEGA_Y, 1.0)->setToolTip(
        QStringLiteral("Half-width of the distribution along its y-axis in nanometers"));
}

void FTDistribution2DItem::add_gamma_property()
{
    addProperty(P_GAMMA, 0.0)->setToolTip(QStringLiteral("Angle in direct space between "
        "first lattice vector \nand x-axis of the distribution in degrees"));
}

void FTDistribution2DItem::add_properties()
{
    add_omega_properties();
    add_gamma_property();
}


// --------------------------------------------------------------------------------------------- //

FTDistribution2DCauchyItem::FTDistribution2DCauchyItem()
    : FTDistribution2DItem(Constants::FTDistribution2DCauchyType)
{
    setToolTip(QStringLiteral("Two-dimensional Cauchy probability distribution"));
    add_properties();
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DCauchyItem::createFTDistribution() const
{
    auto result = std::make_unique<FTDistribution2DCauchy>(
                getItemValue(P_OMEGA_X).toDouble(),
                getItemValue(P_OMEGA_Y).toDouble(),
                Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DGaussItem::FTDistribution2DGaussItem()
    : FTDistribution2DItem(Constants::FTDistribution2DGaussType)
{
    setToolTip(QStringLiteral("Two-dimensional Gauss probability distribution"));
    add_properties();
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DGaussItem::createFTDistribution() const
{
    auto result = std::make_unique<FTDistribution2DGauss>(
        getItemValue(P_OMEGA_X).toDouble(), getItemValue(P_OMEGA_Y).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));

    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DGateItem::FTDistribution2DGateItem()
    : FTDistribution2DItem(Constants::FTDistribution2DGateType)
{
    setToolTip(QStringLiteral("Two-dimensional Gate probability distribution"));
    add_properties();
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DGateItem::createFTDistribution() const
{
    auto result = std::make_unique<FTDistribution2DGate>(
        getItemValue(P_OMEGA_X).toDouble(), getItemValue(P_OMEGA_Y).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DConeItem::FTDistribution2DConeItem()
    : FTDistribution2DItem(Constants::FTDistribution2DConeType)
{
    setToolTip(QStringLiteral("Two-dimensional Cone probability distribution"));
    add_properties();
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DConeItem::createFTDistribution() const
{
    auto result = std::make_unique<FTDistribution2DCone>(
        getItemValue(P_OMEGA_X).toDouble(), getItemValue(P_OMEGA_Y).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution2DVoigtItem::P_ETA = QString::fromStdString(BornAgain::Eta);

FTDistribution2DVoigtItem::FTDistribution2DVoigtItem()
    : FTDistribution2DItem(Constants::FTDistribution2DVoigtType)
{
    setToolTip(QStringLiteral("Two-dimensional pseudo-Voigt probability distribution"));

    add_omega_properties();
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0)).setToolTip(QStringLiteral(
        "Parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)"));
    add_gamma_property();
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DVoigtItem::createFTDistribution() const
{
    auto result = std::make_unique<FTDistribution2DVoigt>(
        getItemValue(P_OMEGA_X).toDouble(), getItemValue(P_OMEGA_Y).toDouble(),
        getItemValue(P_ETA).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}
