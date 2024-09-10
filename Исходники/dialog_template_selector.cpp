void DIALOG_TEMPLATE_SELECTOR::AddPage( const wxString& aTitle, wxFileName& aPath )
{
    wxNotebookPage* newPage = new wxNotebookPage( m_notebook, wxID_ANY );
    m_notebook->AddPage( newPage, aTitle );

    TEMPLATE_SELECTION_PANEL* p = new TEMPLATE_SELECTION_PANEL( newPage );
    m_panels.push_back( p );

    // Get a list of files under the template path to include as choices...
    wxArrayString files;
    wxDir dir, sub;

    if ( dir.Open( aPath.GetPath() ) )
    {
        wxString filename;
        bool cont = dir.GetFirst( &filename, wxEmptyString, wxDIR_FILES | wxDIR_DIRS );

        while( cont )
        {
            if( sub.Open( aPath.GetPathWithSep() + filename ) )
            {
                files.Add( filename );
                PROJECT_TEMPLATE* pt = new PROJECT_TEMPLATE( aPath.GetPathWithSep() + filename );
                AddTemplate( m_notebook->GetPageCount() - 1, pt );
            }

            cont = dir.GetNext( &filename );
        }
    }
}