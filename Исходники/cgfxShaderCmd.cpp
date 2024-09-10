MStatus
cgfxShaderCmd::doCmd(const MArgList& args)
//
//	Description:
//		implements the MEL cgfxShader command.
//
//	Arguments:
//		-fx/fxFile	The CgFX file to load.
//		-e/edit		Edit an existing cgfxShader rather than creating
//					a new one.
//      -q/query    Get specified info
//
//	Return Value:
//		MS::kSuccess - command succeeded
//		MS::kFailure - command failed (returning this value will cause the 
//                     MEL script that is being run to terminate unless the
//                     error is caught using a "catch" statement.
//
{
	// Get the current state of the flag
	// and store it in a temporary variable
	// static int tmpFlag = -1;

#if defined(_WIN32) && defined(CGFX_DEBUG_MEMORY)
	if (tmpFlag == -1)
	{
		tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

		// Turn On (OR) - call _CrtCheckMemory at every
		// allocation request
		tmpFlag |= _CRTDBG_CHECK_ALWAYS_DF;

		// Turn on (OR) - check for memory leaks at end
		// of program.
		tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

		_CrtSetDbgFlag( tmpFlag );
	}
#endif /* _WIN32 && CGFX_DEBUG_MEMORY */

	MStatus        status;
	MSelectionList selList;
	MObject        oNode;
	MString        sResult;
	MStringArray   saResult;
	MString        sFeedback;
	MString        sTemp;
	MString        sWho = "cgfxShader : ";

	status = parseArgs(args, selList);
	if (!status)
	{
		return status;
	}

	// -pp / -pluginPath 
	//     Returns the directory path where this plug-in's auxiliary
	//     files, such as MEL scripts, are expected to be found.
	//     The path name is in Maya format ('/' delimited) with no
	//     trailing slash.  Result type is string.  (Query only)
	if ( fPluginPath )
	{
		setResult( sPluginPath );
		return MS::kSuccess;
	}

	// -lp / -listProfiles
    //  
	//     Return the names of the profiles supported on the current
	//     platform.
	//
	//     Each item in the result array has the form
	//         "VertexProfileName<,GeometryProfileName,FragmentProfileName"
	//
	//     Result type is string[].  (Query only; set internally)
	if ( fListProfiles )
	{
        setResult( cgfxProfile::getProfileList() );
		return status;
	}

	// -mtc / -maxTexCoords
	//     Returns the maximum number of texcoord inputs that can be
	//     passed to vertex shaders under the currently installed
	//     OpenGL implementation.  Returns 0 if the information is
	//     not available.  Result type is integer.  (Query only)
	//
	// Don't use GL_MAX_TEXTURE_UNITS as this does not provide a proper
	// count when the # of image or texcoord inputs differs
	// from the conventional (older) notion of texture unit. 
	//
	// Instead take the minimum of GL_MAX_TEXTURE_COORDS_ARB and
	// GL_MAX_TEXUTRE_IMAGE_UNITS_ARB according to the 
	// ARB_FRAGMENT_PROGRAM specification.
	if ( fMaxTexCoords )    
	{
		GLint     mtc = 0;
		M3dView vw = M3dView::active3dView( &status );
		if ( status &&
			vw.beginGL() )
		{
			glGetIntegerv( GL_MAX_TEXTURE_COORDS_ARB, &mtc );
			GLint mic = 0;
			glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &mic );
			if (mic < mtc)
				mtc = mic;

			if ( mtc < 1 )
				mtc = 1;
			else if ( mtc > CGFXSHADERNODE_GL_TEXTURE_MAX )
				mtc = CGFXSHADERNODE_GL_TEXTURE_MAX;
			
			vw.endGL();
		}
		setResult( (int)mtc );
		return MS::kSuccess;
	}

	// If edit or query, find the specified cgfxShaderNode.
	MFnDependencyNode fnNode;
	cgfxShaderNode*   pNode = NULL;
	if ( fIsEdit || fIsQuery )
	{
		// We are editing an existing node which must have been
		// provided in the args (or the current selection list).
		// Get the correct node name into fNodeName;
		//
		if (selList.length() != 1)
		{
			status = MS::kNotFound;
			return status;
		}

		// Get the name of the node into fNodeName so that it can
		// be saved for undo/redo
		//
		MStringArray tmpList;
		selList.getSelectionStrings(tmpList);
		fNodeName = tmpList[0];
		if ( fNodeName.length() ) 
		{
			sWho += " \"";
			sWho += fNodeName;
			sWho += "\"";
		}

		status = selList.getDependNode(0, oNode);
		if (!status)
		{
			return status;
		}

		status = fnNode.setObject( oNode );
		if (!status)
		{
			sFeedback = sWho;
			sFeedback += " is not a cgfxShader node.";
			MGlobal::displayError( sFeedback );

			return status;
		}

		if (fnNode.typeId() != cgfxShaderNode::sId)
		{
			status = MS::kInvalidParameter;
			sFeedback = sWho;
			sFeedback += " is not a cgfxShader node.";
			MGlobal::displayError( sFeedback );
			return status;
		}

		pNode = (cgfxShaderNode*)fnNode.userNode();
		if (!pNode)
		{
			status = MS::kInvalidParameter;
			sFeedback = sWho;
			sFeedback += " is not cgfxShader node.";
			MGlobal::displayError( sFeedback );
			return status;
		}
	}

	if ( fIsQuery ) {
        
        // -fx / -fxFile
        //     Returns the shader file name. 
        if ( fFxFile )
        {
            MString path = pNode->shaderFxFile();
            setResult( path );
            return MS::kSuccess;
        }

        // -fxp / -fxPath 
        //     Returns the path of the fx file.  The path name is in Maya
        //     format ('/' delimited).  Result type is string.
        //     (Query only)
        if ( fFxPath )
        {
            MString path = cgfxFindFile(pNode->shaderFxFile());
            setResult( path );
            return MS::kSuccess;
        }

        // -t / -technique
        //     Returns the currently active technique
        if ( fTechnique )
        {
            MString path = pNode->getTechnique();
            setResult( path );
            return MS::kSuccess;
        }

        // -p / -profile
        //     Returns the current profile
        if ( fProfile )
        {
            MString path = pNode->getProfile();
            setResult( path );
            return MS::kSuccess;
        }

        // -lt / -listTechniques
        //     Return the technique names defined by the current effect.
        //
        //     Each item in the result array has the form
        //         "techniqueName<TAB>numPasses"
        //     where 
        //         numPasses is the number of passes defined by the 
        //             technique, or 0 if the technique is not valid.   
        //     (Future versions of the cgfxShader plug-in may append
        //      additional tab-separated fields.)
        //
        //     Result type is string[].  (Query only; set internally)
        if ( fListTechniques )
        {
            setResult( pNode->getTechniqueList() );
            return status;
        }

        // -lp / -listParameters
        //     Return the attribute names corresponding to the
        //     shader's tweakable uniform parameters.
        //     Result type is string[].  (Query only; set internally)
        // -des / -description
        //     If specified, each item in the result array has the form
        //          "attrName<TAB>type<TAB>semantic<TAB>description<TAB>extraAttrSuffix"
        //     (Future versions of the cgfxShader plug-in may provide
        //       additional tab-separated fields after the semantic.)
        //     A missing field is indicated by a single space (" ") 
        //       so the string can be parsed more easily using the MEL
        //       "tokenize" function, which treats a group of consecutive
        //       delimiters the same as a single delimiter.
        if ( fListParameters )
        {
            cgfxRCPtr<cgfxAttrDefList> list = cgfxAttrDef::attrsFromNode( oNode );
            for ( cgfxAttrDefList::iterator it = list; it; ++it )
            {
                cgfxAttrDef* aDef = *it;
                if ( fDescription )
                {
                    sResult = aDef->fName.length() ? aDef->fName : " ";
                    sResult += "\t";
                    sTemp = aDef->typeName();
                    sResult += sTemp.length() ? sTemp : " ";
                    sResult += "\t";               
                    sResult += aDef->fSemantic.length() ? aDef->fSemantic : " ";
                    sResult += "\t";
                    sResult += aDef->fDescription.length() ? aDef->fDescription : " ";
                    sResult += "\t";               
                    const char* suffix = aDef->getExtraAttrSuffix();
                    sResult += suffix ? suffix : " ";
                }
                else
                    sResult = aDef->fName;
                saResult.append( sResult );
            }
            setResult( saResult );
            return status;
        }

        // -p  / -parameter <name>
        //     Return a string describing the data type and usage of 
        //     the attribute whose name is specified.  
        //     Result type is string (with no -description flag), or
        //     string array (if you specify -description).  
        //     (Query only; set internally)
        // -ci / -caseInsensitive
        //     If specified, returns information for the first 
        //     attribute that matches the specified name assuming
        //     no distinction between upper and lower case letters.
        // -des / -description
        //     If specified, the result is a string array containing:
        //          [0] = attribute name
        //          [1] = type
        //          [2] = semantic 
        //          [3] = description from "desc" or "uiname" annotation
        //          [4] = extra attribute suffix for Vector4 ("W") / Color4 ("Alpha")
        //          (Future versions of the cgfxShader plug-in may provide
        //          additional tab-separated fields after the semantic.)
        //     If omitted, only the type is returned (a string).
        if ( fParameterName.length() > 0 )
        {
            cgfxRCPtr<cgfxAttrDefList> list = cgfxAttrDef::attrsFromNode( oNode );
            cgfxAttrDefList::iterator it; 
            if ( fCaseInsensitive )
                it = list->findInsensitive( fParameterName );
            else
                it = list->find( fParameterName );
            if ( fDescription )
            {
                if ( it )
                {
                    cgfxAttrDef* aDef = *it;
                    saResult.append( aDef->fName );
                    saResult.append( aDef->typeName() );
                    saResult.append( aDef->fSemantic );
                    saResult.append( aDef->fDescription );
                    const char* suffix = aDef->getExtraAttrSuffix();
                    saResult.append( suffix ? suffix : "" );
                }
                setResult( saResult );
            }
            else
            {
                if ( it )
                    sResult = (*it)->typeName();
                setResult( sResult );
            }
            return status;
        }

        // -euv / -emptyUV
        //     Returns the names of blacklisted UV sets.  These UV sets
        //     are disabled from being passed to the shader because there
        //     is at least one mesh where the UV set name is defined but 
        //     has no faces mapped.  Due to a bug in Maya (in 5.0 and
        //     possibly some other releases), Maya crashes if an empty
        //     UV set is accessed by a hardware shader.  Blacklisting is
        //     intended to protect the user against accidentally hitting
        //     the bug and crashing Maya.  After the Maya fix has been
        //     verified, this option can continue to be accepted for awhile
        //     for compatibility, returning an empty result array.
        //     Result type is string[].  (Query only; set internally)
        if ( fEmptyUV )
        {
            setResult( pNode->getEmptyUVSets() );
            return MS::kSuccess;
        }

        // -eus / -emptyUVShapes
        //     Returns the names of shape nodes that have empty UV sets 
        //     which are causing the UV set names to be blacklisted.
        //     After the Maya bug fix has been verified, this option
        //     can remain for awhile for compatibility, returning an
        //     empty result array.
        //     Result type is string[].  (Query only; set internally)
        if ( fEmptyUVShapes )
        {
            const MObjectArray& oaShapes = pNode->getEmptyUVSetShapes();
            MFnDagNode          fnDagNode;
            MDagPath            dpShape;
            for ( unsigned iShape = 0; iShape < oaShapes.length(); ++iShape )
            {
                fnDagNode.setObject( oaShapes[ iShape ] );
                fnDagNode.getPath( dpShape );
                saResult.append( dpShape.partialPathName() );
            }
            setResult( saResult );
            return MS::kSuccess;
        }

        // -tcs / -texCoordSource
        //     Returns the value of the texCoordSource attribute, because
        //     the MEL "getAttr" command doesn't work with string arrays.
        //     Result type is string[].  (Query only; set via "setAttr")
        if ( fTexCoordSource )
        {
            setResult( pNode->getTexCoordSource() );
            return MS::kSuccess;
        }

#if MAYA_API_VERSION >= 700

        // -cs / -colorSource
        //     Returns the value of the colorSource attribute, because
        //     the MEL "getAttr" command doesn't work with string arrays.
        //     Result type is string[].  (Query only; set via "setAttr")
        if ( fColorSource )
        {
            setResult( pNode->getColorSource() );
            return MS::kSuccess;
        }

#endif

        // Error if -q with no other query flags.
		return MS::kInvalidParameter;
    }

	// If user didn't specify shader fx file, default to current
	// value of our cgfxShader node's "shader" attribute.
	if (!fFxFile && pNode)
		fNewFxFile = pNode->shaderFxFile();

	// If user didn't specify technique name, default to current
	// value of our cgfxShader node's "technique" attribute.
    //
    // If a new fx file has been specified without a technique, we
    // leave the technique name empty so that the first technique of
    // the effect will be selected.
	if (!fTechnique && pNode)
		fNewTechnique = pNode->getTechnique();

	// If user didn't specify profile name, default to current
	// value of our cgfxShader node's "profile" attribute.
	if (!fProfile && pNode)
		fNewProfile = pNode->getProfile();

	//
	// Load the effect from the .fx file.
	//
	if (fFxFile)
	{
		// Attempt to read the new fEffect from the file
		//
		MString file = cgfxFindFile(fNewFxFile);
        MString projectFile = cgfxFindFile(fNewFxFile, true);

		// Compile and create the effect.
		fNewEffect = cgfxEffect::loadEffect(file, cgfxProfile::getProfile(fNewProfile));

		//// Set the device.
		if (fNewEffect->isValid())
		{           
			// There is no current view in batch mode, just return
			// success then
			const MGlobal::MMayaState mayaState = MGlobal::mayaState(&status);
			if ( !status ) return status;
			if ( mayaState == MGlobal::kBatch ) return MS::kSuccess;

			fNewFxFile = projectFile;

			M3dView view = M3dView::active3dView();

			// The M3dView class doesn't return the correct status if
			// there isn't an active 3D view, so we rely on the
			// success of beginGL() which will make the context
			// current.
			//
			if (!view.beginGL()) 
			{
				MString es = "There is no active view to bind " + sWho + " to.";
				MGlobal::displayWarning( es );
				return MS::kSuccess;
			}

			view.endGL();
		}

		// Tell user if successful.
		if (fNewEffect->isValid())
		{
			sFeedback = sWho;
			sFeedback += " loaded effect \"";
			sFeedback += file;
			sFeedback += "\"";
			MGlobal::displayInfo( sFeedback );
		}
		else
		{
			sFeedback = sWho;
			sFeedback += " unable to load effect \"";
			sFeedback += file.length() ? file : fNewFxFile;
			sFeedback += "\"";
			MGlobal::displayError( sFeedback );
			return MS::kFailure;
		}
	}

	// Create an MDGModifier to hold an agenda of operations to be
	//   performed to update the DG.  We build the agenda here;
	//   then invoke it to do/redo/undo the updates.
	fDagMod = new MDGModifier;

	// Create new cgfxShader node if requested.  
	if ( !fIsEdit )
	{
		// Create node.
		oNode = fDagMod->createNode(cgfxShaderNode::sId, &status);
		M_CHECK( status );

		if ( fNodeName.length() > 0 )
		{
			status = fDagMod->renameNode(oNode, fNodeName);
			M_CHECK( status );
		}

		status = fnNode.setObject( oNode );
		M_CHECK( status && fnNode.typeId() == cgfxShaderNode::sId );

		pNode = (cgfxShaderNode*)fnNode.userNode();
		M_CHECK( pNode );

		// On successful completion, redoCmd() will select the new node.
		// Save old selection for undo.
		status = MGlobal::getActiveSelectionList( fOldSelection );
		M_CHECK( status );
	}

	if (fFxFile) {
        // Save the current state of the node for undo purposes
        fOldFxFile    = pNode->shaderFxFile();
        fOldEffect = pNode->effect();   // save old CGeffect

		cgfxShaderNode::NodeList nodes;
		// getNodesToUpdate will return the list of nodes that will need to be updated :
		// if the new fx file is the same as the old fx file, the action is considered a reload,
		//     we'll gather all the nodes that are using the old effect and reload them all.
		// else the effect file is different and only the current node will be updated.
		getNodesToUpdate(fOldEffect, pNode, nodes);

		cgfxShaderNode::NodeList::const_iterator it = nodes.begin();
		cgfxShaderNode::NodeList::const_iterator itEnd = nodes.end();
		for(; it != itEnd; ++it)
		{
			cgfxShaderNode* node = *it;

			MStringArray &oldAttributeList = fOldAttributeList[node];
			cgfxRCPtr<cgfxAttrDefList> &oldAttrDefList = fOldAttrDefList[node];

			MStringArray &newAttributeList = fNewAttributeList[node];
			cgfxRCPtr<cgfxAttrDefList> &newAttrDefList = fNewAttrDefList[node];


			node->getAttributeList( oldAttributeList );

			oldAttrDefList = node->attrDefList(); // save old cgfxAttrDefList ptr

			// Now figure out what to do with the node.
			//
			// updateNode does a fair amount of work.  First, it gets the
			// cgfxAttrDefList from the effect.  Then it gets the equivalent
			// list from the node itself.  It determines which attributes need
			// to be added and which need to be deleted and fills in all the
			// changes in the MDagModifier fDagMod.  Then it builds a new value
			// for the attributeList attribute.  Finally, it builds a new
			// value for the attrDefList internal value.  All these values are
			// returned here where we can set them into the node.
			//
			cgfxAttrDef::updateNode( fNewEffect,             // IN
									 node,                   // IN
									 fDagMod,                // UPD
									 newAttrDefList,         // OUT
									 newAttributeList );     // OUT
		}
    }

	// Save a reference to the node in a selection list for undo/redo.
	status = fNodeSelection.add( oNode );
	M_CHECK( status );

	// Save the current state of the node for undo purposes
	fOldTechnique = pNode->getTechnique();
	fOldProfile   = pNode->getProfile();

	// I think we have all the information to redoIt().
	//
	// Typically, the doIt() method only collects the infomation required
	// to do/undo the action and then stores it in class members.  The 
	// redo method is then called to do the actuall work.  This prevents
	// code duplication.
	//
	return redoCmd( oNode, fnNode, pNode );
}                                      // cgfxShaderCmd::doCmd