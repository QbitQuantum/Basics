void PluginWizard::OnProjectPathChanged(wxFileDirPickerEvent& event)
{
    wxFileName project(event.GetPath(), m_textCtrlName->GetValue());
    project.SetExt("project");
    project.AppendDir(m_textCtrlName->GetValue());
    m_textCtrlPreview->ChangeValue( project.GetFullPath() );
}