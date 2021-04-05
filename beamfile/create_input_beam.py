#===============================================================================
EVENTS   = 11000
USE_CORE = True
#===============================================================================
rfile = root_files['beamfile_prm_mu100']
rfile.ls()
tree = rfile["BeamFile"]
#tree.Print()
#===============================================================================
ev     = 0
length = len( tree )
out_file = open("rand_input.txt","w")
while ev<EVENTS:
    tree.GetEntry( ROOT.gRandom.Integer(length) )
    if USE_CORE:
        while tree.particleFlag!=2:
            tree.GetEntry( ROOT.gRandom.Integer(length) )
    ss  = "13 "
    ss += str(tree.X) + " "
    ss += str(tree.Y) + " "
    ss += "-6299.0 "
    ss += str(tree.dXdZ) + " "
    ss += str(tree.dYdZ) + " "
    ss += str(tree.P) + "\n"
    out_file.write( ss )
    ev+=1
#===============================================================================
