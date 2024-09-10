int CGUIDialogContextMenu::ShowAndGetChoice(const CContextButtons &choices)
{
  if (choices.empty())
    return -1;

  CGUIDialogContextMenu *pMenu = g_windowManager.GetWindow<CGUIDialogContextMenu>(WINDOW_DIALOG_CONTEXT_MENU);
  if (pMenu)
  {
    pMenu->m_buttons = choices;
    pMenu->Initialize();
    pMenu->SetInitialVisibility();
    pMenu->SetupButtons();
    pMenu->PositionAtCurrentFocus();
    pMenu->Open();

    int idx = pMenu->m_clickedButton;
    if (idx != -1)
      return choices[idx].first;
  }
  return -1;
}