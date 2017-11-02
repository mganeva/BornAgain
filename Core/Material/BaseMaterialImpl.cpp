#include "BaseMaterialImpl.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include "MaterialUtils.h"
#include "PhysicalConstants.h"
#include <memory>

using PhysConsts::mu_B;
using PhysConsts::gamma_n;
using PhysConsts::r_e;
 // The factor 1e-18 is here to have unit: m/A*nm^-2
constexpr double magnetization_prefactor
    = (gamma_n * r_e / 2.0 / mu_B) * 1e-18;

namespace {
cvector_t OrthogonalToBaseVector(cvector_t base, const kvector_t vector)
{
    if (base.mag2()==0.0) return cvector_t {};
    cvector_t projection = (base.dot(vector)/base.mag2())*base;
    return vector.complex() - projection;
}
}

BaseMaterialImpl::BaseMaterialImpl(const std::string& name, kvector_t magnetization)
    : INamed(name)
    , m_magnetization(magnetization)
{}

BaseMaterialImpl::~BaseMaterialImpl()
{}

BaseMaterialImpl* BaseMaterialImpl::inverted() const
{
    std::string name = isScalarMaterial() ? getName()
                                          : getName()+"_inv";
    std::unique_ptr<BaseMaterialImpl> result(this->clone());
    result->setName(name);
    result->setMagnetization(-magnetization());
    return result.release();
}

Eigen::Matrix2cd BaseMaterialImpl::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetization);
    complex_t unit_factor = scalarSubtrSLD(wavevectors);
    return MagnetizationCorrection(unit_factor, magnetization_prefactor, mag_ortho);
}

BaseMaterialImpl* BaseMaterialImpl::transformedMaterial(const Transform3D& transform) const
{
    kvector_t transformed_field = transform.transformed(m_magnetization);
    std::unique_ptr<BaseMaterialImpl> result(this->clone());
    result->setName(this->getName());
    result->setMagnetization(transformed_field);
    return result.release();
}

