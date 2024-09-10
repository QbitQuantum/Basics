CComboboxDlg::CComboboxDlg(wxWindow *parent, const char * szTitle, const char * szMessage, const char * szChoices)
             :wxDialog(parent, -1, wxString::FromAscii(szTitle), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
    wxBoxSizer * topsizer;
    wxBoxSizer * sizer   ;
    CStr         S;
    wxButton   * btnOk;
    wxButton   * btnCancel;

    btnOk       = new wxButton     (this, wxID_OK    , wxT("Ok")    );
    btnCancel   = new wxButton     (this, wxID_CANCEL, wxT("Cancel") );
    m_cbChoices = new wxComboBox(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN);


    topsizer = new wxBoxSizer( wxVERTICAL );

    topsizer->Add(new wxStaticText(this, -1, wxString::FromAscii(szMessage)), 0, wxALIGN_LEFT | wxALL, 5);
    topsizer->Add(m_cbChoices                          , 0, wxALIGN_CENTER | wxALL | wxGROW, 5);

    sizer     = new wxBoxSizer( wxHORIZONTAL );
    sizer->Add(btnOk    , 0, wxALIGN_CENTER | wxALL, 5);
    sizer->Add(btnCancel, 0, wxALIGN_CENTER | wxALL, 5);
    topsizer->Add(sizer,   0, wxALIGN_CENTER | wxALL, 10);

    while (szChoices && *szChoices)
    {
        szChoices = S.GetToken(szChoices, ',');
        m_cbChoices->Append(wxString::FromAscii(S.GetData()));
    }

    SetAutoLayout( TRUE );     // tell dialog to use sizer
    SetSizer( topsizer );      // actually set the sizer
    topsizer->Fit( this );            // set size to minimum size as calculated by the sizer
    topsizer->SetSizeHints( this );   // set size hints to honour mininum size}

    m_cbChoices->SetFocus();
    btnOk->SetDefault();

    Centre( wxBOTH | wxCENTER_FRAME);
}