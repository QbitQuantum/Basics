//------------------------------------------------------------------------------
// Method: ExtendBridge
//
// Description: Constructor.
//
// Return:
//		none
//
//------------------------------------------------------------------------------
ExtendBridge::ExtendBridge() {
	// initialize the OLE
	OleInitialize(NULL);

    pExtendDisp = NULL;
    extendPath = NULL;

    //
    // Standard libraries (libraries usually required by SEI models)
    // 
    libraries.insert(StringPair(SEI_LIB, "SEI-2.lix"));
    libraries.insert(StringPair(BPR_LIB, "BPR.lix"));
    libraries.insert(StringPair(UTILITIES_LIB, "Utilities.lix"));
    libraries.insert(StringPair(DISCRETE_LIB, "Discrete Event.lix"));
    libraries.insert(StringPair(GENERIC_LIB, "Generic.lix"));
    libraries.insert(StringPair(PLOTTER_LIB, "Plotter.lix"));
}