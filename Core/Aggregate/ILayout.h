// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ILayout.h
//! @brief     Defines and implements interface class ILayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ILAYOUT_H
#define ILAYOUT_H

#include "ISample.h"
#include "SafePointerVector.h"

class IAbstractParticle;
class IInterferenceFunction;

//! Pure virtual interface class to equip a sample layer with scattering properties.
//! Currently only inherited by ParticleLayout; in the future also by domain structure.
//!
//! @ingroup samples_internal

// NOTE: When domain structures are implemented, this interface would probably undergo
// major changes, because a domain layout would not contain particles
class BA_CORE_API_ ILayout : public ISample
{
public:
    enum EInterferenceApproximation { DA, SSCA };

    ILayout() : m_weight(1.0), me_approx(DA) {}
    virtual ~ILayout();

    virtual ILayout* clone() const = 0;
    virtual ILayout* cloneWithOffset(double offset) const = 0;

    virtual void accept(INodeVisitor* visitor) const = 0;

    //! Returns information on all particles (type and abundance)
    //! and generates new particles if an IAbstractParticle denotes a collection
    virtual SafePointerVector<IParticle> particles() const = 0;

    /// Get total abundance of all particles
    virtual double getTotalAbundance() const = 0;

    //! Returns surface density of all particles
    virtual double totalParticleSurfaceDensity() const = 0;

    //! Sets surface density of all particles
    virtual void setTotalParticleSurfaceDensity(double particle_density) = 0;

    //! Returns the relative weight of this layout
    double weight() const { return m_weight; }

    //! Sets the relative weight of this layout
    void setWeight(double weight) { m_weight = weight; }

    //! Gets the used approximation for particles and interference functions
    EInterferenceApproximation getApproximation() const { return me_approx; }

    //! Sets the used approximation for particles and interference functions
    void setApproximation(EInterferenceApproximation approximation) { me_approx = approximation; }

protected:
    double m_weight;

private:
    //! Approximation used for combining particles and interference functions
    EInterferenceApproximation me_approx;
};

#endif // ILAYOUT_H
