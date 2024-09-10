wxBitmap PoeditArtProvider::CreateBitmap(const wxArtID& id_,
                                         const wxArtClient& client,
                                         const wxSize& size)
{
    wxLogTrace("poedit.icons", "getting icon '%s'", id_.c_str());

    wxArtID id(id_);
    #define CHECK_FOR_VARIANT(name)                         \
        const bool name##Variant = id.Contains("@" #name);  \
        if (name##Variant)                                  \
            id.Replace("@" #name, "")
    CHECK_FOR_VARIANT(disabled);
    CHECK_FOR_VARIANT(opaque);
    CHECK_FOR_VARIANT(inverted);

    // Silence warning about unused parameter in some of the builds
    (void)client;
    (void)size;

    // Note: On Unix, this code is only called as last resort, if standard
    //       theme provider (that uses current icon theme and files from
    //       /usr/share/icons/<theme>) didn't find any matching icon.

#ifdef __WXGTK20__
    // try legacy GNOME icons from standard theme:
    wxString gnomeId = GetGnomeStockId(id);
    if ( !gnomeId.empty() )
    {
        wxLogTrace("poedit.icons", "-> legacy '%s'", gnomeId.c_str());
        wxBitmap gbmp(wxArtProvider::GetBitmap(gnomeId, client, size));
        if ( gbmp.Ok() )
            return gbmp;
    }
#endif // __WXGTK20__

    auto iconsdir = GetIconsDir();
    if ( !wxDirExists(iconsdir) )
    {
        wxLogTrace("poedit.icons",
                   "icons dir %s not found", iconsdir.c_str());
        return wxNullBitmap;
    }

    wxString icon;
    icon.Printf("%s/%s", iconsdir, id);
    wxLogTrace("poedit.icons", "loading from %s", icon);
    wxImage img;
    if (ColorScheme::GetAppMode() == ColorScheme::Dark)
        img = LoadScaledBitmap(icon + "Dark");
    if (!img.IsOk())
        img = LoadScaledBitmap(icon);

    if (!img.IsOk())
    {
        wxLogTrace("poedit.icons", "failed to load icon '%s'", id);
        return wxNullBitmap;
    }

    if (id.EndsWith("Template"))
        ProcessTemplateImage(img, opaqueVariant, invertedVariant);

    if (disabledVariant)
        img = img.ConvertToDisabled();

    if (wxTheApp->GetLayoutDirection() == wxLayout_RightToLeft && ShouldBeMirorredInRTL(id, client))
    {
        img = img.Mirror();
    }

#ifdef __WXMSW__
    if (client == wxART_TOOLBAR && IsWindows10OrGreater())
    {
        const int padding = PX(1);
        auto sz = img.GetSize();
        sz.IncBy(padding * 2);
        img.Resize(sz, wxPoint(padding, padding));
    }
#endif // __WXMSW__

    return wxBitmap(img);
}