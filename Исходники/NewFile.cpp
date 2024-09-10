BOOL CNewFile::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add ouselves to the clipboard chain so we find out when cb changes (via WM_DRAWCLIPBOARD)
	next_cb_hwnd_ = SetClipboardViewer();

	// We have hijacked the "New File" dialog for the purpose of inserting a 
	// block filled in the same ways as the new file dialog.  The only diff.
	// to the dialog is the title (and IDC_FILL_DISK check box is hidden).
	if (insert_block_mode_)
		SetWindowText(_T("Insert Block"));

	// Check if text or binary data available from clipboard and get first bit as a sample
	check_clipboard();

	ASSERT(GetDlgItem(IDC_SPIN_SIZE_FACTOR) != NULL);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SIZE_FACTOR))->SetRange32(1, INT_MAX);

	ASSERT(GetDlgItem(IDC_SPIN_DECIMAL_SIZE) != NULL);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DECIMAL_SIZE))->SetRange32(0, INT_MAX);
	ctl_hex_size_.set_right_align();
	ctl_hex_value_.set_group_by(2);

	char buf[24];

	// Update the decimal number
	//sprintf(buf, "%I64u", (__int64(fill_.size_high)<<32) + fill_.size_low);
	sprintf(buf, "%I64u", __int64(fill_size_));
	ctl_decimal_size_.SetWindowText(buf);
	ctl_decimal_size_.add_commas();

	// Update the hex number
	//sprintf(buf, "%I64x", (__int64(fill_.size_high)<<32) + fill_.size_low);
	sprintf(buf, "%I64x", __int64(fill_size_));
	ctl_hex_size_.SetWindowText(buf);
	ctl_hex_size_.add_spaces();

	// Update the repeat count
	sprintf(buf, "%I64u", __int64(fill_repeat_));
	ctl_size_factor_.SetWindowText(buf);
	ctl_size_factor_.add_commas();

	in_update_ = FALSE;

	fix_controls();

	return TRUE;
}