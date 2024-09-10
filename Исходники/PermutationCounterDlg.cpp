bool PermutationCounterDlg::Create( wxWindow* parent,
									wxWindowID id,
									const wxString& caption,
									const wxPoint& pos,
									const wxSize& size,
									long style )
{
    m_number = NULL;
    SetParent(parent);
    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}