void CheckPointListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {  
  ItemData *data = (ItemData *)lpDrawItemStruct->itemData;
  if (data == NULL || data == (ItemData *)-1) {
    return;
  }
  CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);
  CRect rectItem(lpDrawItemStruct->rcItem);
  dc->FillSolidRect(rectItem, RGB(255, 255, 255));
  rectItem.DeflateRect(32, 0, 32, 0);
  int index = lpDrawItemStruct->itemID;
  CFont *oldFont = dc->SelectObject(GuiResources::GetInstance()->GetFont(GuiResources::FONT_BIG));  
  
  dc->SetBkMode(TRANSPARENT);

  int x = rectItem.right - 32 - 4;
  int y = rectItem.top + (rectItem.Height() - 32) / 2;
  if (imageList_ != NULL && data->state != -1) {
    imageList_->Draw(dc, data->state, CPoint(x, y), ILD_NORMAL);
  }

  dc->SetTextColor(RGB(0,0,0));

  if (imageList_ != NULL && data->icon != -1) {
    imageList_->Draw(dc, data->icon, CPoint(rectItem.left + 10, y), ILD_NORMAL);
  }

  CRect rectText(rectItem);
  rectText.left = rectItem.left + 32 + spacing_;
  dc->DrawText(data->text, rectText, DT_SINGLELINE | DT_VCENTER);

  dc->SelectObject(oldFont);

  dc->Draw3dRect(CRect(rectText.left, rectItem.bottom - 1, rectItem.right, rectItem.bottom),
      RGB(221,221,221), RGB(221,221,221));
}