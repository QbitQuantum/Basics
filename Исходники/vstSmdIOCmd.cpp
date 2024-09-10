//-----------------------------------------------------------------------------
// Purpose: Export the specified bits of the maya scene into the specified file
// Input  : i_mArgDatabase	The command line arguments as passed
// Output : MS::kSuccess if ok, MS::kFailure otherwise
//-----------------------------------------------------------------------------
MStatus CVstSmdIOCmd::DoExport(
	const MArgDatabase &mArgDatabase )
{
	MString optFilename;
	if ( mArgDatabase.getFlagArgument( kOptFilename, 0, optFilename ) != MS::kSuccess || optFilename.length() == 0 )
	{
		MGlobal::displayError( "No filename specified for export" );
		return MS::kFailure;
	}

	MSelectionList optSelectionList;
	if ( GetOptSelection( mArgDatabase, optSelectionList ) != MS::kSuccess )
		return MS::kFailure;

	const uint exportType( GetExportType( mArgDatabase ) );

	const uint exportFlags( GetExportFlags( mArgDatabase ) );

	const uint version(
		mArgDatabase.isFlagSet( kOptRelativeMaterials ) &&
		exportType & ( CSmdExport::kModel | CSmdExport::kPhysModel | CSmdExport::kVertexAnimation ) ? 2 : 1 );

	CSmdExport smdExport( exportType, exportFlags, version );

	smdExport.SetNodeAddPrefix( GetNodeAddPrefix( mArgDatabase ) );
	smdExport.SetNodeDelPrefix( GetNodeDelPrefix( mArgDatabase ) );

	if ( exportType & CSmdExport::kAnimation )
	{
		double fs( 0.0 );
		double fe( 0.0 );
		double fi( 1.0 );

		GetExportFrameRange( mArgDatabase, fs, fe, fi );

		smdExport.SetFrameRange( fs, fe, fi );
	}

	MStringArray result;

	if ( smdExport.DoIt( optFilename, optSelectionList, result ) != MS::kSuccess )
		return MS::kFailure;

	if ( result.length() )
	{
		result.append( "smd" );
		result.append( optFilename );
	}
	else
	{
		result.append( MString( "Exported to " ) + optFilename );
	}

	if ( mArgDatabase.isFlagSet( kOptQci ) )
	{
		MString optQci;
		mArgDatabase.getFlagArgument( kOptQci, 0, optQci );
		MSelectionList qciSelectionList;
		if ( mArgDatabase.isFlagSet( kOptSelection ) )
		{
			mArgDatabase.getObjects( qciSelectionList );
		}

		MStringArray qciResult;
		CQciExport qciExport;
		if ( qciExport.DoIt( optQci, qciSelectionList, qciResult ) && qciResult.length() )
		{
			for ( uint i( 0 ); i != qciResult.length(); ++i )
			{
				result.append( qciResult[ i ] );
			}
		}
	}

	setResult( result );

	return MS::kSuccess;
}