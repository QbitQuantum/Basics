BOOLEAN
BufferDisplay_Init(
    IN  HWND                hCB,
    IN  HWND                hEB,
    IN  INT                 nBuffers,
    IN  INT                 iBufferSize,
    IN  HIDP_REPORT_TYPE    RType,
    __deref_out_opt PBUFFER_DISPLAY *ppBufferDisplay
)
/*++
Routine Description:
    This routine initializes the buffer display mechanism for a given report type

    The display mechanism maintains a list of list of nBuffers, where is each
    is buffer is of iBufferSize and hCB and hEB are handles to the combo box and
    edit box for displaying the buffer.

    The variable ppBufferDisplay is allocated block which is passed into other
    buffer routines and contains information about the buffer for the other
    routines.

    This function will return FALSE if there was a problem allocating memory
--*/
{
#pragma warning(push)
#pragma warning(disable:28197) //  BufferDisplay_Destroy frees memory   
    PBUFFER_DISPLAY pNewDisplay;
    UINT            reportBuffersSize = 0;
    CHAR            *pszBufferHeader;
    CHAR            szBufferName[24];
    UINT            iIndex;
    UINT            iCBIndex;

    pNewDisplay = (PBUFFER_DISPLAY) malloc(sizeof(BUFFER_DISPLAY));

    *ppBufferDisplay = NULL;

    if (NULL == pNewDisplay)
    {
        return (FALSE);
    }

    if(S_OK != ULongMult(sizeof(REPORT_BUFFER), nBuffers, &reportBuffersSize))
    {
        free(pNewDisplay);
        return (FALSE);
    }

    pNewDisplay->ReportBuffers = (PREPORT_BUFFER) malloc(reportBuffersSize);

    if (NULL == pNewDisplay -> ReportBuffers)
    {
        free(pNewDisplay);
        return (FALSE);
    }

    memset(pNewDisplay -> ReportBuffers, 0x00, reportBuffersSize);

    pNewDisplay -> hBufferComboBox = hCB;
    pNewDisplay -> hBufferEditBox = hEB;
    pNewDisplay -> nReportBuffers = nBuffers;
    pNewDisplay -> iBufferSize = iBufferSize;
    pNewDisplay -> ReportType = RType;

    switch (pNewDisplay -> ReportType)
    {
    case HidP_Input:
        pszBufferHeader = "Input";
        break;

    case HidP_Output:
        pszBufferHeader = "Output";
        break;

    case HidP_Feature:
        pszBufferHeader = "Feature";
        break;

    default:
        pszBufferHeader = "Other";
        break;
    }

    for (iIndex = 0; iIndex < pNewDisplay -> nReportBuffers; iIndex++)
    {
        if(FAILED(StringCbPrintf(szBufferName, sizeof(szBufferName),
                                 "%s Buffer #%d", pszBufferHeader, iIndex)))
        {
            BufferDisplay_Destroy(pNewDisplay);
            return (FALSE);
        }

        iCBIndex = (INT) SendMessage(pNewDisplay -> hBufferComboBox,
                                     CB_ADDSTRING,
                                     0,
                                     (LPARAM) szBufferName);

        if (CB_ERR == iCBIndex || CB_ERRSPACE == iCBIndex)
        {
            BufferDisplay_Destroy(pNewDisplay);
            return (FALSE);
        }

        iCBIndex = (INT) SendMessage(pNewDisplay -> hBufferComboBox,
                                     CB_SETITEMDATA,
                                     iCBIndex,
                                     iIndex);

        if (CB_ERR == iCBIndex || CB_ERRSPACE == iCBIndex)
        {
            BufferDisplay_Destroy(pNewDisplay);
            return (FALSE);
        }
    }

    SendMessage(pNewDisplay -> hBufferComboBox, CB_SETCURSEL, 0, 0);

    BufferDisplay_ChangeSelection(pNewDisplay);

    *ppBufferDisplay = pNewDisplay;
    return (TRUE);
#pragma warning(pop)  // 28197
}