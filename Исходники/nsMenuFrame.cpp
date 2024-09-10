//
// Enter
//
// Called when the user hits the <Enter>/<Return> keys or presses the
// shortcut key. If this is a leaf item, the item's action will be executed.
// In either case, do nothing if the item is disabled.
//
nsMenuFrame*
nsMenuFrame::Enter()
{
  if (IsDisabled()) {
#ifdef XP_WIN
    // behavior on Windows - close the popup chain
    if (mMenuParent) {
      nsXULPopupManager* pm = nsXULPopupManager::GetInstance();
      if (pm) {
        nsIFrame* popup = pm->GetTopPopup(ePopupTypeAny);
        if (popup)
          pm->HidePopup(popup->GetContent(), PR_TRUE, PR_TRUE, PR_TRUE);
      }
    }
#endif   // #ifdef XP_WIN
    // this menu item was disabled - exit
    return nsnull;
  }

  if (!IsOpen()) {
    // The enter key press applies to us.
    if (!IsMenu() && mMenuParent)
      Execute(0);          // Execute our event handler
    else
      return this;
  }

  return nsnull;
}