    // ------------------------------------------------------------
    bool SceneGraph::create ( bool selectionOnly )
    {
        // The flag, if just the selected elements should be exported.
        mExportSelectedOnly = selectionOnly;

        // Add all the animation expressions
        MItDependencyNodes depIter ( MFn::kExpression );
        for ( ; !depIter.isDone(); depIter.next() )
        {
            MObject item = depIter.item();
            if ( item.hasFn ( MFn::kExpression ) )
            {
                mAnimationExpressions.append ( item );
            }
        }

        // Push all nodes from root down to all meshes which have to be exported in a list.
        findForcedNodes ();

        // Fills the list with all root targets to export.
        bool success = retrieveExportNodes ();
        
        // Create a selection list containing only the root nodes (implies export all!)
        uint length = mTargets.length();
        for ( uint i=0; i<mTargets.length(); ++i )
        {
            MDagPath dagPath;
            MStatus status = mTargets.getDagPath ( i, dagPath );
            if ( status != MStatus::kSuccess ) return false;

            // This node has no transform - i.e., it's the world node
            MObject transformNode = dagPath.transform ( &status );
            if ( !status && status.statusCode () == MStatus::kInvalidParameter ) continue;

            // Check if it is a valid transform node
            MFnDagNode transform ( transformNode, &status );
            if ( !status )
            {
                status.perror ( "MFnDagNode constructor" );
                return false;
            }

            // Create a new scene element
            SceneElement* sceneElement = createSceneElement ( dagPath );

            // Push the root nodes into the tree.
            // If the root node is instanced, push it at the beginning (no instance on root!).
            if ( dagPath.isInstanced () )
                mExportNodesTree.insert ( mExportNodesTree.begin (), sceneElement );
            else
                mExportNodesTree.push_back ( sceneElement );
            
            // Create the child elements
            //if ( sceneElement->getIsExportNode() )
            {
                createChildSceneElements ( sceneElement );
            }
        }

        return true;
    }