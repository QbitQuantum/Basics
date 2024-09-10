void SimTreeView::onCommand( int id, HWND hwndCtl, UINT codeNotify )
{
   hwndCtl, codeNotify;
   SimObject   *obj;
   SimSet    *prnt;
	lockManager();

   switch( id )
   {
      case IDM_EXIT:
         destroyWindow();
         break;

      case IDM_CUT:
         if ( (obj = getSelectedObject()) !=  NULL )
         {
            // persist selected object
            obj->fileStore( "temp\\clip.tmp" );

            // remove it from parent
            obj->deleteObject();
            delItem( getSelection() );
            state.set(STV_MODIFIED);
         }
         break;

      case IDM_COPY:
         if ( (obj = getSelectedObject()) !=  NULL )
            obj->fileStore( "temp\\clip.tmp" );
         break;

      case IDM_PASTE:
         {
            // unpersist object to get a duplicate
            Persistent::Base::Error err;
            obj = (SimObject*)Persistent::Base::fileLoad( "temp\\clip.tmp", &err );
            if ( err != Ok )
               return;

            // add to simTree
            HTREEITEM hParent = getSelection();
            if ( !isItemFolder(hParent) )
               hParent = getParent( hParent );

            prnt = (SimSet*)getObject( hParent );
            prnt->getManager()->addObject( obj );
				prnt->addObject(obj);
            HTREEITEM hItem = addSet( obj, hParent );
            selectItem( hItem );
            state.set(STV_MODIFIED);
         }
         break;

      case IDM_DELETE:
         obj = getSelectedObject();
         if ( obj )
         {
            obj->deleteObject();
            delItem( getSelection() );
            state.set(STV_MODIFIED);
         }
         break;

      case IDM_REMOVE:
         obj = getSelectedObject();
         if ( obj )
         {
            prnt = getSelectedParent();
				prnt->removeObject(obj);
            delItem( getSelection() );
            state.set(STV_MODIFIED);
         }
         break;

      case IDM_DUPLICATE:
         {
            obj = getSelectedObject();
            
            // persist object to get a duplicate
            if ( obj->fileStore( "temp\\clip.tmp" ) != Ok )
            {
					unlockManager();
               return;
            }

            Persistent::Base::Error err;
            obj = (SimObject*)Persistent::Base::fileLoad( "temp\\clip.tmp", &err );
            if ( err != Ok )
            {
					unlockManager();
               return;
            }
            // perhaps delete clip.tmp to clean up directory

            HTREEITEM hParent = getSelection();
            if ( !isItemFolder(hParent) )
               hParent = getParent( hParent );

            prnt = (SimSet*)getObject( hParent );
            prnt->getManager()->addObject( obj );
            prnt->addObject( obj );
            HTREEITEM hItem = addSet( obj, getParent(getSelection()) );
            selectItem( hItem );
            state.set(STV_MODIFIED);
         }
         break;

      case IDM_EDIT:
         inspectObject( getSelectedObject() );
         state.set(STV_MODIFIED);
         break;

      case IDM_LOCK:
         lockObject( getSelectedObject(), true );
         state.set( STV_MODIFIED );
         break;
         
      case IDM_UNLOCK:
         lockObject( getSelectedObject(), false );
         state.set( STV_MODIFIED );
         break;
         
      default:
         if ( (id>=IDM_SCRIPT_START) && (id<=scriptMenu_IDM) )
         {
            int scriptIndex = id-IDM_SCRIPT_START;
            CMDConsole::getLocked()->evaluate( script[scriptIndex], false );
         }
         // let parent handle its default menu items
         WinParent::handleContextMenuItemSelection( id );
   }
   checkMenu( hMainMenu );
	unlockManager();
}