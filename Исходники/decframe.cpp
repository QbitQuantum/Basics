//
/// Automates hiding and showing of decorations.
//
TResult
TDecoratedFrame::EvCommand(uint id, HWND hWndCtl, uint notifyCode)
{
  TRACEX(OwlCmd, 1, _T("TDecoratedFrame:EvCommand - id(") << id << _T("), ctl(") <<\
    static_cast<void*>(hWndCtl) << _T("), code(") << notifyCode  << _T(")"));

  // Check if it's a menu-style command (i.e. skip commands from Controls)
  //
  if (hWndCtl == 0) {

    // Does the command Id correspond to the Id of one of our children
    //
    TWindow*  decoration = ChildWithId(id);

    // If yes, toggle it's visibility
    //
    if (decoration) {
      bool visible = decoration->IsWindowVisible();

      // If it's visible, remove it's layout metrics - We'll 'Layout' below
      // and toggle the actual visibility of the child below.
      //
      if (visible) {
        RemoveChildLayoutMetrics(*decoration);
      }
      else {

        // Check if decoration wants to be against the frame's edge
        //
        bool insertAtEdge = decoration->IsFlagSet(wfInsertAtEdge);

        // We want to display this child window, first retrieve it's location
        //
        TLocation location = GetLocation(*decoration);

        // Find the decoration it should be adjacent to
        //
        TSiblingSearch  search(decoration, location);
        if (insertAtEdge)
          search.Sibling = FirstThat((TCondFunc)findFirstSiblingAt, &search);
        else
          FirstThat(findSibling, &search);

        // Default to client window if we could not find the decoration's
        // potential neighbor.
        //
        if (!search.Sibling)
          search.Sibling = ClientWnd;

        // Insert at its desired location
        //
        switch (location) {
          case None:
            break;
          case Top:
            InsertAtTop(*decoration, search.Sibling);
            break;

          case Bottom:
            InsertAtBottom(*decoration, search.Sibling);
            break;

          case Left:
            InsertAtLeft(*decoration, search.Sibling);
            break;

          case Right:
            InsertAtRight(*decoration, search.Sibling);
            break;

    default: //JJH added empty default statement
      break;
        }
      }

      // Force the layout manager to compute new locations and shuffle
      // windows around
      //
      Layout();

      // Hide or display the decoration
      //
      decoration->ShowWindow(visible ? SW_HIDE : SW_SHOWNA);
      return 0;
    }
  }

  return TFrameWindow::EvCommand(id, hWndCtl, notifyCode);
}