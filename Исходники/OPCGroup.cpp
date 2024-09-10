/////////////////////////////////////////////////////////////////////
// OPCGroup::SyncRead method
STDMETHODIMP COPCGroupImpl::SyncRead( SHORT Source,
                        LONG NumItems,
                        SAFEARRAY ** ppServerHandles,
                        SAFEARRAY ** ppValues,
                        SAFEARRAY ** ppErrors,
                        VARIANT *pQualities,    // \/ Optional \/
                        VARIANT *pTimeStamps)
{
   // Validate input types
   if(*ppServerHandles == NULL)
      return E_INVALIDARG;
   if(ppValues == NULL)
      return E_INVALIDARG;
   if(ppErrors == NULL)
      return E_INVALIDARG;

   if( !m_pSyncIO )
   {
      m_pSyncIO = m_pOPCGroup;   // get Sync interface
      if( !m_pSyncIO )
         return E_FAIL;
   }

   HRESULT hr = S_OK;
   LONG lBound=0;
   LONG uBound=0;
   hr = SafeArrayGetLBound(*ppServerHandles, 1, &lBound);
   if( FAILED(hr) )
      return hr;
   hr = SafeArrayGetUBound(*ppServerHandles, 1, &uBound);
   if( FAILED(hr) )
      return hr;
   if( lBound > 1 )
      return E_INVALIDARG;
   if( uBound < NumItems )
      return E_INVALIDARG;

   // Create array of handles
   OPCHANDLE* pSHandles = (OPCHANDLE*)_alloca(NumItems*sizeof(OPCHANDLE));
   memset( pSHandles, 0, NumItems*sizeof(OPCHANDLE) );
   for( long index=0; index<NumItems; index++ )
      {
      LONG vbIndex = index+1;
      DWORD localHandle=0;
      hr = SafeArrayGetElement(*ppServerHandles, &vbIndex, &localHandle);
      if( FAILED(hr) )
         return hr;
      COPCItem* pItem = (COPCItem*)localHandle;
//      if( !m_items.Lookup( (LPVOID)localHandle, pItem ) )
//         return E_INVALIDARG;
      pSHandles[index] = pItem->GetServerHandle();
      }

   // call the server
   OPCITEMSTATE* pItemState;
   HRESULT *pErrors=0;
   hr = m_pSyncIO->Read( (OPCDATASOURCE)Source,
                         (DWORD)NumItems,
                         pSHandles,
                         &pItemState,
                         &pErrors);
   if( FAILED( hr ) )
   {
      return hr;
   }

   // Return Values in a SAFEARRAY and update each COPCItem
   {
      SAFEARRAYBOUND bound;
      bound.lLbound = 1;
      bound.cElements = NumItems;
      SAFEARRAY *pArray = SafeArrayCreate(VT_VARIANT, 1, &bound);
      if(pArray == NULL)
         return E_FAIL;    // temp
      for( long index=0; index<NumItems; index++ )
      {
         LONG vbIndex = index+1;
         VariantToAutomation(&pItemState[index].vDataValue);
         SafeArrayPutElement(pArray, &vbIndex, (void *)&pItemState[index].vDataValue);
         if( SUCCEEDED(pErrors[index]) )
         {
            COPCItem* pItem = (COPCItem*)pItemState[index].hClient;
            pItem->Update( &pItemState[index] );
         }
         VariantClear( &pItemState[index].vDataValue );
      }
      *ppValues = pArray;
   }

   // Return errors in a SAFEARRAY
   {
      SAFEARRAYBOUND bound;
      bound.lLbound = 1;
      bound.cElements = NumItems;
      SAFEARRAY *pArray = SafeArrayCreate(VT_I4, 1, &bound);
      if(pArray == NULL)
         return E_FAIL;    // temp
      for( long index=0; index<NumItems; index++ )
      {
         LONG vbIndex = index+1;
         SafeArrayPutElement(pArray, &vbIndex, (void *)&pErrors[index]);
      }
      *ppErrors = pArray;
   }

   // Return qualities in a SAFEARRAY
   if(pQualities != NULL && pQualities->scode != DISP_E_PARAMNOTFOUND )
   {
      VariantClear( pQualities );
      SAFEARRAYBOUND bound;
      bound.lLbound = 1;
      bound.cElements = NumItems;
      SAFEARRAY *pArray = SafeArrayCreate(VT_I2, 1, &bound);
      if(pArray == NULL)
         return E_FAIL;    // temp
      for( long index=0; index<NumItems; index++ )
      {
         LONG vbIndex = index+1;
         SafeArrayPutElement(pArray, &vbIndex, (void *)&pItemState[index].wQuality);
      }
      pQualities->vt = VT_I2 | VT_ARRAY;
      pQualities->parray = pArray;
   }

   // Return timestamps in a SAFEARRAY
   if(pTimeStamps != NULL && pTimeStamps->scode != DISP_E_PARAMNOTFOUND )
   {
      VariantClear( pTimeStamps );
      SAFEARRAYBOUND bound;
      bound.lLbound = 1;
      bound.cElements = NumItems;
      SAFEARRAY *pArray = SafeArrayCreate(VT_DATE, 1, &bound);
      if(pArray == NULL)
         return E_FAIL;    // temp
      for( long index=0; index<NumItems; index++ )
      {
         LONG vbIndex = index+1;
         DATE timeStamp = NULL; 
         FILETIME filetimeLocal;
         if( FileTimeToLocalFileTime( &pItemState[index].ftTimeStamp, &filetimeLocal) )
         {
            SYSTEMTIME systime;
            if( FileTimeToSystemTime(&filetimeLocal, &systime) )
            {
	            SystemTimeToVariantTime( &systime, &timeStamp);
	         }
         }
         SafeArrayPutElement(pArray, &vbIndex, (void *)&timeStamp);
      }
      pTimeStamps->vt = VT_DATE | VT_ARRAY;
      pTimeStamps->parray = pArray;
   }

   CoTaskMemFree( pItemState );
   CoTaskMemFree( pErrors );

   return S_OK;
}