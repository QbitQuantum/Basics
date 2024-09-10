void ForestEditorCtrl::deleteMeshSafe( ForestItemData *mesh )
{
   UndoManager *undoMan = NULL;
   if ( !Sim::findObject( "EUndoManager", undoMan ) )
   {
      Con::errorf( "ForestEditorCtrl::deleteMeshSafe() - EUndoManager not found." );
      return;     
   }

   // CompoundUndoAction which will delete the ForestItemData, ForestItem(s), and ForestBrushElement(s).
   CompoundUndoAction *compoundAction = new CompoundUndoAction( "Delete Forest Mesh" );
    
   // Find ForestItem(s) referencing this datablock and add their deletion
   // to the undo action.
   if ( mForest )
   {      
      Vector<ForestItem> foundItems;
      mForest->getData()->getItems( mesh, &foundItems );

      ForestDeleteUndoAction *itemAction = new ForestDeleteUndoAction( mForest->getData(), this );
      itemAction->removeItem( foundItems );
      compoundAction->addAction( itemAction );
   }

   // Find ForestBrushElement(s) referencing this datablock.
   SimGroup *brushGroup = ForestBrush::getGroup();
   sKey = mesh;
   Vector<SimObject*> foundElements;   
   brushGroup->findObjectByCallback( &findMeshReferences, foundElements );   

   // Add UndoAction to delete the ForestBrushElement(s) and the ForestItemData.
   MEDeleteUndoAction *elementAction = new MEDeleteUndoAction();
   elementAction->deleteObject( foundElements );
   elementAction->deleteObject( mesh );
   
   // Add compound action to the UndoManager. Done.
   undoMan->addAction( compoundAction );

   updateCollision();
}