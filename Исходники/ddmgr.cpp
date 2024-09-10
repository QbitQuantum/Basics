///////////////////////////////////////////////////
//Copy this object out to the clipboard or drag/drop
//buffer based on Keith Rule's
//serialization algorithm
//from the MFC Programmer's Sourcebook website,
//and Chapter 1 of "the Essence of OLE with Active X"
//by David S. Platt.
//
//pDropEffect is only set if doing a drag-drop.
//
//You usually call this function from:
//
//1) Your view class's OnLButtonDown() method
//   when starting a drag-drop.
//
//2) Your document class when copying data
//   to the clipboard.
///////////////////////////////////////////////////
BOOL CDragDropMgr::PrepareDrop(
                   BOOL        bToClipboard,
                   LPCTSTR     lpstrFormat,
                   CObject*    pObj,
                   DROPEFFECT* pDropEffect,
                   LPCTSTR     lpstrFormat2,
                   CObject*    pObj2)
{
    if (pObj == NULL)
        return FALSE;

    CSharedFile sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
    CSharedFile sf2(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

    UINT format = ::RegisterClipboardFormat(lpstrFormat);

    if (format == 0)
        return FALSE;

    TRY
    {
        CArchive ar(&sf, CArchive::store);

        pObj->Serialize(ar);

        ar.Close();

        HGLOBAL hMem = sf.Detach();

        if (hMem == NULL)
            return FALSE;

        COleDataSource* pSrc = new COleDataSource();

        if (pSrc == NULL)
            return FALSE;
    
        pSrc->CacheGlobalData(format,hMem);

		if (pObj2) { // special case for when the second data type is a filelist
			UINT format2 = (strcmp(lpstrFormat2, "CF_HDROP") ? ::RegisterClipboardFormat(lpstrFormat2) : CF_HDROP);
			if (format2 != CF_HDROP) {
				CArchive ar2(&sf2, CArchive::store);

				pObj2->Serialize(ar2);
		
				ar2.Close();

				HGLOBAL hMem2 = sf2.Detach();

				if (hMem2 == NULL)
					return FALSE;

				pSrc->CacheGlobalData(format2,hMem2);
			}
			else { // fake file list
				DROPFILES *pDrop = (DROPFILES*)pObj2;
				HGLOBAL hgDrop = GlobalAlloc ( GHND | GMEM_SHARE, sizeof(DROPFILES)+1 );
				DROPFILES *pDrop2 = (DROPFILES*) GlobalLock ( hgDrop );
				memcpy((void*)pDrop2, (void*)pDrop, sizeof(DROPFILES)+1);
				GlobalUnlock(hgDrop);
				pSrc->CacheGlobalData(format2, hgDrop);
			}
		}
    
        //Pasting to the clipboard:
        //do not free the data source
        //(OLE will free it when no longer needed)
        if (bToClipboard)
            pSrc->SetClipboard();
    
        //Starting a drag-drop:
        //Set the type of drag-drop effect, and
        //free the data source object.
        //OLE has created a data source object in
        //the drag-drop global cache; it's
        //not our problem anymore...
        else if (pDropEffect != NULL)
        {
            *pDropEffect = pSrc->DoDragDrop();

            delete pSrc;
        }

        return TRUE;
    }   //catch

    CATCH_ALL(ce)
    {
        return FALSE;
    }
    END_CATCH_ALL
}