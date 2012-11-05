#include "IChiSquaredModule.h"

IChiSquaredModule::IChiSquaredModule(const OutputData<double>& real_data)
: mp_simulation_data(0), m_chi2_value(0)
{
    mp_real_data = real_data.clone();
    mp_squared_function = new DefaultSquaredFunction();
}

IChiSquaredModule::~IChiSquaredModule()
{
    delete mp_real_data;
    delete mp_simulation_data;
    delete mp_squared_function;
}

void IChiSquaredModule::setRealData(const OutputData<double>& real_data)
{
    delete mp_real_data;
    mp_real_data = real_data.clone();
}

void IChiSquaredModule::setSimulationData(
        const OutputData<double>& simulation_data)
{
    delete mp_simulation_data;
    mp_simulation_data = simulation_data.clone();
}
