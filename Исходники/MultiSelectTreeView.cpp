LRESULT MusicBrowserUI::TreeViewWndProc(HWND hwnd, 
                                        UINT msg, 
                                        WPARAM wParam, 
                                        LPARAM lParam)
{
    WNDPROC lpOldProc = (WNDPROC)GetProp(hwnd, "oldproc" );
    static bool dragging = false;
    static RECT dragRect;
    static HTREEITEM dragItem = NULL;
    static bool selectedOnMouseDown = false;

    //return CallWindowProc(lpOldProc, hwnd, msg, wParam, lParam );

	switch(msg)
	{
		case WM_DESTROY:   
		{
			//  Put back old window proc and
			SetWindowLong( hwnd, GWL_WNDPROC, (DWORD)lpOldProc );

			// remove window property
			RemoveProp( hwnd, "oldproc" ); 
            RemoveProp( hwnd, "this" ); 

			break;
        }

        case WM_MOUSEMOVE:
        {
            if(dragging)
            {
                if(wParam & MK_LBUTTON)
                {
                    POINT dragPt;

                    dragPt.x = LOWORD(lParam);
                    dragPt.y = HIWORD(lParam);

                    if( !PtInRect(&dragRect, dragPt) )
                    {
                        SetCapture(NULL);
                        dragging = false;

                        NM_TREEVIEW nm_treeview;

                        memset(&nm_treeview, 0x00, sizeof(NM_TREEVIEW));
                        
                        nm_treeview.hdr.code = TVN_BEGINDRAG;
                        nm_treeview.hdr.hwndFrom = hwnd;
                        nm_treeview.hdr.idFrom = GetWindowLong(hwnd, GWL_ID);

                        nm_treeview.itemNew.hItem = dragItem;
                        nm_treeview.itemNew.mask = TVIF_STATE|TVIF_PARAM;
                        nm_treeview.itemNew.stateMask = TVIS_BOLD|TVIS_CUT|TVIS_DROPHILITED|TVIS_EXPANDED|TVIS_SELECTED|TVIS_EXPANDEDONCE;
                        
                        TreeView_GetItem(hwnd, &nm_treeview.itemNew);

                        nm_treeview.ptDrag.x = LOWORD(lParam);
                        nm_treeview.ptDrag.y = HIWORD(lParam);

                        SendMessage(GetParent(hwnd), 
                                    WM_NOTIFY, 
                                    (WPARAM)nm_treeview.hdr.idFrom,
                                    (LPARAM)&nm_treeview);

                        return TRUE;
                    }
                }
            }

            break;
        }

        case WM_RBUTTONDOWN:
        {
            SetFocus(hwnd);

            HTREEITEM item;
            TV_HITTESTINFO hti;

            hti.pt.x = LOWORD(lParam);
            hti.pt.y = HIWORD(lParam);

            item = TreeView_HitTest(hwnd, &hti);  

            if(item && (hti.flags & TVHT_ONITEM))
            {
                HTREEITEM focusItem = TreeView_GetSelection(hwnd);
                TV_ITEM tv_item;

                tv_item.hItem = focusItem;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocusSelected = (tv_item.state & TVIS_SELECTED) != 0;

                tv_item.hItem = item;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocus = item == focusItem;
                bool wasSelected = (tv_item.state & TVIS_SELECTED) != 0;

                if(!wasSelected)
                {
                    // need to iterate all the items and 
                    // make sure they aren't selected
                    HTREEITEM rootItem = TreeView_GetRoot(hwnd);

                    if(rootItem)
                    {
                        do
                        {
                            tv_item.hItem = rootItem;
                            tv_item.mask = TVIF_STATE;
                            tv_item.stateMask = TVIS_SELECTED;
                            tv_item.state = 0;

                            TreeView_SetBranch(hwnd, &tv_item);
                        
                        }while(rootItem = TreeView_GetNextSibling(hwnd, rootItem));
                    }

                    // need to set this back cause windows won't
                    // set it if it is already the focus item and
                    // we just deselected it
                    if(wasSelected && wasFocus)
                    {
                        tv_item.hItem = focusItem;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = TVIS_SELECTED;

                        TreeView_SetItem(hwnd, &tv_item);
                    }
                }

                TreeView_Select(hwnd, item, TVGN_CARET);

                if(!wasFocus && wasFocusSelected && wasSelected)
                {
                    tv_item.hItem = focusItem;
                    tv_item.mask = TVIF_STATE;
                    tv_item.stateMask = TVIS_SELECTED;
                    tv_item.state = TVIS_SELECTED;

                    TreeView_SetItem(hwnd, &tv_item);
                }
            }

            //return TRUE;

            break;
        }

        case WM_RBUTTONUP:
        {
            break;
        }

        case WM_LBUTTONDBLCLK:
        {
            TV_ITEM tv_item;
            TV_HITTESTINFO tv_htinfo;

            KillTimer(hwnd, 1);

            //GetCursorPos(&tv_htinfo.pt);
            //ScreenToClient(m_hMusicView, &tv_htinfo.pt);
            tv_htinfo.pt.x =  LOWORD(lParam);
            tv_htinfo.pt.y =  HIWORD(lParam);


            if(TreeView_HitTest(m_hMusicView, &tv_htinfo) && 
			   (tv_htinfo.flags & TVHT_ONITEM))
            {
                tv_item.hItem = TreeView_GetSelection(m_hMusicView); 
                tv_item.mask = TVIF_PARAM | TVIF_HANDLE;
                tv_item.lParam = 0;

                TreeView_GetItem(m_hMusicView, &tv_item);

                TreeData* treedata = (TreeData*)tv_item.lParam;

                bool playNow;

                m_context->prefs->GetPrefBoolean(kPlayImmediatelyPref, &playNow);

                if(treedata && treedata->IsTrack())
                {
                    if(playNow && !m_pParent)
                    {
                        ClearPlaylistEvent();  
                    }

                    PlaylistItem *item;
            
                    item = new PlaylistItem(*treedata->m_pTrack);
                    m_plm->AddItem(item, false);
                } 
                else if(treedata && treedata->IsPlaylist())
                {
                    if(playNow && !m_pParent)
                    {
                        ClearPlaylistEvent();  
                    }

                    m_plm->ReadPlaylist(treedata->m_oPlaylistPath.c_str());
                }
                else if(treedata && treedata->IsPortable())
                {
                    EditPortablePlaylist(treedata->m_pPortable);
                }
                else if(treedata && treedata->IsStream())
                {
                    if(playNow && !m_pParent)
                    {
                        ClearPlaylistEvent();  
                    }

                    PlaylistItem *item;
            
                    item = new PlaylistItem(*treedata->m_pStream);
                    m_plm->AddItem(item, false);
                }
                else if(tv_htinfo.hItem == m_hNewPlaylistItem)
                {
                    NewPlaylist();
                }
                else if(tv_htinfo.hItem == m_hNewPortableItem)
                {
                    m_context->target->AcceptEvent(new ShowPreferencesEvent(3));
                }
                else if(tv_htinfo.hItem == m_hNewFavoritesItem)
                {
                    NewFavoriteEvent();
                }
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            bool shiftKeyPressed = IsShiftDown();
            bool ctrlKeyPressed = IsCtrlDown();

            selectedOnMouseDown = false;

            SetFocus(hwnd);

            HTREEITEM item;
            TV_HITTESTINFO hti;

            hti.pt.x = LOWORD(lParam);
            hti.pt.y = HIWORD(lParam);

            int dx = GetSystemMetrics(SM_CXDRAG);
            int dy = GetSystemMetrics(SM_CYDRAG);

            dragRect.top = hti.pt.y - dy;
            dragRect.bottom = hti.pt.y + dy;
            dragRect.left = hti.pt.x - dx;
            dragRect.right = hti.pt.x + dx;
        
            item = TreeView_HitTest(hwnd, &hti);  

            if(item && (hti.flags & TVHT_ONITEM))
            {
                dragItem = item;

                HTREEITEM focusItem = TreeView_GetSelection(hwnd);
                TV_ITEM tv_item;

                tv_item.hItem = focusItem;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocusSelected = (tv_item.state & TVIS_SELECTED) != 0;

                tv_item.hItem = item;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocus = item == focusItem;
                bool wasSelected = (tv_item.state & TVIS_SELECTED) != 0;

                HTREEITEM rootItem = TreeView_GetRoot(hwnd);
                selectedOnMouseDown = wasSelected && (CountSelectedItems(rootItem) == 1);
                
                if(ctrlKeyPressed)
                {
                    /*TreeView_Select(hwnd, item, TVGN_CARET);

                    if(focusItem)
                    {
                        tv_item.hItem = focusItem;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = TVIS_SELECTED;

                        TreeView_SetItem(hwnd, &tv_item);
                    }*/

                    return TRUE;
                }
                else if(shiftKeyPressed)
                {
                    // need to iterate all the items and 
                    // make sure they aren't selected
                    HTREEITEM rootItem = TreeView_GetRoot(hwnd);

                    if(rootItem)
                    {
                        do
                        {
                            tv_item.hItem = rootItem;
                            tv_item.mask = TVIF_STATE;
                            tv_item.stateMask = TVIS_SELECTED;
                            tv_item.state = 0;

                            TreeView_SetBranch(hwnd, &tv_item);
                            
                        }while(rootItem = TreeView_GetNextSibling(hwnd, rootItem));
                    }

                    HTREEITEM topItem = NULL;
                    HTREEITEM bottomItem = NULL;
                    HTREEITEM dummyItem = NULL;

                    dummyItem = focusItem;

                    // which item is above the other? search downward first
                    while(dummyItem = TreeView_GetNextSibling(hwnd, dummyItem))
                    {
                        if(dummyItem == item)
                        {
                            topItem = focusItem;
                            bottomItem = item;
                            break;
                        }
                    }
                    
                    // did we find out? no? search upward next
                    if(!topItem)
                    {
                        dummyItem = focusItem;

                        // which item is above the other? search downward first
                        while(dummyItem = TreeView_GetPrevSibling(hwnd, dummyItem))
                        {
                            if(dummyItem == item)
                            {
                                topItem = item;
                                bottomItem = focusItem;
                                break;
                            }
                        }
                    }

                    // if they are not siblings then we do not support shift
                    // selection so just pass it on
                    if(topItem)
                    {
                        // need to iterate all the items and 
                        // select them
                        
                        rootItem = topItem;

                        do
                        {
                            tv_item.hItem = rootItem;
                            tv_item.mask = TVIF_STATE;
                            tv_item.stateMask = TVIS_SELECTED;
                            tv_item.state = TVIS_SELECTED;

                            TreeView_SetBranch(hwnd, &tv_item);
                    
                        }while(rootItem != bottomItem && (rootItem = TreeView_GetNextSibling(hwnd, rootItem)));

                        
                        return TRUE;
                    }
                    
                    break;
                }
                else
                {
                    if(!wasSelected)
                    {
                        // need to iterate all the items and 
                        // make sure they aren't selected
                        HTREEITEM rootItem = TreeView_GetRoot(hwnd);

                        if(rootItem)
                        {
                            do
                            {
                                tv_item.hItem = rootItem;
                                tv_item.mask = TVIF_STATE;
                                tv_item.stateMask = TVIS_SELECTED;
                                tv_item.state = 0;

                                TreeView_SetBranch(hwnd, &tv_item);
                            
                            }while(rootItem = TreeView_GetNextSibling(hwnd, rootItem));
                        }

                        // need to set this back cause windows won't
                        // set it if it is already the focus item and
                        // we just deselected it
                        if(wasSelected && wasFocus)
                        {
                            tv_item.hItem = focusItem;
                            tv_item.mask = TVIF_STATE;
                            tv_item.stateMask = TVIS_SELECTED;
                            tv_item.state = TVIS_SELECTED;

                            TreeView_SetItem(hwnd, &tv_item);
                        }
                    }

                    TreeView_Select(hwnd, item, TVGN_CARET);

                    if(!wasFocus && wasFocusSelected && wasSelected)
                    {
                        tv_item.hItem = focusItem;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = TVIS_SELECTED;

                        TreeView_SetItem(hwnd, &tv_item);
                    }
                    
                    
                }

                SetCapture(hwnd);
                dragging = true;

                return TRUE;
            }
                    
            break;
        }

        case WM_TIMER:
        {
            KillTimer(hwnd, 1);
            EditItemLabel(hwnd, g_editItem);
            break;
        }

        case WM_LBUTTONUP:
        {
            bool shiftKeyPressed = IsShiftDown();
            bool ctrlKeyPressed = IsCtrlDown();

            SetCapture(NULL);
            dragging = false;

            HTREEITEM item;
            TV_HITTESTINFO hti;

            hti.pt.x = LOWORD(lParam);
            hti.pt.y = HIWORD(lParam);
        
            item = TreeView_HitTest(hwnd, &hti);  

            if(item && (hti.flags & TVHT_ONITEM))
            {
                HTREEITEM focusItem = TreeView_GetSelection(hwnd);
                TV_ITEM tv_item;

                tv_item.hItem = focusItem;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocusSelected = (tv_item.state & TVIS_SELECTED) != 0;

                tv_item.hItem = item;
                tv_item.mask = TVIF_STATE;
                tv_item.stateMask = TVIS_SELECTED;

                TreeView_GetItem(hwnd, &tv_item);

                bool wasFocus = item == focusItem;
                bool wasSelected = (tv_item.state & TVIS_SELECTED) != 0;
                
                if(ctrlKeyPressed)
                {
                    TreeView_Select(hwnd, item, TVGN_CARET);

                    if(wasSelected)
                    {
                        tv_item.hItem = item;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = 0;

                        TreeView_SetItem(hwnd, &tv_item);
                    }


                    if(!wasFocus && wasFocusSelected || !wasSelected)
                    {
                        tv_item.hItem = focusItem;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = TVIS_SELECTED;

                        TreeView_SetItem(hwnd, &tv_item);
                    }

                    return TRUE;
                }
                else if(!shiftKeyPressed)
                {
                    // need to iterate all the items and 
                    // make sure they aren't selected
                    HTREEITEM rootItem = TreeView_GetRoot(hwnd);

                    if(rootItem)
                    {
                        do
                        {
                            tv_item.hItem = rootItem;
                            tv_item.mask = TVIF_STATE;
                            tv_item.stateMask = TVIS_SELECTED;
                            tv_item.state = 0;

                            TreeView_SetBranch(hwnd, &tv_item);
                        
                        }while(rootItem = TreeView_GetNextSibling(hwnd, rootItem));
                    }

                    // need to set this back cause windows won't
                    // set it if it is already the focus item and
                    // we just deselected it
                    if(wasSelected && wasFocus)
                    {
                        tv_item.hItem = focusItem;
                        tv_item.mask = TVIF_STATE;
                        tv_item.stateMask = TVIS_SELECTED;
                        tv_item.state = TVIS_SELECTED;

                        TreeView_SetItem(hwnd, &tv_item);
                    }
                    
                    if(selectedOnMouseDown)
                    {
                        if(g_editItem != item)
                        {
                            // i should do this in the notify but it is ignoring me
                            if(item != m_hMyMusicItem &&
                               item != m_hPlaylistItem &&
                               item != m_hAllItem &&
                               item != m_hUncatItem &&
                               item != m_hNewPlaylistItem &&
                               item != m_hStreamsItem &&
                               item != m_hFavoritesItem &&
                               item != m_hNewFavoritesItem &&
                               item != m_hPortableItem &&
                               TreeView_GetParent(m_hMusicView, item) != m_hPortableItem &&
                               item != m_hCDItem &&
                               TreeView_GetParent(m_hMusicView, item) != m_hCDItem)
                            {
                                // pause a half sec so this does not
                                // look so jarring
                                //Sleep(500);
                                SetTimer(hwnd, 1, GetDoubleClickTime(), NULL);
                                g_editItem = item;
                                //EditItemLabel(hwnd, item);
                            }
                        }
                        else
                        {
                            g_editItem = NULL;
                        }
                    }
                }
            }

                    
            break;
        }

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        {
            UpdateButtonStates();
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    } 
	
	//  Pass all non-custom messages to old window proc
	return CallWindowProc(lpOldProc, hwnd, msg, wParam, lParam );
}