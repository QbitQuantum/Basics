/**************************** Function Header ********************************
 * bGetOEMUIInfo 
 *    Retrieves OEM custom UI DLL info. 
 *
 * RETURNS:
 *      (BOOL) TRUE for success whether this minidriver has a custom
 *      or not. FALSE indicates an error retrieving info about a custom UI
 *      DLL that should be present. 
 *
 * HISTORY:
 *
 *****************************************************************************/
BOOL
bGetOEMUIInfo(
   PRASDDUIINFO pInfo)
{
   RES_ELEM OEMDLLName;
   BOOL bOK = FALSE;
   static LPCSTR aAPIs[OEM_IDX_MAX+1] = { OEM_WSTRDEVMODE,
                                          OEM_WSTRCOMMONUI,
                                          OEM_WSTRDEVQUERYPRINTEX,
                                          OEM_WSTRDEVICECAPS,
                                          OEM_WSTRUPGRADEPRINTER };
   ASSERT(pInfo);


TRY
   /* Bump lock count if it's already loaded.
    */
   if (pInfo->OEMUIInfo.locks) {
       pInfo->OEMUIInfo.locks++;
   }

   /* Check for UI DLL name in gpc resources. 
    */
   else if (GetWinRes(&pInfo->WinResData, 1, RC_OEMUIDLL, 
           &OEMDLLName)) {

	   DWORD dwOldErrMode;        
      wchar_t path[_MAX_PATH];
      wchar_t drive[_MAX_DRIVE];
      wchar_t dir[_MAX_DIR];
     	HINSTANCE hOEMLib;
      int i;

      /* Construct path from data file path.
       */
      _wsplitpath(pInfo->PI.pwstrDataFileName, drive, dir, 0, 0 );
     	_wmakepath(path, drive, dir, (wchar_t *) OEMDLLName.pvResData, 0 );

      /* Load DLL. It stays loaded until a call to vReleaseUIInfo.
       */
      dwOldErrMode = SetErrorMode(SEM_FAILCRITICALERRORS);
      hOEMLib = LoadLibrary(path);
      SetErrorMode(dwOldErrMode);

      if (hOEMLib == NULL) {
         LEAVE;
      } 
       
      /* Get all UI DLL entry points. If any required are missing, abort.
       */ 
      for (i = 0; i < OEM_IDX_MAX; i++) {
         pInfo->OEMUIInfo.UIEntryPoints[i] = 
               (OEM_UIENTRYPOINT) GetProcAddress(hOEMLib, aAPIs[i]);
      }
      if (pInfo->OEMUIInfo.UIEntryPoints[OEM_IDX_DEVMODE] == 0 ||
            pInfo->OEMUIInfo.UIEntryPoints[OEM_IDX_COMMONUI] == 0) {
         LEAVE;
      }
      pInfo->OEMUIInfo.cbEntryPoints = OEM_IDX_MAX+1; 
      pInfo->OEMUIInfo.hOEMLib = hOEMLib; 

      /* Mark OEM devmode's size as unknown.
       */
      pInfo->OEMUIInfo.dwDevmodeExtra = (DWORD) -1L;

      /* Allocate custom UI heap.
       */
      if ((pInfo->OEMUIInfo.hCommonUIHeap = 
            HeapCreate(0, OEMUI_INITHEAPSIZE, OEMUI_MAXHEAPSIZE))  == 0) {
         LEAVE;
      }

      /* Done
       */
      pInfo->OEMUIInfo.flags |= OEMUI_HASCUSTOMUI;
      pInfo->OEMUIInfo.locks++;
   }
   bOK = TRUE;

ENDTRY
FINALLY

   /* Clean up
    */
   if (!bOK) {
      vReleaseOEMUIInfo(pInfo);
   }

ENDFINALLY
   return(bOK);
}