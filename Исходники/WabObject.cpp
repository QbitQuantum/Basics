HRESULT CWAB::IterateWABContents(CWabIterator *pIter, int *pDone)
{
  if (!m_bInitialized || !m_lpAdrBook)
    return( E_FAIL);

  ULONG      ulObjType =   0;
  LPMAPITABLE    lpAB =  NULL;
  ULONG      cRows =       0;
  LPSRowSet    lpRowAB = NULL;
  LPABCONT    lpContainer = NULL;
  int        cNumRows = 0;
  nsresult      keepGoing;

  HRESULT      hr = E_FAIL;

  ULONG      lpcbEID = 0;
  LPENTRYID    lpEID = NULL;
  ULONG      rowCount = 0;
  ULONG      curCount = 0;

  nsString    uniStr;

  // Get the entryid of the root PAB container
  //
  hr = m_lpAdrBook->GetPAB( &lpcbEID, &lpEID);

  if (HR_FAILED( hr))
    goto exit;

  ulObjType = 0;

  // Open the root PAB container
  // This is where all the WAB contents reside
  //
  hr = m_lpAdrBook->OpenEntry(lpcbEID,
    (LPENTRYID)lpEID,
    NULL,
    0,
    &ulObjType,
    (LPUNKNOWN *)&lpContainer);

  m_lpWABObject->FreeBuffer(lpEID);

  lpEID = NULL;

  if(HR_FAILED(hr))
    goto exit;

  // Get a contents table of all the contents in the
  // WABs root container
  //
  hr = lpContainer->GetContentsTable( 0,
    &lpAB);

  if(HR_FAILED(hr))
    goto exit;

  hr = lpAB->GetRowCount( 0, &rowCount);
  if (HR_FAILED(hr))
    rowCount = 100;
  if (rowCount == 0)
    rowCount = 1;

  // Order the columns in the ContentsTable to conform to the
  // ones we want - which are mainly DisplayName, EntryID and
  // ObjectType
  // The table is gauranteed to set the columns in the order
  // requested
  //
  hr =lpAB->SetColumns( (LPSPropTagArray)&ptaEid, 0 );

  if(HR_FAILED(hr))
    goto exit;


  // Reset to the beginning of the table
  //
  hr = lpAB->SeekRow( BOOKMARK_BEGINNING, 0, NULL );

  if(HR_FAILED(hr))
    goto exit;

  // Read all the rows of the table one by one
  //

  do {

    hr = lpAB->QueryRows(1,  0, &lpRowAB);

    if(HR_FAILED(hr))
      break;

    if(lpRowAB)
    {
      cNumRows = lpRowAB->cRows;

      if (cNumRows)
      {
        LPTSTR lpsz = lpRowAB->aRow[0].lpProps[ieidPR_DISPLAY_NAME].Value.lpszA;
        LPENTRYID lpEID = (LPENTRYID) lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.lpb;
        ULONG cbEID = lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.cb;

        // There are 2 kinds of objects - the MAPI_MAILUSER contact object
        // and the MAPI_DISTLIST contact object
        // For the purposes of this sample, we will only consider MAILUSER
        // objects
        //
        if(lpRowAB->aRow[0].lpProps[ieidPR_OBJECT_TYPE].Value.l == MAPI_MAILUSER)
        {
          // We will now take the entry-id of each object and cache it
          // on the listview item representing that object. This enables
          // us to uniquely identify the object later if we need to
          //
          CStrToUnicode( lpsz, uniStr);
          keepGoing = pIter->EnumUser( uniStr.get(), lpEID, cbEID);
          curCount++;
          if (pDone) {
            *pDone = (curCount * 100) / rowCount;
            if (*pDone > 100)
              *pDone = 100;
          }
        }
      }
      FreeProws(lpRowAB );
    }


  } while ( SUCCEEDED(hr) && cNumRows && lpRowAB && NS_SUCCEEDED(keepGoing) )  ;

  hr = lpAB->SeekRow( BOOKMARK_BEGINNING, 0, NULL );

  if(HR_FAILED(hr))
    goto exit;

  // Read all the rows of the table one by one
  //
  keepGoing = TRUE;
  do {

    hr = lpAB->QueryRows(1,  0, &lpRowAB);

    if(HR_FAILED(hr))
      break;

    if(lpRowAB)
    {
      cNumRows = lpRowAB->cRows;

      if (cNumRows)
      {
        LPTSTR lpsz = lpRowAB->aRow[0].lpProps[ieidPR_DISPLAY_NAME].Value.lpszA;
        LPENTRYID lpEID = (LPENTRYID) lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.lpb;
        ULONG cbEID = lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.cb;

        // There are 2 kinds of objects - the MAPI_MAILUSER contact object
        // and the MAPI_DISTLIST contact object
        // For the purposes of this sample, we will only consider MAILUSER
        // objects
        //
        if(lpRowAB->aRow[0].lpProps[ieidPR_OBJECT_TYPE].Value.l == MAPI_DISTLIST)
        {
          LPABCONT distListContainer = NULL;
          // We will now take the entry-id of each object and cache it
          // on the listview item representing that object. This enables
          // us to uniquely identify the object later if we need to
          //
          hr = m_lpAdrBook->OpenEntry(cbEID, lpEID, NULL,
            0,&ulObjType,(LPUNKNOWN *)&distListContainer);

          LPMAPITABLE    distListTable =  NULL;


          // Get a contents table of the dist list
          //
          hr = distListContainer->GetContentsTable( 0, &distListTable);
          if (lpAB)
          {
            hr = distListTable->GetRowCount( 0, &rowCount);
            if (HR_FAILED(hr))
              rowCount = 100;
            if (rowCount == 0)
              rowCount = 1;

            // Order the columns in the ContentsTable to conform to the
            // ones we want - which are mainly DisplayName, EntryID and
            // ObjectType
            // The table is gauranteed to set the columns in the order
            // requested
            //
            hr = distListTable->SetColumns( (LPSPropTagArray)&ptaEid, 0 );
            CStrToUnicode( lpsz, uniStr);
            keepGoing = pIter->EnumList( uniStr.get(), lpEID, cbEID, distListTable);
            curCount++;
            if (pDone) {
              *pDone = (curCount * 100) / rowCount;
              if (*pDone > 100)
                *pDone = 100;
            }
          }
          if (distListContainer)
            distListContainer->Release();
          if (distListTable)
            distListTable->Release();
        }
      }
      FreeProws(lpRowAB );
    }

  } while ( SUCCEEDED(hr) && cNumRows && lpRowAB && NS_SUCCEEDED(keepGoing) )  ;


exit:

  if ( lpContainer )
    lpContainer->Release();

  if ( lpAB )
    lpAB->Release();

  return hr;
}