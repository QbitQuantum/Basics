void CppCheck::DoCppCheckAnalysis(const wxString& Xml)
{
    // clear the list
    m_ListLog->Clear();

    TiXmlDocument Doc;
    Doc.Parse( Xml.ToAscii() );
    if ( Doc.Error() )
    {
        wxString msg = _("Failed to parse cppcheck XML file.\nProbably it's not produced correctly.");
        AppendToLog(msg);
        cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
    }
    else
    {
        TiXmlHandle Handle(&Doc);
        Handle = Handle.FirstChildElement("results");

        bool ErrorsPresent = false;
        TiXmlElement* resultNode = Handle.ToElement();
        if (nullptr!=resultNode->Attribute("version"))
        {
            wxString Version = wxString::FromAscii(resultNode->Attribute("version"));
            if ( Version.IsSameAs(wxT("2")) )
                ErrorsPresent = DoCppCheckParseXMLv2(Handle);
            else
            {
                cbMessageBox(_("Unsupported XML file version of CppCheck."),
                             _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
            }
        }
        else
        {
            ErrorsPresent = DoCppCheckParseXMLv1(Handle);
        }

        if (ErrorsPresent)
        {
            if ( Manager::Get()->GetLogManager() )
            {
                CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_ListLog);
                Manager::Get()->ProcessEvent(evtSwitch);
            }
        }

        if ( !Doc.SaveFile("CppCheckResults.xml") )
        {
            cbMessageBox(_("Failed to create output file 'CppCheckResults.xml' for cppcheck.\nPlease check file/folder access rights."),
                         _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
        }
    }
}