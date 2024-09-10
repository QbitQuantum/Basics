BOOL CGeneralMsgBox::OnInitDialog()
{
  if (!CDialog::OnInitDialog())
    return FALSE;

  SetWindowText(m_strTitle);

  // Getting the base dialog unit used in pixel <-> d.u. conversion
  CRect rc(0, 0, CX_DLGUNIT_BASE, CY_DLGUNIT_BASE);
  MapDialogRect(rc);

  m_dimDlgUnit = rc.Size();

  // Creating the nested controls
  CreateRtfCtrl();
  CreateIcon();
  CreateBtns();

  // Updating the layout - preparing to show
  UpdateLayout();

  // Disabling the ESC key
  if (m_uiEscCmdId == (UINT)IDC_STATIC)
    ModifyStyle(WS_SYSMENU, NULL);

  // Focusing and setting the defaul button
  if (m_uiDefCmdId != (UINT)IDC_STATIC) {
    GetDlgItem(m_uiDefCmdId)->SetFocus();
    SetDefID(m_uiDefCmdId);

    return FALSE;
  }

  return TRUE;
}