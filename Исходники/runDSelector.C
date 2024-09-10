void runDSelector() 
{
    // $(ROOT_ANALYSIS_HOME)/scripts/Load_DSelector.C
    gSystem->AddIncludePath("-I${HALLD_HOME}/${BMS_OSNAME}/include/");
    gSystem->AddIncludePath("-I${ROOT_ANALYSIS_HOME}/${BMS_OSNAME}/include/");
    gSystem->Load("$(ROOT_ANALYSIS_HOME)/$(BMS_OSNAME)/lib/libDSelector.so");

    // load the tree
    TChain *chain = new TChain("pippim_Tree");
    chain->Add("tree_pippim.root");
    // and run it
    chain->Process("DSelector_piDelta.C+", "");

}