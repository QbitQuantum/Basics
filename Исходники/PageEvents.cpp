void CPageEvents::ToggleCheckBox(UINT id)
{
  CWnd* pwndCheckBox = GetDlgItem(id);
  if (!pwndCheckBox->IsWindowEnabled())
    MessageBeep(static_cast<DWORD>(-1));
  else
  {
    bool bChecked = BST_CHECKED == IsDlgButtonChecked(id);
    CheckDlgButton(id, bChecked ? BST_UNCHECKED : BST_CHECKED);
  }
}