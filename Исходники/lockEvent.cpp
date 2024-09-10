MStatus lockEvent::parseArgs( const MArgList &args )
{
	MStatus status; 
	MArgDatabase argData( syntax(), args ); 
	
	fAttach = kAttachDV; 
	fOverrideFlag = kOverrideDV; 
	fClearCB = kClearCBDV; 

	// begin-parse-args 

	if ( argData.isFlagSet( kClearCB ) ) { 
		fClearCB = !kClearCBDV; 
 	} 	

	if ( argData.isFlagSet( kOverride ) ) { 
		bool tmp;
		status = argData.getFlagArgument( kOverride, 0, tmp ); 
		if ( !status ) { 
			MGlobal::displayError( "override flag parsing failed" ); 
			return status;
		}
		fOverrideFlag = !kOverrideDV; 
		fOverrideVal = tmp; 
	}

	if ( argData.isFlagSet( kAttach ) ) { 
		unsigned int tmp;
		status = argData.getFlagArgument( kAttach, 0, tmp ); 
		if ( !status ) { 
			MGlobal::displayError( "attach flag parsing failed" ); 
			return status;
		}
		fAttach = tmp; 
	} 

	if ( fAttach ) { 
		status = argData.getObjects( theList ); 
		if ( theList.length() == 0 ) { 
			MString msg = "You must specify a node/plug to attach to!"; 
			MGlobal::displayError(msg); 
			status = MS::kFailure; 
		}
	}

	// Ensure that the caller did not specify too many arguments! 
	//
	if ( status && fAttach && fOverrideFlag ) { 
		MString msg = "You specified too many flags!" ;
		MGlobal::displayError(msg);  
		status = MS::kFailure; 
	} 
	
	// end-parse-args 
	
	return status; 
}