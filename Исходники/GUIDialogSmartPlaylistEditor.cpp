bool CGUIDialogSmartPlaylistEditor::NewPlaylist(const CStdString &type)
{
  CGUIDialogSmartPlaylistEditor *editor = (CGUIDialogSmartPlaylistEditor *)g_windowManager.GetWindow(WINDOW_DIALOG_SMART_PLAYLIST_EDITOR);
  if (!editor) return false;

  editor->m_path = "";
  editor->m_playlist = CSmartPlaylist();
  editor->m_playlist.m_ruleCombination.m_rules.push_back(CSmartPlaylistRule());
  editor->m_mode = type;
  editor->Initialize();
  editor->DoModal(g_windowManager.GetActiveWindow());
  return !editor->m_cancelled;
}