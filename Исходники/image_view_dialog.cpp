void ImageViewDialog::OnRButtonDown(UINT nFlags, CPoint point) {
  CMenu menu;
  menu.LoadMenu(IDR_POPUP_IMAGE_VIEW);
  CMenu *contextMenu = menu.GetSubMenu(0);
  int choice = contextMenu->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, this);
  if (choice == ID_SAVE_IMAGE) {
    CFileDialog dlg(FALSE);
    if (dlg.DoModal() == IDOK) {
      CString filePath = dlg.GetPathName();
      topImage_.SaveToFile(filePath + "_top.bmp");
      bottomImage_.SaveToFile(filePath + "_bottom.bmp");
    }
  }

  CDialog::OnRButtonDown(nFlags, point);
}