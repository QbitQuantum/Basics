void GuiRoadEditorCtrl::deleteSelectedRoad( bool undoAble )
{
   AssertFatal( mSelRoad != NULL, "GuiRoadEditorCtrl::deleteSelectedRoad() - No road IS selected" );

   // Not undo-able? Just delete it.
   if ( !undoAble )
   {
      DecalRoad *lastRoad = mSelRoad;

      setSelectedRoad(NULL);

      lastRoad->deleteObject();
      mIsDirty = true;

      return;
   }

   // Grab the mission editor undo manager.
   UndoManager *undoMan = NULL;
   if ( !Sim::findObject( "EUndoManager", undoMan ) )
   {
      // Couldn't find it? Well just delete the road.
      Con::errorf( "GuiRoadEditorCtrl::on3DMouseDown() - EUndoManager not found!" );    
      return;
   }
   else
   {
      DecalRoad *lastRoad = mSelRoad;
      setSelectedRoad(NULL);

      // Create the UndoAction.
      MEDeleteUndoAction *action = new MEDeleteUndoAction("Deleted Road");
      action->deleteObject( lastRoad );
      mIsDirty = true;

      // Submit it.               
      undoMan->addAction( action );
   }
}