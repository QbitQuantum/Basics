//-----------------------------------------------------------------------------
// Returns the vsSkinner node if the passed node is connected to a vsSkinner node
//-----------------------------------------------------------------------------
MStatus CVsSkinnerCmd::ConnectedToSkinnerNode(
	const MDagPath &iDagPath,
	MDagPath &oDagPath )
{
	MPlugArray pA;
	MPlugArray pA1;

	if ( MFnDagNode( iDagPath ).getConnections( pA ) && pA.length() )
	{
		MObject mObj;

		const uint np( pA.length() );
		for ( uint i( 0U ); i != np; ++i )
		{
			if ( pA[ i ].connectedTo( pA1, true, true ) && pA1.length() )
			{
				const uint np1( pA1.length() );
				for ( uint j( 0U ); j != np1; ++j )
				{
					mObj = pA1[ j ].node();

					if ( IsSkinnerNode( mObj ) )
					{
						MDagPath::getAPathTo( mObj, oDagPath );
						return MS::kSuccess;
					}
				}
			}
		}
	}

	return MS::kFailure;
}