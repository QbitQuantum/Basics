int CSkinAdvanced::Parse(MIOFILE& in) {
    char buf[256];
    std::string strBuffer;

    while (in.fgets(buf, 256)) {
        if (match_tag(buf, "</advanced>")) break;
        else if (parse_bool(buf, "is_branded", m_bIsBranded)) continue;
        else if (parse_str(buf, "<application_name>", strBuffer)) {
            m_strApplicationName = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        } else if (parse_str(buf, "<application_short_name>", strBuffer)) {
            m_strApplicationShortName = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        } else if (match_tag(buf, "<application_icon>")) {
            m_iconApplicationIcon.Parse(in);
            continue;
        } else if (match_tag(buf, "<application_icon32>")) {
            m_iconApplicationIcon.Parse32(in);
            continue;
        } else if (match_tag(buf, "<application_disconnected_icon>")) {
            m_iconApplicationDisconnectedIcon.Parse(in);
            continue;
        } else if (match_tag(buf, "<application_snooze_icon>")) {
            m_iconApplicationSnoozeIcon.Parse(in);
            continue;
        } else if (parse_str(buf, "<application_logo>", strBuffer)) {
            if(strBuffer.length()) {
                wxString str = wxString(
                    wxGetApp().GetSkinManager()->ConstructSkinPath() +
                    wxString(strBuffer.c_str(), wxConvUTF8)
                );
                if (boinc_file_exists(str.c_str())) {
                    wxImage img = wxImage(str.c_str(), wxBITMAP_TYPE_ANY);
                    if (img.IsOk()) {
#ifdef __WXMSW__
// TODO: Choose from multiple size images if provided, else resize the closest one
                        if ((GetXDPIScaling() > 1.05) || (GetYDPIScaling() > 1.05)) {
                            img.Rescale((int) (img.GetWidth()*GetXDPIScaling()), 
                                        (int) (img.GetHeight()*GetYDPIScaling()), 
                                        wxIMAGE_QUALITY_BILINEAR
                                    );
                        }
#endif
                        m_bitmapApplicationLogo = wxBitmap(img);
                    }
                }
            }
            continue;
        } else if (parse_str(buf, "<organization_name>", strBuffer)) {
            m_strOrganizationName = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        } else if (parse_str(buf, "<organization_website>", strBuffer)) {
            m_strOrganizationWebsite = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        } else if (parse_str(buf, "<organization_help_url>", strBuffer)) {
            m_strOrganizationHelpUrl = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        } else if (parse_int(buf, "<open_tab>", m_iDefaultTab)) {
            m_bDefaultTabSpecified = true;
            continue;
        } else if (parse_str(buf, "<exit_message>", strBuffer)) {
            m_strExitMessage = wxString(strBuffer.c_str(), wxConvUTF8);
            continue;
        }
    }

    InitializeDelayedValidation();

    return 0;
}