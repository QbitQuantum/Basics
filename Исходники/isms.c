/*===========================================================================

FUNCTION ISmsApp_InitAppData

DESCRIPTION
   This function initializes app specific data.

PROTOTYPE:
  static boolean ISmsApp_InitAppData(IApplet* pi);

PARAMETERS:
  pi [in]: Pointer to the IApplet structure.

DEPENDENCIES
    None.

RETURN VALUE
    TRUE: If the app has app data is allocated and initialized successfully
    FALSE: Either app data could not be allocated or initialized

SIDE EFFECTS
    None.
===========================================================================*/
static boolean ISmsApp_InitAppData(IApplet* pi)
{
    ISmsApp * pMe = (ISmsApp*)pi;
    int charHeight, pnAscent, pnDescent;
    AEEDeviceInfo di;
    int nErr;
    int i;
    AECHAR szwStr[32];
    char szNumber[32];

#define MAX_ENC 32
    uint32 *EncodingMoSms;
    uint32 nSize;

    IModel * pIModel = NULL;
    // Make sure the pointers we'll be using are valid
    if (pMe == NULL || pMe->a.m_pIShell == NULL)
        return FALSE;

    pMe->m_pIMenu = NULL;
    pMe->m_pISMSMsg = NULL;
    pMe->m_pISMS      = NULL;
    pMe->m_pISMSStorage = NULL;



    // Determine the amount of available screen space
    ISHELL_GetDeviceInfo(pMe->a.m_pIShell,&di);

    // Determine the height of a line of text
    charHeight = IDISPLAY_GetFontMetrics (pMe->a.m_pIDisplay, AEE_FONT_NORMAL,
                                          &pnAscent, &pnDescent);

    // Number of available lines equals the available screen
    // space divided by the height of a line, minus 3 for the
    // lines we always print at the top and bottom of the screen
    pMe->m_cMaxLine = (di.cyScreen / charHeight) - 3;

    nErr =ISHELL_CreateInstance(pMe->a.m_pIShell, AEECLSID_SMS, (void **)&pMe->m_pISMS);
    DBGPRINTF("CreateInstance of AEECLSID_SMS ret %d", nErr);
    if(nErr != AEE_SUCCESS)
    {
        return FALSE;
    }

    if ((ISMS_GetEncodingsAvailableForMOSMS(pMe->m_pISMS, NULL, (uint32*)&nSize) == SUCCESS) &&
            ((EncodingMoSms = (uint32*)MALLOC(nSize)) != NULL) &&
            (ISMS_GetEncodingsAvailableForMOSMS(pMe->m_pISMS, EncodingMoSms, (uint32*)&nSize) == SUCCESS))
    {
        nSize = nSize/sizeof(uint32);
        DBGPRINTF("ISMS_GetEncodingsAvailableForMOSMS");
        DBGPRINTF("size Encode ret:%d", nSize);
        for(i=0; i<nSize; i++)
        {
            DBGPRINTF("en[%d]=%x", i, EncodingMoSms[i]);
        }
    }

    if ((nErr = ISHELL_CreateInstance(pMe->a.m_pIShell, AEECLSID_SMSSTORAGE, (void**)&pMe->m_pISMSStorage)) != SUCCESS)
    {
        DBGPRINTF("CreateInstance SMSSTORAGE ret %d", nErr);
        return FALSE;
    }

    if (pMe->m_pISMSStorage &&
            (SUCCESS == ISMSSTORAGE_QueryInterface(pMe->m_pISMSStorage, AEEIID_MODEL, (void**)&pIModel)))
    {
        IMODEL_AddListenerEx(pIModel, &pMe->m_SMSStorageModelListener, (PFNLISTENER)OATSMSStorage_ModelListener, pMe);
        IMODEL_Release(pIModel);
        pIModel = NULL;
    }

    ISHELL_LoadResString(pMe->a.m_pIShell, ISMS_RES_FILE, IDS_SMS_TAG, szwStr, sizeof(szwStr));
    WSTRTOSTR(szwStr, szNumber, sizeof(szNumber));
    pMe->m_tag = STRTOUL(szNumber, NULL, 10);

    ISHELL_LoadResString(pMe->a.m_pIShell, ISMS_RES_FILE, IDS_SMS_MT, szwStr, sizeof(szwStr));
    WSTRTOSTR(szwStr, szNumber, sizeof(szNumber));
    pMe->m_mt = STRTOUL(szNumber, NULL, 10);

    return TRUE;
}