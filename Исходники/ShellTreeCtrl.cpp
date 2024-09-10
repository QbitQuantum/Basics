/****************************************************************************
*
*  FUNCTION: FillTreeView( LPSHELLFOLDER lpsf,
*                          LPITEMIDLIST  lpifq,
*                          HTREEITEM     hParent)
*
*  PURPOSE: Fills a branch of the TreeView control.  Given the
*           shell folder, enumerate the subitems of this folder,
*           and add the appropriate items to the tree.
*
*  PARAMETERS:
*    lpsf         - Pointer to shell folder that we want to enumerate items 
*    lpifq        - Fully qualified item id list to the item that we are enumerating
*                   items for.  In other words, this is the PIDL to the item
*                   identified by the lpsf parameter.
*    hParent      - Parent node
*
*  COMMENTS:
*    This function enumerates the items in the folder identifed by lpsf.
*    Note that since we are filling the left hand pane, we will only add
*    items that are folders and/or have sub-folders.  We *could* put all
*    items in here if we wanted, but that's not the intent.
*
****************************************************************************/
void CShellTreeCtrl::FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM     hParent)
{
    TV_ITEM         tvi;                          // TreeView Item.
    TV_INSERTSTRUCT tvins;                        // TreeView Insert Struct.
    HTREEITEM       hPrev = NULL;                 // Previous Item Added.
    LPSHELLFOLDER   lpsf2=NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    lpi=NULL, lpiTemp=NULL, lpifqThisItem=NULL;
    LPTVITEMDATA    lptvid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;
    char            szBuff[256];
	char			szFileName[2048];
    HWND            hwnd=::GetParent(m_hWnd);

    // Allocate a shell memory object. 
    hr=::SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(hr))
    {
        // Get the IEnumIDList object for the given folder.
        hr=lpsf->EnumObjects(hwnd, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS | SHCONTF_INCLUDEHIDDEN , &lpe);

        if (SUCCEEDED(hr))
        {
            // Enumerate throught the list of folder and non-folder objects.
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                //Create a fully qualified path to the current item
                //The SH* shell api's take a fully qualified path pidl,
                //(see GetIcon above where I call SHGetFileInfo) whereas the
                //interface methods take a relative path pidl.
                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                // Determine what type of object we have.
                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                if (m_bDispFile || (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER)))
                {
                   //We need this next if statement so that we don't add things like
                   //the MSN to our tree.  MSN is not a folder, but according to the
                   //shell it has subfolders.
                   if (m_bDispFile || (ulAttrs & SFGAO_FOLDER ))
                   {
                      tvi.mask= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

                      if (ulAttrs & (SFGAO_FOLDER|SFGAO_HASSUBFOLDER) )//
                      {
                         //This item has sub-folders, so let's put the + in the TreeView.
                         //The first time the user clicks on the item, we'll populate the
                         //sub-folders.
                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      //OK, let's get some memory for our ITEMDATA struct
                      lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;  // Error - could not allocate memory.
   
                      //Now get the friendly name that we'll put in the treeview.
                      if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                         goto Done; // Error - could not get friendly name.

					//  if (!GetName(lpsf, lpi, SHGDN_FORPARSING, szFileName))
					  if(SHGetPathFromIDList(lpi,szFileName))
					  {		
		 				  if(!(ulAttrs & SFGAO_FOLDER) && m_bDispFile)
							  if(!MatchExtensionFilter(szFileName))
								  continue;
					  }
					  else
		 				  if(!(ulAttrs & SFGAO_FOLDER) && m_bDispFile)
							  if(!MatchExtensionFilter(szBuff))
								  continue;

                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                      //Now, make a copy of the ITEMIDLIST
                      lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
                      GetNormalAndSelectedIcons(lpifqThisItem, &tvi);
   
                      lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                      lpsf->AddRef();

                      lptvid->lpifq=ConcatPidls(lpifq, lpi);
   
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
                   // Free this items task allocator.
                   lpMalloc->Free(lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->Free(lpi);  //Free the pidl that the shell gave us.
                lpi=0;
            }
        }

    }
    else
       return;

Done:
 
    if (lpe)  
        lpe->Release();

    //The following 2 if statements will only be TRUE if we got here on an
    //error condition from the "goto" statement.  Otherwise, we free this memory
    //at the end of the while loop above.
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();
}