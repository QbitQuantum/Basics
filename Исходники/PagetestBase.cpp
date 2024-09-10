/*-----------------------------------------------------------------------------
  Find the top-level and document windows for the browser
-----------------------------------------------------------------------------*/
bool CPagetestBase::FindBrowserWindows(DWORD process_id, HWND& frame_window, 
                          HWND& document_window) {
  bool found = false;
  // find a known document window that belongs to this process
  document_window = FindDocumentWindow(process_id, ::GetDesktopWindow());
  if (document_window) {
    found = true;
    frame_window = GetAncestor(document_window, GA_ROOTOWNER);
  }
  return found;
}