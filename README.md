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

Second, create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```

Third, create envoirment for `ESEPP`, `ROOT` and `OstapHEP`.
To setup enviorment, please, follow this: https://github.com/aleksha/pres-mc 

# ESEPP preparation

It's better to use automatic config version for the `ESEPP`.
```bash
git clone https://github.com/nuramatov/esepp.git
cd esepp
make
```
Edit `config.ini` and run it:
```bash
cp ../configs/cinfig.esepp config.ini
python start.py config.ini
```

## Beam noise

Next step is to clone and build `amber-prm-pilot-run` application
```bash
cd # you may want to choose other directory
git clone https://github.com/aleksha/amber-prm-pilot-run.git
cd amber-prm-pilot-run
mkdir build_beam
cd build_beam
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../source
make -j4
```
As a result an `exec_MUP` application should be compiled.
It uses an input (called `rand_input.txt`), which must be created.
Follow instructions in `beamfile/README.md`.

You can run it directly from `build_beam/` deirecory or create a specila 
`run/` place:
```bash
mkdir ../run_beam
cp exec_MUP run.mac seed ../run_beam
cd ../run_beam
./exec_MUP run.mac >> inLOG
```
One can use `build_beam.sh` and `run_beam.sh` scripts.

## Electronic noise

See information in the `noise` directory.
The speeded-up version is in use.
