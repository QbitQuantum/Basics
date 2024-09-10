// You declared this function in the extern "C" block of the header.
// R will call this function to drive the processing of the Tree/Chain.
// Except for the name of your class (in this case met), your 
// function should look identical to the below... 
SEXP metToR(SEXP manager, SEXP nEntriesR, SEXP firstEntryR,
	    SEXP initialSizeR, SEXP growthFactorR, SEXP argsR)
{

  try {
    // Pull out the arguments
    Long64_t nEntries = INTEGER(nEntriesR)[0];
    Long64_t firstEntry = INTEGER(firstEntryR)[0];
    int initialSize = INTEGER(initialSizeR)[0];
    double growthFactor = REAL(growthFactorR)[0];

    // Get the Root chain manager
    checkForRootChainManagerPtr(manager);
    RootChainManager* rcm = (RootChainManager*) R_ExternalPtrAddr(manager);
    
    bool verbose = rcm->getVerbose();
    
    // Get the chain we wish to deal with
    TChain* tree = rcm->tree();
    
    // Create the TSelector (replace Met with your class name)
    Met stor(initialSize, growthFactor, verbose, tree->GetTreeOffset() );
                             
    // Process it!
    tree->Process(&stor, "", nEntries, firstEntry);
      
    // Return the data frame
    return stor.rDataFrame();
  }

  catch ( RDataFrameException e ) {
    error(e.what().c_str());
    return 0;
  }
}