/*======================================================================= 
Function: SamplePosDet_QosSettings_HandleEvent()

Description: 
   Event handler function for the QoS settings menu.

Prototype:

   boolean SamplePosDet_QosSettings_HandleEvent(CSamplePosDet *pMe, AEEEvent eCode,
                                                 uint16 wParam, uint32 dwParam)

Parameters:
   pMe: [in]. CSamplePosDet instance.
   eCode: [in]. Event code.
   wParam: [in]. Event wParam.
   dwParam: [in]. Event dwParam.

Return Value:

   TRUE - If the event was handled by this menu.
   FALSE - If the event was not handled.
 
Comments:  
   None

Side Effects: 
   None

See Also:
   None
=======================================================================*/
boolean SamplePosDet_QosSettings_HandleEvent(CSamplePosDet *pMe, AEEEvent eCode,
                                                 uint16 wParam, uint32 dwParam)
{
   boolean bHandled = FALSE;
   CTextCtlData *ptcd = SamplePosDet_GetScreenData( pMe );
   ITextCtl *pTextCtl = NULL;
   IMenuCtl *pSoftKeyMenu = NULL;
   char * pszStr;
   AECHAR * pQos;
   uint32 nResult;

   if (ptcd) {
      pSoftKeyMenu = ptcd->pSoftKey;
      pTextCtl = ptcd->pTextCtl;
   }

   switch( eCode ) {
   case EVT_SCREEN:
      if( wParam == SCREEN_PARAM_INIT ) {
         if( pTextCtl ) {  /* This is not expected to happen */
            SamplePosDet_DrawScreen( pMe, 0 );
            bHandled = TRUE;
         }
         else {
            if( ISHELL_CreateInstance( pMe->theApp.m_pIShell, AEECLSID_TEXTCTL, 
               (void **)&pTextCtl ) == SUCCESS ) {
               if (ISHELL_CreateInstance(pMe->theApp.m_pIShell, AEECLSID_SOFTKEYCTL,
                  (void **)&pSoftKeyMenu) == SUCCESS) {

                  IMENUCTL_AddItem( pSoftKeyMenu, SAMPLEPOSDET_RES_FILE, IDS_SOFTKEY_SAVE,
                     IDS_SOFTKEY_SAVE, NULL, (uint32)pSoftKeyMenu );

                  ITEXTCTL_SetSoftKeyMenu( pTextCtl, pSoftKeyMenu );
                  ITEXTCTL_SetTitle( pTextCtl, SAMPLEPOSDET_RES_FILE, IDS_QOS_SETTINGS_TITLE, NULL );
                  ITEXTCTL_SetInputMode( pTextCtl, AEE_TM_NUMBERS );

                  // Load the current QoS value, if it exists
                  pszStr = MALLOC(50);
                  pQos = MALLOC(100);
                  SPRINTF(pszStr, "%d", pMe->gpsSettings.qos);
                  STRTOWSTR(pszStr, pQos, 100);
                  ITEXTCTL_SetText(pTextCtl, pQos, -1);
                  FREE(pszStr);
                  FREE(pQos);

                  ptcd = MALLOC( sizeof(CTextCtlData) );

                  ptcd->pSoftKey = pSoftKeyMenu;
                  ptcd->pTextCtl = pTextCtl;
                  SamplePosDet_SetScreenData( pMe, (void *)ptcd );
                  SamplePosDet_DrawScreen( pMe, 0 );
                  bHandled = TRUE;
               }
            }
         }
      }
      else if( wParam == SCREEN_PARAM_CLOSE ) {
         ITEXTCTL_Release( pTextCtl );
         IMENUCTL_Release( pSoftKeyMenu );
         FREE( ptcd );
         SamplePosDet_SetScreenData( pMe, 0 );
         pMe->currentHandler = 0;
         bHandled = TRUE;
      }
      else if( wParam == SCREEN_PARAM_PAINT ) {
         if( ITEXTCTL_IsActive( pTextCtl ) ) {
            ITEXTCTL_Redraw( pTextCtl );
         }
         else {
            ITEXTCTL_SetActive( pTextCtl, TRUE );  /* Also causes a menu draw */
         }
      }
      break;

   case EVT_KEY:
   case EVT_KEY_PRESS:
   case EVT_KEY_RELEASE:
      bHandled = ITEXTCTL_HandleEvent( pTextCtl, eCode, wParam, dwParam );
      if (!bHandled) {
         bHandled = IMENUCTL_HandleEvent( pSoftKeyMenu, eCode, wParam, dwParam );
         
         if(!bHandled && wParam == AVK_CLR && eCode == EVT_KEY) {
            SamplePosDet_GotoScreen( pMe, SCREENID_CONFIG, 0 );
            bHandled = TRUE;
         }
      }
      break;
   case EVT_COMMAND:
      bHandled = ITEXTCTL_HandleEvent( pTextCtl, eCode, wParam, dwParam );
      if (!bHandled) {
         if (IDS_SOFTKEY_SAVE == wParam) {
            // Need to validate and save the Port settings here
            pQos = ITEXTCTL_GetTextPtr(pTextCtl);
            pszStr = MALLOC(50);
            WSTRTOSTR(pQos, pszStr, 50);
            nResult = STRTOUL(pszStr, NULL, 10);
            if (nResult >= 0 && nResult <= 255) {
               pMe->gpsSettings.qos = (AEEGPSQos)nResult;
               SamplePosDet_SaveGPSSettings(pMe);
               SamplePosDet_GotoScreen(pMe, SCREENID_CONFIG, 0);
            }
            else {
               ITEXTCTL_SetTitle(pTextCtl, SAMPLEPOSDET_RES_FILE, IDS_QOS_SETTINGS_INVALID, NULL);
               ITEXTCTL_Redraw(pTextCtl);
            }
            FREE(pszStr);
            bHandled = TRUE;
         }
      }
      break;
   }
   return bHandled;
}