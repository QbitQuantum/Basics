void DataCaptureGridCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
  CGridCellIndices currCell = GetCellIndices(point);
  int currRow = currCell.m_nRow;
  if ((currRow <= 0) || (currRow > dataCaptureData.Size()))
    return;

  m_currDCap = currRow - 1;

  CMenu popMenu;
  popMenu.CreatePopupMenu();

  UINT insFlags = MF_STRING;
  if (dataCaptureData.IsNotValid(m_currDCap))
    insFlags = MF_STRING | MF_GRAYED;

  VERIFY(popMenu.AppendMenu(insFlags, WM_DCAPM_INS_BEFORE,  "Insert Before" ));
  VERIFY(popMenu.AppendMenu(insFlags, WM_DCAPM_INS_AFTER, "Insert After" ));
  VERIFY(popMenu.AppendMenu(insFlags, WM_DCAPM_DUPLICATE, "Duplicate" ));
  VERIFY(popMenu.AppendMenu(MF_STRING, WM_DCAPM_DELETE, "Delete" ));

  ClientToScreen(&point);
  popMenu.TrackPopupMenu( TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y, this );

}