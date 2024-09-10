void CGUIDialogFavourites::OnPopupMenu(int item)
{
  if (item < 0 || item >= m_favourites->Size())
    return;

  CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)g_windowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
  if (pMenu)
  {
    // highlight the item
    (*m_favourites)[item]->Select(true);

    // initialize the positioning
    CPoint pos;
    const CGUIControl *pList = GetControl(FAVOURITES_LIST);
    if (pList)
      pos = pList->GetRenderPosition() + CPoint(pList->GetWidth() * 0.5f, pList->GetHeight() * 0.5f);
    pMenu->Initialize();

    int btn_MoveUp = m_favourites->Size() > 1 ? pMenu->AddButton(13332) : 0;
    int btn_MoveDown = m_favourites->Size() > 1 ? pMenu->AddButton(13333) : 0;
    int btn_Remove = pMenu->AddButton(15015);
    int btn_Rename = pMenu->AddButton(118);

    pMenu->OffsetPosition(pos.x, pos.y);
    pMenu->DoModal(GetID());
    int button = pMenu->GetButton();

    // unhighlight the item
    (*m_favourites)[item]->Select(false);

    if (button == btn_MoveUp)
      OnMoveItem(item, -1);
    else if (button == btn_MoveDown)
      OnMoveItem(item, 1);
    else if (button == btn_Remove)
      OnDelete(item);
    else if (button == btn_Rename)
      OnRename(item);
  }
}