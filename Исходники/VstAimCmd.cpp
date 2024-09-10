MStatus CVstAimCmd::redoIt()
{
	MStatus mStatus;

	if ( !mStatus )
	{
		setResult( MString( "Cannot parse command line" ) + mStatus.errorString() );
		return MS::kFailure;
	}

	if ( m_mArgDatabase->isFlagSet( kHelp ) )
	{
		PrintHelp();
	}
	else
	{
		// See if there are two object specified

		MDagPath mDagPath;
		MSelectionList optSelectionList;

		// Validate specified items to whole dag nodes
		{
			MSelectionList tmpSelectionList;
			m_mArgDatabase->getObjects( tmpSelectionList );
			for ( MItSelectionList sIt( tmpSelectionList, MFn::kDagNode ); !sIt.isDone(); sIt.next() )
			{
				if ( sIt.getDagPath( mDagPath ) )
				{
					optSelectionList.add( mDagPath, MObject::kNullObj, true );
				}
			}
		}

		if ( m_mArgDatabase->isFlagSet( "create" ) || optSelectionList.length() >= 2 && m_mArgDatabase->numberOfFlagsUsed() == 0 )
		{
			// Error if there aren't at least two
			if ( optSelectionList.length() < 2 )
			{
				displayError( GetName() + " needs at least two objects specified or selected when -create is used" );
				return MS::kFailure;
			}

			// Get name command line arg
			MString optName;
			if ( m_mArgDatabase->isFlagSet( "name" ) )
			{
				m_mArgDatabase->getFlagArgument( "name", 0, optName );
			}

			m_undoable = true;
			m_mDagModifier = new MDagModifier;

			MObject vstAimObj( m_mDagModifier->MDGModifier::createNode( GetName() ) );
			if ( m_mDagModifier->doIt() != MS::kSuccess )
			{
				displayError( MString( "Couldn't create " ) + GetName() + " node" );
				m_mDagModifier->undoIt();
				delete m_mDagModifier;
				m_mDagModifier = NULL;
				m_undoable = false;

				return MS::kFailure;
			}

			m_mDagModifier->renameNode( vstAimObj, optName.length() ? optName : GetName() );
			if ( m_mDagModifier->doIt() != MS::kSuccess )
			{
				if ( optName.length() )
				{
					displayWarning( MString( "Couldn't rename newly created vstNode \"" ) + optName + "\"" );
				}
			}

			// Set options on the newly create vstAim node

			MFnDependencyNode vstAimFn( vstAimObj );

			MPlug sP;
			MPlug dP;

			if ( m_mArgDatabase->isFlagSet( kAim ) )
			{
				MVector aim;
				m_mArgDatabase->getFlagArgument( kAim, 0, aim.x );
				m_mArgDatabase->getFlagArgument( kAim, 1, aim.y );
				m_mArgDatabase->getFlagArgument( kAim, 2, aim.z );

				sP = vstAimFn.findPlug( "aimX" );
				sP.setValue( aim.x );

				sP = vstAimFn.findPlug( "aimY" );
				sP.setValue( aim.y );

				sP = vstAimFn.findPlug( "aimZ" );
				sP.setValue( aim.z );
			}

			if ( m_mArgDatabase->isFlagSet( kUp ) )
			{
				MVector up;
				m_mArgDatabase->getFlagArgument( kUp, 0, up.x );
				m_mArgDatabase->getFlagArgument( kUp, 1, up.y );
				m_mArgDatabase->getFlagArgument( kUp, 2, up.z );

				sP = vstAimFn.findPlug( "upX" );
				sP.setValue( up.x );

				sP = vstAimFn.findPlug( "upY" );
				sP.setValue( up.y );

				sP = vstAimFn.findPlug( "upZ" );
				sP.setValue( up.z );
			}

			// Now connect up the newly created vstAim node

			MDagPath toAim;
			optSelectionList.getDagPath( 1, toAim );
			const MFnDagNode toAimFn( toAim );

			if ( toAim.hasFn( MFn::kJoint ) )
			{
				MPlug joP( toAimFn.findPlug( "jointOrient" ) );
				if ( !joP.isNull() )
				{
					MAngle jox, joy, joz;
					joP.child( 0 ).getValue( jox );
					joP.child( 1 ).getValue( joy );
					joP.child( 2 ).getValue( joz );
					if ( abs( jox.value() ) > FLT_EPSILON || abs( joy.value() ) > FLT_EPSILON || abs( joz.value() ) > FLT_EPSILON )
					{
						mwarn << "Joint orient on node being constrained is non-zero ( " << jox.asDegrees() << " " << joy.asDegrees() << " " << joz.asDegrees() << " ), setting to 0" << std::endl;
						joP.child( 0 ).setValue( MAngle( 0.0 ) );
						joP.child( 1 ).setValue( MAngle( 0.0 ) );
						joP.child( 2 ).setValue( MAngle( 0.0 ) );
					}
				}
			}

			if ( toAim.hasFn( MFn::kTransform ) )
			{
				MPlug mP( toAimFn.findPlug( "rotateAxis" ) );
				if ( !mP.isNull() )
				{
					MAngle rx, ry, rz;
					mP.child( 0 ).getValue( rx );
					mP.child( 1 ).getValue( ry );
					mP.child( 2 ).getValue( rz );
					if ( abs( rx.value() ) > FLT_EPSILON || abs( ry.value() ) > FLT_EPSILON || abs( rz.value() ) > FLT_EPSILON )
					{
						mwarn << "Rotate Axis on node being constrained is non-zero ( " << rx.asDegrees() << " " << ry.asDegrees() << " " << rz.asDegrees() << " ), setting to 0" << std::endl;
						mP.child( 0 ).setValue( MAngle( 0.0 ) );
						mP.child( 1 ).setValue( MAngle( 0.0 ) );
						mP.child( 2 ).setValue( MAngle( 0.0 ) );
					}
				}
			}

			MDagPath aimAt;
			optSelectionList.getDagPath( 0, aimAt );
			const MFnDagNode aimAtFn( aimAt );

			// toAim.rotateOrder -> vstAim.rotateOrder
			sP = toAimFn.findPlug( "rotateOrder" );
			dP = vstAimFn.findPlug( "rotateOrder" );
			m_mDagModifier->connect( sP, dP );

			// toAim.translate -> vstAim.translate
			sP = toAimFn.findPlug( "translate" );
			dP = vstAimFn.findPlug( "translate" );
			m_mDagModifier->connect( sP, dP );

			// toAim.parentMatrix[ instance ] -> vstAim.parentSpace
			sP = toAimFn.findPlug( "parentMatrix" );
			sP = sP.elementByLogicalIndex( toAim.instanceNumber() );
			dP = vstAimFn.findPlug( "parentSpace" );
			m_mDagModifier->connect( sP, dP );

			// aimAt.worldMatrix[ instance ] -> vstAim.aimSpace
			sP = aimAtFn.findPlug( "worldMatrix" );
			sP = sP.elementByLogicalIndex( aimAt.instanceNumber() );
			dP = vstAimFn.findPlug( "aimSpace" );
			m_mDagModifier->connect( sP, dP );

			// vstAim.rotation -> toAim.rotation
			// These have to be connected individually because Maya plays stupid tricks
			// with rotateOrder if they aren't
			sP = vstAimFn.findPlug( "rotateX" );
			dP = toAimFn.findPlug( "rotateX" );
			m_mDagModifier->connect( sP, dP );

			sP = vstAimFn.findPlug( "rotateY" );
			dP = toAimFn.findPlug( "rotateY" );
			m_mDagModifier->connect( sP, dP );

			sP = vstAimFn.findPlug( "rotateZ" );
			dP = toAimFn.findPlug( "rotateZ" );
			m_mDagModifier->connect( sP, dP );

			if ( m_mDagModifier->doIt() != MS::kSuccess )
			{
				displayWarning( MString( GetName() ) + ": Couldn't connect everything when creating" );
			}

			// Save the current selection just in case we want to undo stuff
			MGlobal::getActiveSelectionList( m_mSelectionList );

			MGlobal::select( vstAimObj, MGlobal::kReplaceList );
			setResult( vstAimFn.name() );
		}
		else if ( m_mArgDatabase->isFlagSet( "select" ) )
		{
			MSelectionList mSelectionList;
			MDagPath mDagPath;

			for ( MItDag dagIt; !dagIt.isDone(); dagIt.next() )
			{
				if ( MFnDependencyNode( dagIt.item() ).typeName() == GetName() )
				{
					dagIt.getPath( mDagPath );
					mSelectionList.add( mDagPath, MObject::kNullObj, true );
				}
			}

			if ( mSelectionList.length() )
			{
				m_undoable = true;
				// Save the current selection just in case we want to undo stuff
				MGlobal::getActiveSelectionList( m_mSelectionList );
				MGlobal::setActiveSelectionList( mSelectionList, MGlobal::kReplaceList );
			}
		}
		else
		{
			displayError( GetName() + ": No valid operation specified via command line arguments\n" );
		}
	}

	return MS::kSuccess;
}