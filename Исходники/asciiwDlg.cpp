void CAsciiwDlg::OnViewDec() {
  checkMenuItem(this,ID_VIEW_DEC,true );
  checkMenuItem(this,ID_VIEW_HEX,false);
  Invalidate(true);
}