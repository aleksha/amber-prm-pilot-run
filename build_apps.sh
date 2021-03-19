rm -rf build
conda deactivate
conda activate g4-mc
mkdir build
cd build
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../source
make -j4
