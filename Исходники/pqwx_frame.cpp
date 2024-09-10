void PqwxFrame::OnOpenScript(wxCommandEvent& event)
{
  bool suggest = haveCurrentServer;
  ServerConnection suggestServer;
  wxString suggestDatabase;
  if (suggest) {
    suggestServer = currentServer;
    suggestDatabase = currentDatabase;
  }

  wxFileDialog dbox(this, _("Open File"), wxEmptyString, wxEmptyString,
                    _("SQL files (*.sql)|*.sql"));
  dbox.CentreOnParent();
  if (dbox.ShowModal() == wxID_OK) {
    ScriptEditorPane *editor = documentsBook->OpenNewScript();
    editor->OpenFile(dbox.GetPath());
    if (suggest)
      editor->Connect(suggestServer, suggestDatabase);
    editor->SetFocus();
  }
}