void CModuleControl::Create(HWND hParent, RECT& rect)
{
  CWindowImpl<CModuleControl>::Create(hParent, rect);

  RECT captionRect = { 0, 0, CAPTION_WIDTH, GetCaptionHeight() };
  MapDialogRect(hParent, &captionRect);
  m_hCaption.Create(TEXT("STATIC"), *this, captionRect, m_strCaption.c_str(), WS_CHILD | WS_VISIBLE);

  RECT childRect = { CAPTION_WIDTH, 0, CAPTION_WIDTH + CHILD_WIDTH, GetChildHeight() };
  MapDialogRect(hParent, &childRect);
  CreateChild(*this, childRect);
};