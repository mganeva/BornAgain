# IsGISAXS01 example: Mixture of cylinders and prisms without interference
import sys, os, numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', '..', 'lib')
                ))

sys.path.append(os.path.abspath(os.path.join(os.path.split(__file__)[0],'..')))

from libBornAgainCore import *
from utils.show2d import PlotNumpyArray


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    # collection of particles
    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(n_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(5*nanometer, 5*nanometer)
    prism = Particle(n_particle, prism_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder, 0.0, 0.5)
    particle_decoration.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,-1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return GetOutputData(simulation)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)

