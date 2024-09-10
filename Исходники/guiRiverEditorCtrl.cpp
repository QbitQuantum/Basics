void GuiRiverEditorCtrl::on3DMouseDown(const Gui3DMouseEvent & event)
{
   mGizmo->on3DMouseDown( event );

   if ( !isFirstResponder() )
      setFirstResponder();
	
	// Get the raycast collision position
   Point3F tPos;
   if ( !getStaticPos( event, tPos ) )
		return;  

   // Construct a LineSegment from the camera position to 1000 meters away in
   // the direction clicked.
   // If that segment hits the terrain, truncate the ray to only be that length.

   // We will use a LineSegment/Sphere intersection test to determine if a RiverNode
   // was clicked.   

   Point3F startPnt = event.pos;
   Point3F endPnt = event.pos + event.vec * 1000.0f;

   RayInfo ri;   

   if ( gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri) )
      endPnt = ri.point;

   River *riverPtr = NULL;
   River *clickedRiverPtr = NULL;

   // Did we click on a river? check current selection first
   U32 insertNodeIdx = -1;
   Point3F collisionPnt;
   if ( mSelRiver != NULL && mSelRiver->collideRay( event.pos, event.vec, &insertNodeIdx, &collisionPnt ) )
   {
      clickedRiverPtr = mSelRiver;
   }
   else
   {
      for ( SimSetIterator iter(mRiverSet); *iter; ++iter )
      {
         riverPtr = static_cast<River*>( *iter );
         if ( riverPtr->collideRay( event.pos, event.vec, &insertNodeIdx, &collisionPnt ) )
         {
            clickedRiverPtr = riverPtr;
            break;
         }
      }
   }

   // Did we click on a riverNode?
   bool nodeClicked = false;   
   S32 clickedNodeIdx = -1;
   F32 clickedNodeDist = mNodeSphereRadius;

   // If we clicked on the currently selected river, only scan its nodes
   if ( mSelRiver != NULL && clickedRiverPtr == mSelRiver )
   {
      for ( U32 i = 0; i < mSelRiver->mNodes.size(); i++ )
      {
         const Point3F &nodePos = mSelRiver->mNodes[i].point;

         Point3F screenPos;
         project( nodePos, &screenPos );

         F32 dist = ( event.mousePoint - Point2I(screenPos.x, screenPos.y) ).len();
         if ( dist < clickedNodeDist )
         {
            clickedNodeDist = dist;
            clickedNodeIdx = i;
            nodeClicked = true;
         }
      }
   }
   else
   {
      for ( SimSetIterator iter(mRiverSet); *iter; ++iter )
      {
         riverPtr = static_cast<River*>( *iter );
         
         for ( U32 i = 0; i < riverPtr->mNodes.size(); i++ )
         {
            const Point3F &nodePos = riverPtr->mNodes[i].point;

            Point3F screenPos;
            project( nodePos, &screenPos );

            F32 dist = ( event.mousePoint - Point2I(screenPos.x, screenPos.y) ).len();
            if ( dist < clickedNodeDist )
            {
               // we found a hit!
               clickedNodeDist = dist;
               clickedNodeIdx = i;
               nodeClicked = true;
               clickedRiverPtr = riverPtr;
            }
         }
      }
   }
	
	// shortcuts
	bool dblClick = ( event.mouseClickCount > 1 );
	if( dblClick )
   { 
		if( mMode == mSelectRiverMode )
		{
			setMode( mAddRiverMode, true );
			return;
		}
		if( mMode == mAddNodeMode )
		{
			// Delete the node attached to the cursor.
			deleteSelectedNode();
			mMode = mAddRiverMode;
			return;
		}
	}

	//this check is here in order to bounce back from deleting a whole road with ctrl+z
	//this check places the editor back into addrivermode
	if ( mMode == mAddNodeMode )
	{
      if ( !mSelRiver )
         mMode = mAddRiverMode;
	}

	if ( mMode == mSelectRiverMode )
	{
      // Did not click on a River or a node.
      if ( !clickedRiverPtr  )
      {
         setSelectedRiver( NULL );
         setSelectedNode( -1 );
         
         return;
      }

      // Clicked on a River that wasn't the currently selected River.
      if ( clickedRiverPtr != mSelRiver )
      {
         setSelectedRiver( clickedRiverPtr );
         setSelectedNode( clickedNodeIdx );
         return;
      }

     // Clicked on a node in the currently selected River that wasn't
      // the currently selected node.
      if ( nodeClicked )
      {
         setSelectedNode( clickedNodeIdx );
         return;
      }
	}
   else if ( mMode == mAddRiverMode )
   {
		if ( nodeClicked )
      {
			// A double-click on a node in Normal mode means set AddNode mode.  
         if ( clickedNodeIdx == 0 )
         {
				setSelectedRiver( clickedRiverPtr );
				setSelectedNode( clickedNodeIdx );

				mAddNodeIdx = clickedNodeIdx;
            mMode = mAddNodeMode; 

            mSelNode = mSelRiver->insertNode( tPos, mDefaultWidth, mDefaultDepth, mDefaultNormal, mAddNodeIdx );
            mIsDirty = true;

				return;
         }
			else if ( clickedNodeIdx == clickedRiverPtr->mNodes.size() - 1 )
         {
				setSelectedRiver( clickedRiverPtr );
				setSelectedNode( clickedNodeIdx );

            mAddNodeIdx = U32_MAX;
				mMode = mAddNodeMode;

            mSelNode = mSelRiver->addNode( tPos, mDefaultWidth, mDefaultDepth, mDefaultNormal);
            mIsDirty = true;
				setSelectedNode( mSelNode );

				return;
         } 
		}

		if ( !isMethod( "createRiver" ) )
      {
			Con::errorf( "GuiRiverEditorCtrl::on3DMouseDown - createRiver method does not exist." );
         return;
      }

      const char *res = Con::executef( this, "createRiver" );

      River *newRiver;
      if ( !Sim::findObject( res, newRiver ) )
      {
         Con::errorf( "GuiRiverEditorCtrl::on3DMouseDown - createRiver method did not return a river object." );
         return;
      }                

      // Add to MissionGroup                              
      SimGroup *missionGroup;
      if ( !Sim::findObject( "MissionGroup", missionGroup ) )               
         Con::errorf( "GuiRiverEditorCtrl - could not find MissionGroup to add new River" );
      else
         missionGroup->addObject( newRiver );

      Point3F pos( endPnt );
      pos.z += mDefaultDepth * 0.5f;

      newRiver->insertNode( pos, mDefaultWidth, mDefaultDepth, mDefaultNormal, 0 );
      U32 newNode = newRiver->insertNode( pos, mDefaultWidth, mDefaultDepth, mDefaultNormal, 1 );

      // Always add to the end of the road, the first node is the start.
      mAddNodeIdx = U32_MAX;
      
      setSelectedRiver( newRiver );      
      setSelectedNode( newNode );

      mMode = mAddNodeMode;

      // Disable the hover node while in addNodeMode, we
      // don't want some random node enlarged.
      mHoverNode = -1;

      // Grab the mission editor undo manager.
      UndoManager *undoMan = NULL;
      if ( !Sim::findObject( "EUndoManager", undoMan ) )
      {
         Con::errorf( "GuiMeshRoadEditorCtrl::on3DMouseDown() - EUndoManager not found!" );
         return;           
      }

      // Create the UndoAction.
      MECreateUndoAction *action = new MECreateUndoAction("Create MeshRoad");
      action->addObject( newRiver );

      // Submit it.               
      undoMan->addAction( action );

		return;
   }
	else if ( mMode == mAddNodeMode )
	{
		// Oops the road got deleted, maybe from an undo action?
      // Back to NormalMode.
      if ( mSelRiver )
      {
			// A double-click on a node in Normal mode means set AddNode mode.  
         if ( clickedNodeIdx == 0 )
         {
				submitUndo( "Add Node" );
				mAddNodeIdx = clickedNodeIdx;
            mMode = mAddNodeMode;
            mSelNode = mSelRiver->insertNode( tPos, mDefaultWidth, mDefaultDepth, mDefaultNormal, mAddNodeIdx );
            mIsDirty = true;
				setSelectedNode( mSelNode );

				return;
         }
			else
         {
				if( clickedRiverPtr && clickedNodeIdx == clickedRiverPtr->mNodes.size() - 1 )
				{
					submitUndo( "Add Node" );
					mAddNodeIdx = U32_MAX;
					mMode = mAddNodeMode;
					U32 newNode = mSelRiver->addNode( tPos, mDefaultWidth, mDefaultDepth, mDefaultNormal);  
               mIsDirty = true;
					setSelectedNode( newNode );

					return;
				}
				else
				{
					submitUndo( "Insert Node" );
					// A single-click on empty space while in
					// AddNode mode means insert / add a node.
					//submitUndo( "Add Node" );
					//F32 width = mSelRiver->getNodeWidth( mSelNode );
					U32 newNode = mSelRiver->insertNode( tPos, mDefaultWidth, mDefaultDepth, mDefaultNormal, mAddNodeIdx);
               mIsDirty = true;
					setSelectedNode( newNode );

					return;
				}
			}
		}
	}
	else if ( mMode == mInsertPointMode && mSelRiver != NULL )
	{
		if ( clickedRiverPtr == mSelRiver )
      {
			// NOTE: I guess we have to determine the if the clicked ray intersects a road but not a specific node...
         // in order to handle inserting nodes in the same way as for DecalRoad

         U32 prevNodeIdx = insertNodeIdx;
         U32 nextNodeIdx = ( prevNodeIdx + 1 > mSelRiver->mNodes.size() - 1 ) ? prevNodeIdx : prevNodeIdx + 1;

         const RiverNode &prevNode = mSelRiver->mNodes[prevNodeIdx];
         const RiverNode &nextNode = mSelRiver->mNodes[nextNodeIdx];

         F32 width = ( prevNode.width + nextNode.width ) * 0.5f;
         F32 depth = ( prevNode.depth + nextNode.depth ) * 0.5f;
         Point3F normal = ( prevNode.normal + nextNode.normal ) * 0.5f;
         normal.normalize();

         submitUndo( "Insert Node" );
         U32 newNode = mSelRiver->insertNode( collisionPnt, width, depth, normal, insertNodeIdx + 1 );
         mIsDirty = true;
         setSelectedNode( newNode );

			return;
       }
	}
	else if ( mMode == mRemovePointMode && mSelRiver != NULL )
	{
		if ( nodeClicked && clickedRiverPtr == mSelRiver )
      {
			setSelectedNode( clickedNodeIdx );
         deleteSelectedNode();
         return;
      }
	}
	else if ( mMode == mMovePointMode )
	{
		if ( nodeClicked && clickedRiverPtr == mSelRiver )
      {
			setSelectedNode( clickedNodeIdx );
         return;
      }
	}
	else if ( mMode == mScalePointMode )
	{
		if ( nodeClicked && clickedRiverPtr == mSelRiver )
      {
			setSelectedNode( clickedNodeIdx );
         return;
      }
	}
	else if ( mMode == mRotatePointMode )
	{
		if ( nodeClicked && clickedRiverPtr == mSelRiver )
      {
			setSelectedNode( clickedNodeIdx );
         return;
      }
	}
}