//*****************************************************************************
void CBCGPDBGridCtrl::Sort (int nColumn, BOOL bAscending, BOOL bAdd)
{
    if (m_bIsSorting || !CanSortByColumn (nColumn))
    {
        return;
    }

    if (!m_bDbSort || m_strSQL.IsEmpty ())
    {
        CBCGPGridCtrl::Sort (nColumn, bAscending, bAdd);
        return;
    }

    SetCurSel (NULL);

    m_CachedItems.CleanUpCache ();

    CString strSQLOrign = m_strSQL;

    CString strColumn = GetColumnName (nColumn);
    if (strColumn.Find (_T(' ')) >= 0)
    {
        strColumn = _T('\'') + strColumn + _T('\'');
    }

    CString strSQL;
    strSQL.Format (_T("%s ORDER BY %s %s"),
                   m_strSQL, strColumn,
                   bAscending ? _T(" ASC") : _T(" DESC"));

    if (bAdd)
    {
        for (POSITION pos = m_Columns.m_mapSortColumn.GetStartPosition (); pos != NULL; )
        {
            int nListColumn, nState;

            m_Columns.m_mapSortColumn.GetNextAssoc (pos, nListColumn, nState);

            if (nState != 0 && nListColumn != nColumn)
            {
                CString strListColumn = GetColumnName (nListColumn);
                if (strListColumn.Find (_T(' ')) >= 0)
                {
                    strListColumn = _T('\'') + strListColumn + _T('\'');
                }

                CString strOrder;
                strOrder.Format (_T(", %s %s"),
                                 strListColumn,
                                 nState > 0 ? _T(" ASC") : _T(" DESC"));

                strSQL += strOrder;
            }
        }
    }

    CWaitCursor wait;

    m_bRebuildTerminalItems = TRUE;

    m_bIsSorting = TRUE;

    if (OpenSQL (strSQL))
    {
        m_Columns.SetSortColumn (nColumn, bAscending, bAdd);
    }

    RedrawWindow (m_rectHeader);

    m_bIsSorting = FALSE;
    m_strSQL = strSQLOrign;
}