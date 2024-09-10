afx_msg void CModbusMDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

    CMenu MenuRButton;
    MenuRButton.CreatePopupMenu();
    MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить набор инф.объектов");
    MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон наборов инф.объектов");
    MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить набор инф.объектов");
    MenuRButton.AppendMenu(MF_SEPARATOR);
    MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");
    MenuRButton.AppendMenu(MF_STRING, IDM_COPY2, "Скопировать в буфер обмена...");

    POINT point;
    GetCursorPos(&point);
    MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
    MenuRButton.DestroyMenu();

}