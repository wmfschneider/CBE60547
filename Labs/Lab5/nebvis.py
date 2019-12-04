#!/usr/bin/env python3

from ase.io import read
import glob
from ase.visualize import view
import os
from ase import Atoms,Atom
import numpy as np
#os.chdir('NH3-cineb')
maxforces = []
folders = glob.glob('[0-9]'*2)
traj = []
energies = []
cwd = os.getcwd()
for f in folders:

    #Get the length of atoms, and last image from OUTCAR
    atoms = read('{}/OUTCAR'.format(f))
    traj+=[atoms]
    os.chdir(f)
    # Get forces
    fq = os.popen('grep FORCES: OUTCAR | tail -1')
    fmax = 0
    for line in fq:
        fields = line.split()
        fmax = fields[4]

    maxforces.append(fmax)

    # Get energies
    o = open('./OUTCAR')
    alllines = o.readlines()
    o.close()
    n = len(alllines)
   
    for i in reversed(range(n)):
        line = alllines[i]
        if 'energy(sigma->0)' in line:
            break
    fields = line.split()
    energies.append(fields[-1])


    # Go back to main directory
    os.chdir(cwd)

energies =np.array(energies)
energies = energies.astype(float)
nenergies = energies - energies[0]
print('Image \t | FMax \t | Energy \t | Rel. En.')
print('----------------------------------------------------')
for i,f,e,ne in zip(folders,maxforces,energies,nenergies):
    print('{0} \t | {1:.4f} \t | {2:.4f} \t | {3:.4f}'.format(i,float(f),e,ne))
view(traj)
