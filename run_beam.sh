mkdir run_beam
cp build_beam/exec_MUP build_beam/run.mac build_beam/seed run_beam/
cd run_beam
./exec_MUP run.mac >> inLOG
