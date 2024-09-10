_Check_return_ HRESULT CAclDlg::GetSelectedItems(ULONG ulFlags, ULONG ulRowFlags, _In_ LPROWLIST* lppRowList)
{
    if (!lppRowList || !m_lpContentsTableListCtrl)
        return MAPI_E_INVALID_PARAMETER;

    *lppRowList = NULL;
    HRESULT hRes = S_OK;
    int iNumItems = m_lpContentsTableListCtrl->GetSelectedCount();

    if (!iNumItems) return S_OK;
    if (iNumItems > MAXNewROWLIST) return MAPI_E_INVALID_PARAMETER;

    LPROWLIST lpTempList = NULL;

    EC_H(MAPIAllocateBuffer(CbNewROWLIST(iNumItems),(LPVOID*) &lpTempList));

    if (lpTempList)
    {
        lpTempList->cEntries = iNumItems;
        int iArrayPos = 0;
        int iSelectedItem = -1;

        for (iArrayPos = 0 ; iArrayPos < iNumItems ; iArrayPos++)
        {
            lpTempList->aEntries[iArrayPos].ulRowFlags = ulRowFlags;
            lpTempList->aEntries[iArrayPos].cValues = 0;
            lpTempList->aEntries[iArrayPos].rgPropVals = 0;
            iSelectedItem = m_lpContentsTableListCtrl->GetNextItem(
                                iSelectedItem,
                                LVNI_SELECTED);
            if (-1 != iSelectedItem)
            {
                SortListData* lpData = (SortListData*) m_lpContentsTableListCtrl->GetItemData(iSelectedItem);
                if (lpData)
                {
                    if (ulFlags & ACL_INCLUDE_ID && ulFlags & ACL_INCLUDE_OTHER)
                    {
                        LPSPropValue lpSPropValue = NULL;
                        EC_H(MAPIAllocateMore(2 * sizeof(SPropValue), lpTempList, (LPVOID*)&lpTempList->aEntries[iArrayPos].rgPropVals));

                        lpTempList->aEntries[iArrayPos].cValues = 2;

                        lpSPropValue = PpropFindProp(
                                           lpData->lpSourceProps,
                                           lpData->cSourceProps,
                                           PR_MEMBER_ID);

                        lpTempList->aEntries[iArrayPos].rgPropVals[0].ulPropTag = lpSPropValue->ulPropTag;
                        lpTempList->aEntries[iArrayPos].rgPropVals[0].Value = lpSPropValue->Value;

                        lpSPropValue = PpropFindProp(
                                           lpData->lpSourceProps,
                                           lpData->cSourceProps,
                                           PR_MEMBER_RIGHTS);

                        lpTempList->aEntries[iArrayPos].rgPropVals[1].ulPropTag = lpSPropValue->ulPropTag;
                        lpTempList->aEntries[iArrayPos].rgPropVals[1].Value = lpSPropValue->Value;
                    }
                    else if (ulFlags & ACL_INCLUDE_ID)
                    {
                        lpTempList->aEntries[iArrayPos].cValues = 1;
                        lpTempList->aEntries[iArrayPos].rgPropVals = PpropFindProp(
                                    lpData->lpSourceProps,
                                    lpData->cSourceProps,
                                    PR_MEMBER_ID);
                    }
                }
            }
        }
    }

    *lppRowList = lpTempList;
    return hRes;
} // CAclDlg::GetSelectedItems