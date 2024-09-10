/**
 * \brief
 */
bool NewClassDlg::ValidateInput()
{
    // validate the class name
    if(!IsValidCppIndetifier(m_textClassName->GetValue())) {
        wxString msg;
        msg << wxT("'") << m_textClassName->GetValue() << _("' is not a valid C++ qualifier");
        wxMessageBox(msg, _("CodeLite"), wxOK | wxICON_WARNING);
        return false;
    }

    // validate the namespace
    if(!m_textCtrlNamespace->GetValue().IsEmpty()) {
        wxArrayString namespacesList;
        this->GetNamespacesList(namespacesList);
        // validate each namespace
        for(unsigned int i = 0; i < namespacesList.Count(); i++) {
            if(!IsValidCppIndetifier(namespacesList[i])) {
                wxString msg;
                msg << wxT("'") << namespacesList[i] << _("' is not a valid C++ qualifier");
                wxMessageBox(msg, _("CodeLite"), wxOK | wxICON_WARNING);
                return false;
            }
        }
    }

    // validate the path of the class
    wxString path(m_textCtrlGenFilePath->GetValue());
    if(!wxDir::Exists(path)) {
        wxString msg;
        msg << wxT("'") << path << _("': directory does not exist");
        wxMessageBox(msg, _("CodeLite"), wxOK | wxICON_WARNING);
        return false;
    }

    if(GetClassFile().IsEmpty()) {
        wxMessageBox(_("Empty file name"), _("CodeLite"), wxOK | wxICON_WARNING);
        return false;
    }

    wxString cpp_file;
    cpp_file << GetClassPath() << wxFileName::GetPathSeparator() << GetClassFile() << wxT(".cpp");
    if(wxFileName::FileExists(cpp_file)) {
        if(wxMessageBox(
               wxString::Format(_("A file with this name: '%s' already exists, continue anyway?"), cpp_file.GetData()),
               _("CodeLite"),
               wxYES_NO | wxICON_WARNING) == wxNO) {
            return false;
        }
    }
    wxString h_file;
    h_file << GetClassPath() << wxFileName::GetPathSeparator() << GetClassFile() << wxT(".h");
    if(wxFileName::FileExists(h_file)) {
        if(wxMessageBox(
               wxString::Format(_("A file with this name: '%s' already exists, continue anyway?"), h_file.GetData()),
               _("CodeLite"),
               wxYES_NO | wxICON_WARNING) == wxNO) {
            return false;
        }
    }

    if(GetVirtualDirectoryPath().IsEmpty()) {
        wxMessageBox(_("Please select a virtual directory"), _("CodeLite"), wxOK | wxICON_WARNING);
        return false;
    }
    return true;
}