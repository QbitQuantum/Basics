//------------------------------------------------------------------------
//! Send LV_DISPINFO structure as LVN_ENDLABELEDIT from CListCtrl to parent window
//!
//! @param wndListCtrl The list control starting edit
//! @param nRow The index of the row
//! @param nCol The index of the column
//! @param lvDispInfo Specifies the properties of the new cell value
//! @return Result of the SendMessage to parent window
//------------------------------------------------------------------------
LRESULT CGridColumnTraitImage::SendEndLabelEdit(CWnd& wndListCtrl, int nRow, int nCol, LV_DISPINFO& lvDispInfo)
{
	lvDispInfo.hdr.hwndFrom = wndListCtrl.m_hWnd;
	lvDispInfo.hdr.idFrom = static_cast<UINT_PTR>(wndListCtrl.GetDlgCtrlID());
	lvDispInfo.hdr.code = LVN_ENDLABELEDIT;

	lvDispInfo.item.iItem = nRow;
	lvDispInfo.item.iSubItem = nCol;

	return wndListCtrl.GetParent()->SendMessage(WM_NOTIFY, static_cast<WPARAM>(wndListCtrl.GetDlgCtrlID()), reinterpret_cast<LPARAM>(&lvDispInfo));
}