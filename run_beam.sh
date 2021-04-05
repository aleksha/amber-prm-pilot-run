mkdir run_beam
cp beamfile/rand_input.txt run_beam/input_g4.txt
cp build_g4/exec_MUP build_g4/run.mac build_g4/seed run_beam/
cd run_beam
./exec_MUP run.mac >> inLOG
