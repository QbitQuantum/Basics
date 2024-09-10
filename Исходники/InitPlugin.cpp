//! Initialize plugin for LaplacianSmoother.
MStatus initializePlugin ( MObject obj )
{
    MStatus status;
    MFnPlugin plugin ( obj, "Tody", "1.0", "Any" );
    status = plugin.registerNode ( LaplacianSmoother::getMayaName(), LaplacianSmoother::id, LaplacianSmoother::creator,
                                   LaplacianSmoother::initialize,  MPxNode::kDeformerNode );

    if ( !status )
    {
        status.perror ( "initialized plug-in" );
        status.perror ( status.errorString( ) );
    }

    return status;
}