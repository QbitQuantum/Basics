void CCJShellTree::FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM hParent)
{
    TV_ITEM         tvi;                          // TreeView Item.
    TV_INSERTSTRUCT tvins;                        // TreeView Insert Struct.
    HTREEITEM       hPrev = NULL;                 // Previous Item Added.
    LPENUMIDLIST    lpe=0;
    LPITEMIDLIST    lpi=0, lpifqThisItem=0;
    LPTVITEMDATA    lptvid=0;
    LPMALLOC        lpMalloc=0;
    ULONG           ulFetched;
    HRESULT         hr;
    TCHAR           szBuff[256];
    HWND            hwnd=GetParent()->GetSafeHwnd();

    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    // Hourglass on!

    SetCapture();
    CWaitCursor wait;   // display wait cursor

    if (SUCCEEDED(hr))
    {
		SetRedraw(FALSE);

        hr=lpsf->EnumObjects(hwnd, 
			SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &lpe);

        if (SUCCEEDED(hr))
        {
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                //Create a fully qualified path to the current item
                //The SH* shell api's take a fully qualified path pidl,
                //(see GetIcon above where I call SHGetFileInfo) whereas the
                //interface methods take a relative path pidl.

                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                if (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER))
                {
                   //We need this next if statement so that we don't add things like
                   //the MSN to our tree.  MSN is not a folder, but according to the
                   //shell is has subfolders....

                   if (ulAttrs & SFGAO_FOLDER)
                   {
                      tvi.mask            = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE |
                                            TVIF_PARAM;

                      if (ulAttrs & SFGAO_HASSUBFOLDER)
                      {
                         //This item has sub-folders, so let's put the + in the TreeView.
                         //The first time the user clicks on the item, we'll populate the
                         //sub-folders then.

                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      //OK, let's get some memory for our ITEMDATA struct

                      lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;
   
                      //Now get the friendly name that we'll put in the treeview...

                      if( m_shell.GetName(lpsf, lpi, SHGDN_NORMAL, szBuff) == FALSE ) {
                         goto Done;
					  }

                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=m_shell.ConcatPidls(lpifq, lpi);
      
                      //Now, make a copy of the ITEMIDLIST
      
                      lptvid->lpi=m_shell.CopyITEMID(lpMalloc, lpi);
   
                      m_shell.GetNormalAndSelectedIcons(lpifqThisItem, &tvi);
   
                      lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                      lpsf->AddRef();

                      //So, you ask, what's the story here?  Why do we have 2
                      //functions that apparently do the same thing?  Well, 
                      //ParseDisplayName() (used in GetFullyQualPidl) does not 
                      //work well for non-file system objects such as the My 
                      //Computer and Net Hood.  So, since we know that these 
                      //guys will only show up when we are enumerating the root 
                      //of the namespace (as identified by an hParent of TVI_ROOT), 
                      //we special case this here.  You *could* use ConcatPidls() 
                      //in ALL cases, but the GetFullyQualPidl() is shown for 
                      //demonstration purposes, since it's the more intuative way.

//Commented out for now, since we need ConcatPidls for *any* non-file system object.
//This includes things like Control Panel, et al.

//                      if (hParent==TVI_ROOT)
                         lptvid->lpifq=m_shell.ConcatPidls(lpifq, lpi);
//                      else
//                         lptvid->lpifq=GetFullyQualPidl(lpsf, lpi);
   
                      tvi.lParam = (LPARAM)lptvid;
   
                      // Populate the TreeVeiw Insert Struct
                      // The item is the one filled above.
                      // Insert it after the last item inserted at this level.
                      // And indicate this is a root entry.
   				   
                      tvins.item         = tvi;
                      tvins.hInsertAfter = hPrev;
                      tvins.hParent      = hParent;
   
                      // Add the item to the tree
   
                      hPrev = InsertItem(&tvins);
                   }

                   lpMalloc->Free(lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->Free(lpi);  //Finally, free the pidl that the shell gave us...
                lpi=0;
            }
        }

    }
    else {
		SetRedraw();
		return;
	}

Done:
 
    // Hourglass off!

    ReleaseCapture();

    if (lpe)  lpe->Release();

    //The following 2 if statements will only be TRUE if we got here on an
    //error condition from the "goto" statement.  Otherwise, we free this memory
    //at the end of the while loop above.
    if (lpi && lpMalloc)           lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) lpMalloc->Release();
	SetRedraw();
}