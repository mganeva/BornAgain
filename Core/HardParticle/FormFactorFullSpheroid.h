// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSpheroid.h
//! @brief     Defines class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHEROID_H
#define FORMFACTORFULLSPHEROID_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! A full spheroid (an ellipsoid with two equal axes, hence with circular cross section)
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorFullSpheroid : public IFormFactorBorn
{
public:
    FormFactorFullSpheroid(double radius, double height);

    FormFactorFullSpheroid* clone() const override final {
        return new FormFactorFullSpheroid(m_radius, m_height); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }

    double radialExtension() const override final { return m_radius; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorFullSpheroid>> mP_integrator;
#endif
};

#endif // FORMFACTORFULLSPHEROID_H
