mkdir run_scat
cp -v scattering/scat_input.txt run_scat/input_g4.txt
cp -v build_g4/exec_MUP run_scat/
cp -v configs/mac/run_scat.mac run_scat/run.mac
cp -v configs/seeds/seed_scat run_scat/seed
cd run_scat
echo "Starting scat lepton tracingp"
./exec_MUP run.mac >> inLOG
echo "Done! (see inLOG for details)"
