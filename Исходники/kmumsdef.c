BOOL
bGetPrnModel(HANDLE hModule, 
	     LPWSTR pPrinterModel,
	     PMOPIERDM* pmdmDefault,
	     PPRNPROPSHEET* pPrnPropSheet)
{
  BOOL result = FALSE;
  WCHAR matchedPrinterModel[MAX_RES_STR_CHARS];

TRY
  ASSERT(pPrinterModel);

  /* 1) If a valid printer model is given, try to match that first.
   */
  if(pPrinterModel) {
    if(OEMLoadString(hModule, IDS_CUI_JONAH_VER, matchedPrinterModel, MAX_RES_STR_CHARS))
      if(wcscmp(pPrinterModel, matchedPrinterModel) == 0) {
	if(pmdmDefault) {
	  *pmdmDefault = &JonahDM;
	  result = TRUE;
	}
	if(pPrnPropSheet) {
	  *pPrnPropSheet = &JonahSheet;
#ifdef UI
	  result = bFillMBwResources(hModule, *pPrnPropSheet);
#else
	  result = TRUE;
#endif /* UI */
	}
	LEAVE;
      }
    
    if(OEMLoadString(hModule, IDS_CUI_SI_VER, matchedPrinterModel, MAX_RES_STR_CHARS))
      if(wcscmp(pPrinterModel, matchedPrinterModel) == 0) {
	if(pmdmDefault) {
	  *pmdmDefault = &EclipseDM;
	  result = TRUE;
	}
	if(pPrnPropSheet) {
	  *pPrnPropSheet = &EclipseSheet;
#ifdef UI
	  result = bFillMBwResources(hModule, *pPrnPropSheet);
#else
	  result = TRUE;
#endif /* UI */
	}
	LEAVE;
      }
    
    if(OEMLoadString(hModule, IDS_CUI_ECLIPSE_VER, matchedPrinterModel, MAX_RES_STR_CHARS))
      if(wcscmp(pPrinterModel, matchedPrinterModel) == 0) {
	if(pmdmDefault) {
	  *pmdmDefault = &SiDM;
	  result = TRUE;
	}
	if(pPrnPropSheet) {
	  *pPrnPropSheet = &SiSheet;
#ifdef UI
	  result = bFillMBwResources(hModule, *pPrnPropSheet);
#else
	  result = TRUE;
#endif /* UI */
	}
	LEAVE;
      }
  }

ENDTRY
    
FINALLY
ENDFINALLY
  return result;
}