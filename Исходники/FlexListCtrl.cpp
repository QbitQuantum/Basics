/*******************************************************************************
 Function Name  : vShowControl
 Inputs         : nRow      - Index of the Row
                  nColumn   - Index of the Column
 Output         :   -
 Description    : This function will show the UI control to change the list item
                  text. This will get the type information from the Cmap and
                  will call approp. function to create and show that control.
 Member of      : CFlexListCtrl
 Author(s)      : Raja N
 Date Created   : 22.07.2004
 Modifications  : Raja N on 30.07.2004, Code review comments implemented
*******************************************************************************/
void CFlexListCtrl::vShowControl(int nItem, int nSubItem)
{
    // Proceed only for a valid entry
    if( nItem >= 0 && nSubItem >= 0)
    {
        SLISTINFO sInfo;
        SNUMERICINFO    sNumInfo;
        SUSERPROGINFO   sProgInfo;
        CString omStr = STR_EMPTY;
        // Got the entry type from the CMap
        if( m_omListItemType.Lookup(
                    lGetMapID(nItem, nSubItem) , sInfo) == TRUE )
        {
            // Begining of Controls creation
            m_bCreating = TRUE;
            switch( sInfo.m_eType)
            {
            // Numeric Edit box with or with out Spin Control
            case eNumber:
            case eBuddy:
                // Get the numeric control parameters
                if( m_omNumDetails.Lookup( lGetMapID(nItem, nSubItem),
                                           sNumInfo ) == TRUE )
                {
                    pomNumItem(nItem, nSubItem, sNumInfo);
                }
                else
                {
                    // Numeric info is not set
                    ASSERT( FALSE );
                    // Call with default value
                    pomNumItem(nItem, nSubItem, sNumInfo);
                }
                break;
            // General Edit control
            case eText:
                pomEditItem(nItem, nSubItem);
                break;
            // Editalble Combo Box
            case eComboList:
                pomComboList(nItem, nSubItem, sInfo.m_omEntries);
                break;
            // Non - Editable combo box
            case eComboItem:
                pomComboItem(nItem, nSubItem, sInfo.m_omEntries);
                break;
            // User function will be executed
            case eUser:
                // Get the user program pointer and parameter details
                if( m_omUserProg.Lookup( lGetMapID(nItem, nSubItem),
                                         sProgInfo ) == TRUE )
                {
                    sProgInfo.m_pfHandler( this,
                                           nItem,
                                           nSubItem,
                                           sProgInfo.m_pUserParam);
                }
                else
                {
                    // User program information is not set
                    ASSERT( FALSE );
                }
                break;
            // Toggling type control
            case eBool:
                // Get the current text
                omStr = GetItemText(nItem, nSubItem);
                // Compare with the first item
                if( sInfo.m_omEntries.GetAt(0).Compare(omStr) == 0 )
                {
                    // Toggle the first with the second item text.
                    omStr = sInfo.m_omEntries.GetAt(1);
                }
                // Compare with the Second item
                else if( sInfo.m_omEntries.GetAt(1).Compare(omStr) == 0 )
                {
                    // Replace with the first item
                    omStr = sInfo.m_omEntries.GetAt(0);
                }
                // If it is not matching with these two items nothing will
                // happen. This could be used to disable the control

                // For boolean type this is the end of Controls creation
                m_bCreating = FALSE;

                // For boolean send the EndLAbleEdit message here itself
                LV_DISPINFO lvDispInfo;
                lvDispInfo.hdr.hwndFrom = m_hWnd;
                lvDispInfo.hdr.idFrom = GetDlgCtrlID();
                lvDispInfo.hdr.code = LVN_ENDLABELEDIT;
                lvDispInfo.item.mask = LVIF_TEXT;
                lvDispInfo.item.iItem = nItem;
                lvDispInfo.item.iSubItem = nSubItem;
                lvDispInfo.item.pszText = LPTSTR((LPCTSTR)omStr);
                lvDispInfo.item.cchTextMax = omStr.GetLength();
                SendMessage( WM_NOTIFY, GetDlgCtrlID(),(LPARAM)&lvDispInfo);
                break;
            default:
                // Unknown control type
                ASSERT( FALSE );
            }
            // End of Controls
            m_bCreating = FALSE;
        }
    }
}