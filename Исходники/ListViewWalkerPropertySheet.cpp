void CListViewWalkerPropertySheet::InsertPage(int iIndex, CPropertyPage* pPage)
{
    ASSERT_VALID( this );
    ASSERT( pPage != NULL );
    ASSERT_KINDOF( CPropertyPage, pPage );
    ASSERT_VALID( pPage );

    m_pages.InsertAt(iIndex, pPage);
    BuildPropPageArray();

    if (m_hWnd != NULL)
    {
        PROPSHEETPAGE* ppsp = const_cast<PROPSHEETPAGE*>(m_psh.ppsp);
        for (UINT i = 0; i < m_psh.nPages; i++) {
            if (i == (UINT)iIndex)
                break;
            (BYTE*&)ppsp += ppsp->dwSize;
        }

        HPROPSHEETPAGE hPSP = CreatePropertySheetPage(ppsp);
        if (hPSP == NULL)
            AfxThrowMemoryException();

        if (!SendMessage(PSM_INSERTPAGE, iIndex, (LPARAM)hPSP)) {
            DestroyPropertySheetPage(hPSP);
            AfxThrowMemoryException();
        }
    }
}