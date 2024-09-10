void DFUFileDialog::OnSize(UINT nType, int cx, int cy) 
{
	// Pass on to the base class first
	CFileDialog::OnSize(nType, cx, cy);

	// Move the preview control
	CWnd *parent = GetParent();
	WINDOWPLACEMENT placement;
	RECT rect;
	parent->GetDlgItem(cmb1)->GetWindowPlacement(&placement);
	rect = placement.rcNormalPosition;
	parent->GetDlgItem(stc2)->GetWindowPlacement(&placement);
	rect.left = placement.rcNormalPosition.left;
	editPreview.MoveWindow(&rect);
}