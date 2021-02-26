# amber-prm-pilot-run

A simple `Geant4` application to simulate features of the backup solution
for an AMBER PRM pilot run.

## Software setup

This project is tested with `conda` package solution.
First one have to setup and configure `conda`:
```bash
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh
conda config --add channels conda-forge
```

Second create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```

Third step is to clone and build `amber-prm-pilot-run` application
```bash
cd # you may want to choose other directory
git clone https://github.com/aleksha/amber-prm-pilot-run.git
cd amber-prm-pilot-run
mkdir build
cd build
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../source
make
```
As a result an `exec_MUP` application should be compiled. 
You can run it directly from `build/` deirecory or create a specila 
`run/` place:
```bash
mkdir ../run
cp exec_MUP run.mac ../run
cd ../run
./exec_MUP run.mac >> inLOG
```
