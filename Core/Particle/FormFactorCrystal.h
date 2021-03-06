// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCrystal.h
//! @brief     Defines class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORCRYSTAL_H
#define FORMFACTORCRYSTAL_H

#include "IFormFactorBorn.h"
#include "Lattice.h"

//! The formfactor of a MesoCrystal.
//! @ingroup formfactors

class BA_CORE_API_ FormFactorCrystal : public IFormFactor
{
public:
    FormFactorCrystal(const Lattice& lattice, const IFormFactor& basis_form_factor,
                      const IFormFactor& meso_form_factor);
    ~FormFactorCrystal() override final;

    FormFactorCrystal* clone() const override final {
        return new FormFactorCrystal(m_lattice, *mp_basis_form_factor, *mp_meso_form_factor); }

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setAmbientMaterial(Material material) override {
        mp_basis_form_factor->setAmbientMaterial(std::move(material));
    }

    double volume() const override final { return mp_meso_form_factor->volume(); }
    double radialExtension() const override final {
        return mp_meso_form_factor->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    void calculateLargestReciprocalDistance();

    Lattice m_lattice;
    IFormFactor* mp_basis_form_factor;
    IFormFactor* mp_meso_form_factor; //!< The outer shape of this mesocrystal
    double m_max_rec_length;
};

#endif // FORMFACTORCRYSTAL_H
