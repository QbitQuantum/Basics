bool SupressibleMessageDialog::Create( wxWindow* parent, wxWindowID, const wxString&, const wxPoint&, const wxSize&, long)
{
    ////@begin SupressibleMessageDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    SetParent(parent);
    CreateControls();
    SetIcon(GetIconResource(wxT("res/nx.png")));
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    ////@end SupressibleMessageDialog creation
    return true;
}