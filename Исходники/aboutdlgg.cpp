bool wxGenericAboutDialog::Create(const wxAboutDialogInfo& info)
{
    // TODO: should we use main frame as parent by default here?
    if ( !wxDialog::Create(NULL, wxID_ANY, _("About ") + info.GetName(),
                           wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE) )
        return false;

    m_sizerText = new wxBoxSizer(wxVERTICAL);
    wxString nameAndVersion = info.GetName();
    if ( info.HasVersion() )
        nameAndVersion << _T(' ') << info.GetVersion();
    wxStaticText *label = new wxStaticText(this, wxID_ANY, nameAndVersion);
    wxFont fontBig(*wxNORMAL_FONT);
    fontBig.SetPointSize(fontBig.GetPointSize() + 2);
    fontBig.SetWeight(wxFONTWEIGHT_BOLD);
    label->SetFont(fontBig);

    m_sizerText->Add(label, wxSizerFlags().Centre().Border());
    m_sizerText->AddSpacer(5);

    AddText(info.GetCopyrightToDisplay());
    AddText(info.GetDescription());

    if ( info.HasWebSite() )
    {
#if wxUSE_HYPERLINKCTRL
        AddControl(new wxHyperlinkCtrl(this, wxID_ANY,
                                       info.GetWebSiteDescription(),
                                       info.GetWebSiteURL()));
#else
        AddText(info.GetWebSiteURL());
#endif // wxUSE_HYPERLINKCTRL/!wxUSE_HYPERLINKCTRL
    }

#if wxUSE_COLLPANE
    if ( info.HasLicence() )
        AddCollapsiblePane(_("License"), info.GetLicence());

    if ( info.HasDevelopers() )
        AddCollapsiblePane(_("Developers"),
                           AllAsString(info.GetDevelopers()));

    if ( info.HasDocWriters() )
        AddCollapsiblePane(_("Documentation writers"),
                           AllAsString(info.GetDocWriters()));

    if ( info.HasArtists() )
        AddCollapsiblePane(_("Artists"),
                           AllAsString(info.GetArtists()));

    if ( info.HasTranslators() )
        AddCollapsiblePane(_("Translators"),
                           AllAsString(info.GetTranslators()));
#endif // wxUSE_COLLPANE

    DoAddCustomControls();


    wxSizer *sizerIconAndText = new wxBoxSizer(wxHORIZONTAL);
#if wxUSE_STATBMP
    wxIcon icon = info.GetIcon();
    if ( icon.Ok() )
    {
        sizerIconAndText->Add(new wxStaticBitmap(this, wxID_ANY, icon),
                                wxSizerFlags().Border(wxRIGHT));
    }
#endif // wxUSE_STATBMP
    sizerIconAndText->Add(m_sizerText, wxSizerFlags(1).Expand());

    wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(sizerIconAndText, wxSizerFlags(1).Expand().Border());

    wxSizer *sizerBtns = CreateButtonSizer(wxOK);
    if ( sizerBtns )
    {
        sizerTop->Add(sizerBtns, wxSizerFlags().Expand().Border());
    }

    SetSizerAndFit(sizerTop);

    CentreOnScreen();

    return true;
}