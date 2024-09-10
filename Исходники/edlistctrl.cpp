PoeditListCtrl::PoeditListCtrl(wxWindow *parent,
               wxWindowID id,
               const wxPoint &pos,
               const wxSize &size,
               long style,
               bool dispIDs,
               const wxValidator& validator,
               const wxString &name)
     : wxListView(parent, id, pos, size, style | wxLC_VIRTUAL, validator, name)
{
#ifdef __WXMSW__
    if (wxApp::GetComCtl32Version() >= 600)
    {
        ::SendMessage(GetHwnd(), LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER);
    }
#endif

    m_displayIDs = dispIDs;

    m_isRTL = false;
    m_appIsRTL = (wxTheApp->GetLayoutDirection() == wxLayout_RightToLeft);

    sortOrder = SortOrder::Default();

    CreateColumns();

    wxImageList *list = new wxImageList(PX(16), PX(16));

    // IMG_XXX:
#ifndef __WXMSW__
    list->Add(wxArtProvider::GetBitmap("poedit-status-nothing"));
#endif
    list->Add(wxArtProvider::GetBitmap("poedit-status-automatic"));
    list->Add(wxArtProvider::GetBitmap("poedit-status-comment"));
    list->Add(wxArtProvider::GetBitmap("poedit-status-bookmark"));

    AssignImageList(list, wxIMAGE_LIST_SMALL);

    // configure items colors & fonts:

    wxVisualAttributes visual = GetDefaultAttributes();
    wxColour shaded = visual.colBg;

#ifdef __WXMSW__
    // On Windows 7, shaded list items make it impossible to see the selection,
    // so use different color for it (see bug #336).
    if (IsWindows7OrGreater())
    {
        shaded.Set(int(0.99 * shaded.Red()),
                   int(0.99 * shaded.Green()),
                   shaded.Blue());
    }
    else
#endif // __WXMSW__
#ifdef __WXOSX__
    if ( shaded == *wxWHITE )
    {
        // use standard shaded color from finder/databrowser:
        shaded.Set("#f0f5fd");
    }
    else
#endif // __WXOSX__
    {
        shaded.Set(int(DARKEN_FACTOR * shaded.Red()),
                   int(DARKEN_FACTOR * shaded.Green()),
                   int(DARKEN_FACTOR * shaded.Blue()));
    }

    m_attrNormal[1].SetBackgroundColour(shaded);
    m_attrUntranslated[1].SetBackgroundColour(shaded);
    m_attrFuzzy[1].SetBackgroundColour(shaded);
    m_attrInvalid[1].SetBackgroundColour(shaded);

    // FIXME: make this user-configurable
    if ( IsAlmostWhite(visual.colBg) )
    {
        m_attrUntranslated[0].SetTextColour(gs_UntranslatedForWhite);
        m_attrUntranslated[1].SetTextColour(gs_UntranslatedForWhite);
        m_attrFuzzy[0].SetTextColour(gs_FuzzyForWhite);
        m_attrFuzzy[1].SetTextColour(gs_FuzzyForWhite);
    }
    else if ( IsAlmostBlack(visual.colBg) )
    {
        m_attrUntranslated[0].SetTextColour(gs_UntranslatedForBlack);
        m_attrUntranslated[1].SetTextColour(gs_UntranslatedForBlack);
        m_attrFuzzy[0].SetTextColour(gs_FuzzyForBlack);
        m_attrFuzzy[1].SetTextColour(gs_FuzzyForBlack);
    }
    // else: we don't know if the default colors would be well-visible on
    //       user's background color, so play it safe and don't highlight
    //       anything

    // FIXME: todo; use appropriate font for fuzzy/trans/untrans
    m_attrInvalid[0].SetBackgroundColour(gs_ErrorColor);
    m_attrInvalid[1].SetBackgroundColour(gs_ErrorColor);

    // Use gray for IDs
    if ( IsAlmostBlack(visual.colFg) )
        m_attrId.SetTextColour(wxColour("#A1A1A1"));

    SetCustomFont(wxNullFont);
}