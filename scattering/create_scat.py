#===============================================================================
EVENTS   = 11000
USE_CORE = True
#===============================================================================
rfile = ROOT.TFile('../beamfile/beamfile_prm_mu100.root', "READ")
rfile.ls()
tree = rfile["BeamFile"]
#===============================================================================
efile = ROOT.TFile("../esepp/\"events\"_mu-.root", "READ")
efile.ls()
ntp = efile["ntp"]
#===============================================================================
ev     = 0
length = len( tree )
in_list = []
while ev<EVENTS:
    tree.GetEntry( ROOT.gRandom.Integer(length) )
    if USE_CORE:
        while tree.particleFlag!=2:
            tree.GetEntry( ROOT.gRandom.Integer(length) )
    in_list.append( (13, tree.X, tree.Y, -6299., tree.dXdZ*0.001, tree.dYdZ*0.001 ) )
    ev+=1
#===============================================================================
for e in in_list:
    
