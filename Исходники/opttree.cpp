BOOL  OptTree_ProcessMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, BOOL *result, int idcTree, OPTTREE_OPTION *options, int optionCount)
{
    enum { IMG_GROUP, IMG_CHECK, IMG_NOCHECK, IMG_RCHECK, IMG_NORCHECK, IMG_GRPOPEN, IMG_GRPCLOSED };

    HWND hwndTree = GetDlgItem(hwnd, idcTree);
    switch (msg)
    {
    case WM_INITDIALOG:
    {
        int indx;
        TCHAR itemName[1024];
        HIMAGELIST hImgLst;

        TreeView_SelectItem(hwndTree, NULL);
        TreeView_DeleteAllItems(hwndTree);

        hImgLst = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR|ILC_COLOR32|ILC_MASK, 5, 1);
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_MIRANDA));
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_TICK));	// check on
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_NOTICK));	// check off
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_TICK));	// radio on
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_NOTICK));	// radio on
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_GROUPOPEN));
        ImageList_ReplaceIcon(hImgLst, -1, (HICON)LoadSkinnedIcon(SKINICON_OTHER_GROUPSHUT));
        TreeView_SetImageList(hwndTree, hImgLst, TVSIL_NORMAL);

        /* build options tree. based on code from IcoLib */
        for (indx = 0; indx < optionCount; indx++)
        {
            TCHAR* sectionName;
            int sectionLevel = 0;

            HTREEITEM hSection = NULL;
            if (options[indx].szOptionName)
                lstrcpy(itemName, options[indx].szOptionName);
            else
                itemName[0] = 0;

            sectionName = itemName;

            while (sectionName)
            {
                // allow multi-level tree
                TCHAR* pItemName = sectionName;
                HTREEITEM hItem;

                if (sectionName = _tcschr(sectionName, '/'))
                {
                    // one level deeper
                    *sectionName = 0;
                    sectionName++;
                }

                hItem = OptTree_FindNamedTreeItemAt(hwndTree, hSection, pItemName);
                //if (!sectionName || !hItem)
                if ((!sectionName || !hItem) && !(options[indx].dwFlag & OPTTREE_INVISIBLE))
                {
                    if (!hItem)
                    {
                        TVINSERTSTRUCT tvis = {0};

                        tvis.hParent = hSection;
                        tvis.hInsertAfter = TVI_LAST;//TVI_SORT;
                        tvis.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_STATE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
                        tvis.item.pszText = pItemName;
                        tvis.item.state = tvis.item.stateMask = TVIS_EXPANDED;
                        if (sectionName)
                        {
                            tvis.item.lParam = -1;
                            tvis.item.state |= TVIS_BOLD;
                            tvis.item.stateMask |= TVIS_BOLD;
                            tvis.item.iImage = tvis.item.iSelectedImage = IMG_GRPOPEN;
                        } else
                        {
                            tvis.item.lParam = indx;
                            if (options[indx].groupId == OPTTREE_CHECK)
                            {
                                tvis.item.iImage = tvis.item.iSelectedImage = IMG_NOCHECK;
                            } else
                            {
                                tvis.item.iImage = tvis.item.iSelectedImage = IMG_NORCHECK;
                            }
                        }
                        hItem = TreeView_InsertItem(hwndTree, &tvis);
                        if (!sectionName)
                            options[indx].hItem = hItem;
                    }
                }
                sectionLevel++;
                hSection = hItem;
            }
        }

        OptTree_Translate(hwndTree);
        ShowWindow(hwndTree, SW_SHOW);
        TreeView_SelectItem(hwndTree, OptTree_FindNamedTreeItemAt(hwndTree, 0, NULL));
        break;
    }

    case WM_DESTROY:
    {
        ImageList_Destroy(TreeView_GetImageList(hwndTree, TVSIL_NORMAL));
        break;
    }

    case WM_NOTIFY:
    {
        LPNMHDR lpnmhdr = (LPNMHDR)lparam;
        if (lpnmhdr->idFrom != idcTree) break;
        switch (lpnmhdr->code)
        {
        case NM_CLICK:
        {
            TVHITTESTINFO hti;
            hti.pt.x=(short)LOWORD(GetMessagePos());
            hti.pt.y=(short)HIWORD(GetMessagePos());
            ScreenToClient(lpnmhdr->hwndFrom,&hti.pt);
            if(TreeView_HitTest(lpnmhdr->hwndFrom,&hti))
            {
                if(hti.flags&TVHT_ONITEMICON)
                {
                    TVITEM tvi;
                    tvi.mask=TVIF_HANDLE|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
                    tvi.hItem=hti.hItem;
                    TreeView_GetItem(lpnmhdr->hwndFrom,&tvi);
                    switch (tvi.iImage)
                    {
                    case IMG_GRPOPEN:
                        tvi.iImage = tvi.iSelectedImage = IMG_GRPCLOSED;
                        TreeView_Expand(lpnmhdr->hwndFrom, tvi.hItem, TVE_COLLAPSE);
                        break;
                    case IMG_GRPCLOSED:
                        tvi.iImage = tvi.iSelectedImage = IMG_GRPOPEN;
                        TreeView_Expand(lpnmhdr->hwndFrom, tvi.hItem, TVE_EXPAND);
                        break;

                    case IMG_CHECK:
                        tvi.iImage = tvi.iSelectedImage = IMG_NOCHECK;
                        SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
                        break;
                    case IMG_NOCHECK:
                        tvi.iImage = tvi.iSelectedImage = IMG_CHECK;
                        SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
                        break;
                    case IMG_NORCHECK:
                    {
                        int i;
                        for (i = 0; i < optionCount; ++i)
                        {
                            if (options[i].groupId == options[tvi.lParam].groupId)
                            {
                                TVITEM tvi_tmp;
                                tvi_tmp.mask = TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
                                tvi_tmp.hItem = options[i].hItem;
                                tvi_tmp.iImage = tvi_tmp.iSelectedImage = IMG_NORCHECK;
                                TreeView_SetItem(lpnmhdr->hwndFrom, &tvi_tmp);
                            }
                        }
                        tvi.iImage = tvi.iSelectedImage = IMG_RCHECK;
                        SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
                        break;
                    }
                    }
                    TreeView_SetItem(lpnmhdr->hwndFrom,&tvi);
                }
            }
            break;
        }

        case TVN_ITEMEXPANDEDW:
        {
            LPNMTREEVIEWW lpnmtv = (LPNMTREEVIEWW)lparam;
            TVITEM tvi;
            tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
            tvi.hItem = lpnmtv->itemNew.hItem;
            tvi.iImage = tvi.iSelectedImage =
                             (lpnmtv->itemNew.state & TVIS_EXPANDED) ? IMG_GRPOPEN : IMG_GRPCLOSED;
            SendMessageW(lpnmhdr->hwndFrom, TVM_SETITEMW, 0, (LPARAM)&tvi);
            break;
        }

        case TVN_ITEMEXPANDEDA:
        {
            LPNMTREEVIEWA lpnmtv = (LPNMTREEVIEWA)lparam;
            TVITEM tvi;
            tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
            tvi.hItem = lpnmtv->itemNew.hItem;
            tvi.iImage = tvi.iSelectedImage =
                             (lpnmtv->itemNew.state & TVIS_EXPANDED) ? IMG_GRPOPEN : IMG_GRPCLOSED;
            SendMessageA(lpnmhdr->hwndFrom, TVM_SETITEMA, 0, (LPARAM)&tvi);
            break;
        }
        }
        break;
    }
    }
    return FALSE;
}