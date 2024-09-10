LRESULT CALLBACK WndProc(
      HWND hWnd,         // window handle
      UINT message,      // type of message
      WPARAM uParam,     // additional information
      LPARAM lParam      // additional information
      )
{
   FARPROC lpProcAbout;  // pointer to the "About" function
   int wmId, wmEvent;

//****************** NEW CODE START *********

#define ptrNMHDR       ((LPNMHDR)lParam)
#define ptrNM_TREEVIEW ((NM_TREEVIEW *)lParam)
#define ptrTV_DISPINFO ((TV_DISPINFO *)lParam)

          RECT       rcItem;
   static HIMAGELIST hDragImage;
   static BOOL       bDragging;
   static HTREEITEM  hDragItem;

   switch (message) {

      case WM_NOTIFY: // This is a new Chicago message for control
                      // notifications

         switch (ptrNMHDR->code)
           {
           case TVN_BEGINDRAG: // Sent by TreeView when user
                               // wants to drag an item.

             // Only allow drag & drop for the actual coaster
             // items. The "itemNew" field of the NM_TREEVIEW
             // structure contains the attribytes of the item
             // we are going to drag. Therefore, since we are
             // using the lParam field to store an ITEM_TYPE_*
             // value, we check that field.

             if ( ITEM_TYPE_COASTER_NAME == ptrNM_TREEVIEW->itemNew.lParam)
               {
               // The hDragImage variable is declared static,
               // so the code in WM_LBUTTONUP can delete it when
               // the user stops dragging. Here we create a
               // drag image to use for the ImageList_StartDrag
               // API.

               hDragImage = TreeView_CreateDragImage
                              (
                              ptrNMHDR->hwndFrom,
                              ptrNM_TREEVIEW->itemNew.hItem
                              );

               // Get the location of the item rectangle's text.

               TreeView_GetItemRect
                 (
                 ptrNMHDR->hwndFrom,            // Handle of TreeView
                 ptrNM_TREEVIEW->itemNew.hItem, // Item in TreeView
                 &rcItem,                       // RECT to store result
                 TRUE                           // Rect of label text only
                 );

               // Cache away the handle of the item to drag into a
               // staticly declared variable, so the code in
               // WM_LBUTTONUP can know what the user is dragging.

               hDragItem = ptrNM_TREEVIEW->itemNew.hItem;

               // Start the drag ala ImageList

               ImageList_BeginDrag(hDragImage, 0,
                 ptrNM_TREEVIEW->ptDrag.x - rcItem.left, // Offset hotspot
                 ptrNM_TREEVIEW->ptDrag.y - rcItem.top);


               ImageList_DragEnter(ptrNMHDR->hwndFrom,
                 ptrNM_TREEVIEW->ptDrag.x,  // Coords of image to drag
                 ptrNM_TREEVIEW->ptDrag.y);

               // Capture the mousey to this window

               ShowCursor ( FALSE );
               SetCapture ( hWnd );

               // Set a staticly declared drag flag so the WM_MOUSEMOVE
               // and WM_LBUTTONUP messages know to take action.

               bDragging = TRUE;
               }

             return 0L;  // Return value is irrelevant

           case TVN_GETDISPINFO: // Sent by TreeView just before it paints
                                 // an item declared with callback values.

             // Our "state" items have the I_IMAGECALLBACK value
             // used for the iImage and iSelectedImage fields. This
             // TVN_GETDISPINFO code will be called whenever the
             // item is about to be drawn. It is out responsibility
             // to add code to fill in the images. The code below
             // uses a different image depending on if the item is
             // expanded or collapsed. That attribute is in the
             // state field of the item passed in the TV_DISPINFO
             // structure.

             // Our lParam is where we store what state the item
             // represents. Therefore, we will switch on that so
             // we can indicate the correct image to use.

             if ( ptrTV_DISPINFO->item.state & TVIS_EXPANDED )
               {
               switch (ptrTV_DISPINFO->item.lParam)
                 {
                 case ITEM_TYPE_STATE_CA:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageCA_OPEN;
                   break;

                 case ITEM_TYPE_STATE_NY:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageNY_OPEN;
                   break;

                 case ITEM_TYPE_STATE_OH:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageOH_OPEN;
                   break;
                 }
               }
             else  // Collapsed item
               {
               switch (ptrTV_DISPINFO->item.lParam)
                 {
                 case ITEM_TYPE_STATE_CA:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageCA;
                   break;

                 case ITEM_TYPE_STATE_NY:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageNY;
                   break;

                 case ITEM_TYPE_STATE_OH:

                   ptrTV_DISPINFO->item.iImage =
                   ptrTV_DISPINFO->item.iSelectedImage = iImageOH;
                   break;
                 }
               }
             return TRUE;

           case TVN_BEGINLABELEDIT: // Sent by TreeView when user single
                                    // clicks on an item in a TreeView
                                    // that has the TVS_EDITLABELS style
                                    // bit set.

             // Only allow label editing for the coaster names

             if (ITEM_TYPE_COASTER_NAME == ptrTV_DISPINFO->item.lParam)
               return 0;  // Return 0 to OK edit
             else
               return 1;  // Return non-zero to disallow edit
             break;

           case TVN_ENDLABELEDIT:   // Sent by TreeView when user presses
                                    // the ENTER key or ESC key, to end
                                    // an in-place edit session. If the user
                                    // pressed the ESC key, the pszText
                                    // field of the item in the TV_DISPINFO
                                    // field is NULL.

             // if user pressed ENTER to accept edits


             if ( ptrTV_DISPINFO->item.pszText)
               {
               // Set the "change mask" to indicate that the only attribute
               // we wish to change is the text field. The TV_DISPINFO
               // structure has already been filled out with the new
               // text the user typed in, we just need to pass that on
               // to the TreeView control. This is our chance to evaluate
               // the contents of this field and change it.


               ptrTV_DISPINFO->item.mask = TVIF_TEXT;

               TreeView_SetItem
                 (
                   ptrNMHDR->hwndFrom,      // Handle of TreeView
                   &(ptrTV_DISPINFO->item)  // TV_ITEM structure w/changes
                 );
               }
             break;

           }

         return (DefWindowProc(hWnd, message, uParam, lParam));

      case WM_MOUSEMOVE: // Since the mouse capture is set to this
                         // window while we do our drag & drop,
                         // we check for the drag flag and process
                         // the WM_MOUSEMOVE message.

         if (bDragging)
           {
           HTREEITEM       hTarget;  // Item under mouse
           TV_HITTESTINFO  tvht;     // Used for hit testing

           // Do standard drag drop movement

           ImageList_DragMove ( LOWORD (lParam), HIWORD (lParam));

           // Fill out hit test struct with mouse pos

           tvht.pt.x = LOWORD (lParam);
           tvht.pt.y = HIWORD (lParam);

           // Check to see if an item lives under the mouse

           if ( hTarget = TreeView_HitTest
                            (
                            hWndTreeView,  // This is the global variable
                            &tvht          // TV_HITTESTINFO struct
                            )
              )
             {
             TV_ITEM         tvi;           // Temporary Item

             tvi.mask       = TVIF_PARAM; // We want to fetch the
                                          // lParam field.

             tvi.hItem      = hTarget;    // Set the handle of the
                                          // item to fetch.

             TreeView_GetItem ( hWndTreeView, &tvi ); // Fetch, spot!

             // Check to see if the lParam is a valid item to drop
             // onto (in this case, another roller coaster, such as
             // the Coney Island Cyclone). Skip this operation if
             // the item is already selected (to avoid flicker)

             if ( ITEM_TYPE_COASTER_NAME == tvi.lParam )
               {
               if ( hTarget != TreeView_GetDropHilight (hWndTreeView))
                 {
                 // Hide the drag image
                 ImageList_DragShowNolock ( FALSE );  //DragShow to DragShowNoLock lithangw
                 // Select the item
                 TreeView_SelectDropTarget ( hWndTreeView, hTarget );
                 // Show the drag image
                 ImageList_DragShowNolock ( TRUE ); //DragShow to DragShowNoLock lithangw
                 }
               return 0L;
               }
             }

           // If we made it here, then the user has either
           // dragged the mouse over an invalid item, or no item.
           // Hide any current drop target, this is a no-no drop
           ImageList_DragShowNolock ( FALSE );  //screen update problem tokuroy
           TreeView_SelectDropTarget ( hWndTreeView, NULL );
           ImageList_DragShowNolock ( TRUE );   //screen update problem tokuroy
           }
         break;

      case WM_LBUTTONUP: // Since the mouse capture is set to this
                         // window while we do our drag & drop,
                         // we check for the drag flag and process
                         // the WM_LBUTTONUP message.


         if (bDragging)
           {
           HTREEITEM       hTarget;       // Item under mouse
           TV_ITEM         tvi;           // Temporary Item
           TV_INSERTSTRUCT tvIns;         // Insert struct
           char            szBuffer[256]; // Item text buffer

           // End the drag
           ImageList_EndDrag();
           // Bring back the cursor
           ShowCursor ( TRUE );
           // Release the mouse capture
           ReleaseCapture();
           // Clear the drag flag
           bDragging = FALSE;
           // Clean up the image list object
           ImageList_Destroy ( hDragImage );
           hDragImage = NULL;

           // First, check to see if there is a valid drop point.
           // The cheezy way to do this is to check for a highlighted
           // drop target, since the logic to validate drop points
           // is in the WM_MOUSEMOVE. Duping that code here would
           // be a headache.

           if ( hTarget = TreeView_GetDropHilight (hWndTreeView))
             {
             // If we made it here, then we need to move the item.
             // First, we will fetch it, specifying the attributes
             // we need to copy.

             tvi.mask       = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
             tvi.hItem      = hDragItem;
             tvi.pszText    = szBuffer;
             tvi.cchTextMax = sizeof(szBuffer);

             TreeView_GetItem ( hWndTreeView, &tvi );

             // Now, figure the new place to put it by filling out
             // the TV_INSERTSTRUCT structure, to use the drop target
             // as the sibling to insert after, and using the drop
             // target's parent as the parent to insert this one
             // after as well.

             tvIns.hParent         = TreeView_GetParent ( hWndTreeView, hTarget );
             tvIns.hInsertAfter    = hTarget;
             tvIns.item            = tvi;

             // Delete the old item

             TreeView_DeleteItem ( hWndTreeView, hDragItem );

             // And add the new item (if your app tracks the handles of
             // the items, you want to use the return value
             // of this function to update your data structure that
             // tracks the handles.

             TreeView_InsertItem ( hWndTreeView, &tvIns );
             }

           // Clear any drop highlights on the TreeView

           TreeView_SelectDropTarget ( hWndTreeView, NULL );
           }
         break;

      case WM_SIZE:

         if ( hWndTreeView )     // Standard code to keep the TreeView
                                 // sized up with the main window
           {
           SetWindowPos ( hWndTreeView,
                          NULL,
                          0, 0,
                          LOWORD (lParam),
                          HIWORD (lParam),
                          SWP_NOZORDER
                        );
           }
         break;

//****************** NEW CODE END *********

      case WM_COMMAND:  // message: command from application menu

         // Message packing of uParam and lParam have changed for Win32,
         // let us handle the differences in a conditional compilation:
         #if defined (_WIN32)
             wmId    = LOWORD(uParam);
			    wmEvent = HIWORD(uParam);
         #else
            wmId    = uParam;
            wmEvent = HIWORD(lParam);
         #endif

         switch (wmId) {
            case IDM_ABOUT:
               lpProcAbout = MakeProcInstance((FARPROC)About, hInst);

               DialogBox(hInst,           // current instance
                  "AboutBox",             // dlg resource to use
                  hWnd,                   // parent handle
                  (DLGPROC)lpProcAbout);  // About() instance address

               FreeProcInstance(lpProcAbout);
               break;

            case IDM_EXIT:
               DestroyWindow (hWnd);
               break;

            case IDM_HELPCONTENTS:
               if (!WinHelp (hWnd, "TREEVIEW.HLP", HELP_KEY,(DWORD)(LPSTR)"CONTENTS")) {
                  MessageBox (GetFocus(),
                     "Unable to activate help",
                     szAppName, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
				
               }
               break;

            case IDM_HELPSEARCH:
               if (!WinHelp(hWnd, "TREEVIEW.HLP", HELP_PARTIALKEY, (DWORD)(LPSTR)"")) {
                  MessageBox (GetFocus(),
                     "Unable to activate help",
                     szAppName, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
               }
               break;

            case IDM_HELPHELP:
               if(!WinHelp(hWnd, (LPSTR)NULL, HELP_HELPONHELP, 0)) {
                  MessageBox (GetFocus(),
                     "Unable to activate help",
                     szAppName, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
               }
               break;

            // Here are all the other possible menu options,
            // all of these are currently disabled:
            case IDM_NEW:
            case IDM_OPEN:
            case IDM_SAVE:
            case IDM_SAVEAS:
            case IDM_UNDO:
            case IDM_CUT:
            case IDM_COPY:
            case IDM_PASTE:
            case IDM_LINK:
            case IDM_LINKS:

            default:
               return (DefWindowProc(hWnd, message, uParam, lParam));
         }
         break;

      case WM_DESTROY:  // message: window being destroyed

         PostQuitMessage(0);
         break;

      default:          // Passes it on if unproccessed
         return (DefWindowProc(hWnd, message, uParam, lParam));
   }
   return (0);
}