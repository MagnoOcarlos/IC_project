# -*- coding: utf-8 -*-
import sys
import numpy as np
from crpropa import *


def lmaxFromCohrenceLength(lmin, gridsize, compCoerencia):
	
	n=1000
	lmaxs=np.logspace(np.log10(lmin), np.log10(gridsize), n)

	lcs= [ turbulentCorrelationLength(lmin,lmax,-11/3) for lmax in lmaxs ]
	

	return	np.interp(compCoerencia, lcs,lmaxs)
	
	
NEvents = int(sys.argv[1]) #números de eventos lidos via terminal
OutputName = 'dados.txt'
#supre = 'supression.txt'
A =1 #massa atômica
Z =1 #número atômico


#Volume da simulação

'''
	Aqui criamos uma 'caixa' na qual o ocorrerá a nossa simulação. Sendo mais específico, é a região na qual nosso campo mag-
	nético atua.
'''

boxOrigin = Vector3d(0, 0, 0) * Mpc
boxSize = 10 * Mpc
boxEdge = Vector3d(boxSize, boxSize, boxSize)



#Campo Magnético

'''
	Aqui vamos criar o campo magnético da simulação. Tratando-se de uma simualção 3d, usasse o Vector grid para guardar a infor-
	mações dos campo nos eixos (x,y,z) (usando a função VectorGrid)
	
	VectorGrid: o primeiro parâmetro da função é a origem da caixa de atuação do campo; o segundo é o número de células que irão
	preencer essa caixa ( pense num tabuleiro de xadrez em 3d); o terceiro é o tamanho de cada 'casa' desse tabuleiro de xadrez.

	initTurbulence: Essa função inicizaliza um campo turbulento aleatório. Seus parâmetro 
		
		1°: vgrid-> é a grid inicializada com a Função VectorGrid
		2°: módulo do nosso campo magnético
		3°: lmin-> comprimento de onda  mínimo de oscilação turbulenta.
		4°: lmx-> comprimento de onda máximo de oscilação turbulenta.
		5°: índice da lei de potência( nesse caso temos o espectro de Kolmogorov)
		5°: seed 
'''



randomSeed = 42
space = 0.1*Mpc
lmax=lmaxFromCohrenceLength(space*2,boxSize,int(sys.argv[2])*Mpc) # gere o comprimento máximo ideal para o CL desejado
vgrid = VectorGrid(boxOrigin, 1024, space)
initTurbulence(vgrid, 10*nG, space*2, lmax, -11/3, randomSeed)
bField0 = MagneticFieldGrid(vgrid)


#Info

'''
	Print de algumas informações do nosso campo.

'''
'''
print("lmax={} e lmin={}".format(lmax/kpc,2*space/Mpc))
print ("Lc = {}kpc".format(turbulentCorrelationLength( 2*space, lmax , -11./3.)/Mpc))  # correlation length
print ("sqrt(<B^2>) = {} nG".format((rmsFieldStrength(vgrid) / nG)))   # RMS
print ("<|B|> = {} nG".format((meanFieldStrength(vgrid) / nG)) ) # mean
print ("B(10 Mpc, 0, 0) ={}nG".format(bField0.getField(Vector3d(10,0,0) * Mpc) / nG))


'''

#Observador

'''
	A ideia de simulação é fazer uma geometria reversa na qual iremos posicionar a fonte dentro de uma esfera de raio R(distância
	da fonte desejada até a terra). Nesta simulação, a fonte é CenA que está a uma distância de 3.7 Mpc da terra.

	A esfera em questão é a Terra.

	As funções nessa região são intuitivas.
'''
out = TextOutput("../geometry/dados1.txt")
obs = Observer()
obs.add((ObserverSurface( Sphere(Vector3d(0,0,0), 3.7*Mpc)) ))
obs.onDetection(out)


out2 = TextOutput("../geometry/dados2.txt")
obs2=Observer()
obs2.add((ObserverSurface( Sphere(Vector3d(0,0,0), 10*Mpc))))
obs2.setDeactivateOnDetection(False)
obs2.onDetection(out2)


out3 = TextOutput("../geometry/dados3.txt")
obs3=Observer()
obs3.add((ObserverSurface( Sphere(Vector3d(0,0,0), 20*Mpc))))
obs3.setDeactivateOnDetection(False)
obs3.onDetection(out3)


out4 = TextOutput("../geometry/dados4.txt")
obs4=Observer()
obs4.add((ObserverSurface( Sphere(Vector3d(0,0,0), 30*Mpc))))
obs4.setDeactivateOnDetection(False)
obs4.onDetection(out4)



out5 = TextOutput("../geometry/dados5.txt")
obs5=Observer()
obs5.add((ObserverSurface( Sphere(Vector3d(0,0,0), 50*Mpc))))
obs5.setDeactivateOnDetection(False)
obs5.onDetection(out5)


out6 = TextOutput("../geometry/dados6.txt")
obs6=Observer()
obs6.add((ObserverSurface( Sphere(Vector3d(0,0,0), 60*Mpc))))
obs5.setDeactivateOnDetection(False)
obs6.onDetection(out6)


out7 = TextOutput("../geometry/dados7.txt")
obs7=Observer()
obs7.add((ObserverSurface( Sphere(Vector3d(0,0,0), 70*Mpc))))
obs7.setDeactivateOnDetection(False)
obs7.onDetection(out7)


out8 = TextOutput("../geometry/dados8.txt")
obs8=Observer()
obs8.add((ObserverSurface( Sphere(Vector3d(0,0,0), 80*Mpc))))
obs8.setDeactivateOnDetection(False)
obs8.onDetection(out8)


out9 = TextOutput("../geometry/dados9.txt")
obs9=Observer()
obs9.add((ObserverSurface( Sphere(Vector3d(0,0,0), 90*Mpc))))
obs9.setDeactivateOnDetection(False)
obs9.onDetection(out9)


out10 = TextOutput("../geometry/dados10.txt")
obs10 =Observer()
obs10.add((ObserverSurface( Sphere(Vector3d(0,0,0), 100*Mpc))))
obs10.setDeactivateOnDetection(False)
obs10.onDetection(out10)


output.setEnergySclae(eV)


# module setup
sim = ModuleList()
#sim.add(SimplePropagation())
sim.add(PropagationBP(bField0,1e-3,1*kpc,10*kpc))
sim.add(PhotoPionProduction(CMB))
sim.add(PhotoPionProduction(IRB_Gilmore12))
sim.add(PhotoDisintegration(CMB))
sim.add(PhotoDisintegration(IRB_Gilmore12))
sim.add(NuclearDecay())
sim.add(ElectronPairProduction(CMB))
sim.add(ElectronPairProduction(IRB_Gilmore12))
sim.add(MinimumEnergy(0.01 * EeV))
sim.add(Redshift())
sim.add(MaximumTrajectoryLength(4000 * Mpc))
sim.add(obs)
#sim.add(obs2)


#fonte


'''
	A fonte irá emitir somente prótons isotropicamente. A energia de emissão varia de 1e17 até 1e21
'''
sourceList = SourceList()
source = Source()
source.add(SourcePosition(Vector3d(0, 0, 0)))
source.add(SourceIsotropicEmission())
source.add(SourcePowerLawSpectrum(1e17 * eV, 1e21 * eV, -1.))
source.add(SourceParticleType(nucleusId(A,Z)))
sourceList.add(source, 1)



c = sourceList.getCandidate()

#execute
sim.setShowProgress(True)
sim.run(sourceList, NEvents, True)
