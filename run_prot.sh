mkdir run_prot
cp -v scattering/prot_input.txt run_prot/input_g4.txt
cp -v build_g4/exec_MUP run_prot/
cp -v configs/mac/run_prot.mac run_prot/run.mac
cp -v configs/seeds/seed_prot run_prot/seed
cd run_prot
echo "Starting prot lepton tracingp"
./exec_MUP run.mac >> inLOG
echo "Done! (see inLOG for details)"
