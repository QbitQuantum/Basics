bool wxSTEditorNotebook::LoadFile( const wxFileName &fileName_,
                                   const wxString &extensions_,
                                   const wxString& encoding_ref)
{
    wxString encoding(encoding_ref);
    wxFileName fileName(fileName_);
    wxString extensions(extensions_.Length() ? extensions_ : GetOptions().GetDefaultFileExtensions());

    if (fileName.GetFullPath().IsEmpty())
    {
        wxSTEditorFileDialog fileDialog( this, _("Open file into new notebook page"),
                                 GetOptions().GetDefaultFilePath(),
                                 extensions,
                                 wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        fileDialog.m_encoding = encoding;
        if (fileDialog.ShowModal() == wxID_OK)
        {
            fileName = fileDialog.GetPath();
            encoding = fileDialog.m_encoding;
        }
        else
            return false;
    }

    bool ok = fileName.FileExists();
    if (ok)
    {
        // load the file from disk and only load it once
        GetOptions().SetDefaultFilePath(fileName.GetPath());

        int page = FindEditorPageByFileName(fileName);
        if (page != wxNOT_FOUND)
        {
            ok = GetEditor(page)->LoadFile(fileName, wxEmptyString, true, encoding);
            SetSelection(page);
        }
        else if ( (GetEditor() == NULL) || GetEditor()->IsModified() || GetEditor()->IsFileFromDisk()) // non-empty editor?
        {
            // new splitter+editor
            wxSTEditorSplitter *splitter = CreateSplitter(wxID_ANY);
            wxCHECK_MSG(splitter, false, wxT("Invalid splitter"));
            ok = splitter->GetEditor()->LoadFile(fileName, wxEmptyString, true, encoding);
            if (ok)
            {
                ok = InsertEditorSplitter(-1, splitter, true);
            }
        }
        else // empty editor
        {
            // reuse editor
            ok = GetEditor()->LoadFile(fileName, wxEmptyString, true, encoding);
        }
    }
    return ok;
}