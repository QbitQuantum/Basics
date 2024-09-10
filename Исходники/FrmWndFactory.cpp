bool CFrameWndFactory::CreateFrameWnd(LPCWSTR factoryFile)
{
    CXTPWinDwmWrapper().SetProcessDPIAware();   // Support high DPI on Vista or above.

    std::wstring xtpfile(getTranslationsPath(L"ToolkitPro.Resource.xml"));
    if (PathFileExistsW(xtpfile.c_str()))
        XTPResourceManager()->SetResourceFile(xtpfile.c_str());
    else
        TRACE1("Warning: no translation file '%s'\n", xtpfile.c_str());

    Object<IConfigXml> xmlfile(x3::clsidXmlFile);
    ASSERT_MESSAGE(xmlfile, "Need the configxml plugin.");
    xmlfile->SetFileName((getConfigPath() + factoryFile).c_str());
    ASSERT_MESSAGE(xmlfile->Reload(), "No xml file or need to setup MSXML4.");

    ConfigSection root(xmlfile->GetData()->GetSection(L""));
    ConfigSection mainframe(root.GetSection(L"mainframe"));
    bool mdi = root->GetBool(L"mdi", false);

    g_factoryRoot = root;
    g_factoryRoot->SetString(L"_appid", m_appid.c_str());

    Object<IUIOptionsInit> initOptions(clsidUIOptions);
    initOptions->setFileName((getConfigPath() + 
        root->GetString(L"optionsFile", L"uioptions.xml")).c_str());

    RegisterDocTemplate(mdi, mainframe, root.GetSection(L"views"));
    if (mdi)
    {
        CMainMDIFrame* pFrame = new CMainMDIFrame;
        if (!pFrame->LoadFrame(0))
            return FALSE;

        std::vector<ViewItem>::const_iterator it = s_views.begin();
        for (; it != s_views.end(); ++it)
        {
            if (!it->caption.empty())
            {
                CDocument* pDoc = it->pTemplate->OpenDocumentFile(NULL);
                pDoc->SetTitle(it->caption.c_str());
            }
        }
    }

    return ProcessShellCommand();
}