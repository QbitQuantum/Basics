BOOL COngTVApp::InitInstance()
{
    // customisation des barres d'outils non autorisée
    CMFCToolBar::SetCustomizeMode(FALSE);
#ifdef SCINTILLA_DLL
    // Chargement de la DLL Scintilla : on va la chercher dans le repertoire de l'exe et nul part ailleurs
    // recuperation du path de l'exe
    char lpFilename[255];
    memset(lpFilename,0,255);
    GetModuleFileName(NULL ,lpFilename, 255);
    std::string strSciLexerDllName = CPathMgr::ExtractPath(lpFilename);
    strSciLexerDllName = strSciLexerDllName + "\\SciLexer.dll";
    m_hSciDLL = LoadLibrary(strSciLexerDllName.c_str());
    if (NULL == m_hSciDLL)
    {
        // DLL scintilla non disponible => on ne pourra pas editer de scrip LUA
    }
    else
    {
        CVersion versionSciDLL(strSciLexerDllName);
        if (versionSciDLL.GetProductVersion() < std::string(EXPECTED_SCINTILLA_VERSION))
        {
            // version de la DLL inferieur a la version attendue => on ne pourra pas editer de scrip LUA
            FreeLibrary(m_hSciDLL);
            m_hSciDLL = NULL;
            std::string strMsgError = "Dll min expected version : "EXPECTED_SCINTILLA_VERSION" obtained : ";
            strMsgError += versionSciDLL.GetProductVersion();
            MessageBox(NULL, strMsgError.c_str(), "Unable to load SciLexer.dll", MB_ICONEXCLAMATION);
        }
    }
#endif

#ifdef TEST_ENGLISH
    // Pour forcer une langue
    ::SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH,
                       SUBLANG_DEFAULT),SORT_DEFAULT));
#endif

    // nettoyage des clefs de registres de la version precedente
    // si la version qui s'execute n'est pas identique a celle enregistree dans la base de registres
    // MFCFP = MFC Feature Pack => pour pouvoir faire cohabiter sur un même PC des versions antérieures à la 1.6.0 et des versions postérieures
    // a la 1.6.0
    // avant la 1.6.0 => IHM basée sur UltimateToolbox et sauvegarde des caractéristiques des fenêtres à plat dans la base de registre
    // à partir de 1.6.0 => IHM basée sur MFC Feature Pack et sauvegarde des caractéristiques des fenêtres dans une arborescence de clefs
    // dans la base de registres
    // le nettoyage de la base de registres plantait si on essaiyait de revenir à une version < 1.6.0 => on différencie la clef de base

    std::string strReg = "\\CurrentUser\\Software\\" + m_versionInfos.GetCompanyName() + "\\" + m_versionInfos.GetProductName() + "MFCFP\\";
    g_Registry.SetFullRegistryItem(strReg.c_str());
    CString sVersion=g_Registry.GetStringValue(REGISTRY_KEY_VERSION);
    CString sProductVersion(m_versionInfos.GetProductVersion().c_str());
    if (sVersion != sProductVersion)
    {
        DeleteRegTree(&g_Registry);
    }
    g_Registry.Close();

    // Pour utilisation de RichEditCtrl
    AfxEnableControlContainer();
    AfxInitRichEdit();
    // InitCommonControlsEx() est requis sur Windows XP si le manifeste de l'application
    // spécifie l'utilisation de ComCtl32.dll version 6 ou ultérieure pour activer les
    // styles visuels.  Dans le cas contraire, la création de fenêtres échouera.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // À définir pour inclure toutes les classes de contrôles communs à utiliser
    // dans votre application.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    InitContextMenuManager();
    InitShellManager();
    InitKeyboardManager();
    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // enregistrement Scintilla
#ifndef SCINTILLA_DLL
    Scintilla_RegisterClasses(AfxGetInstanceHandle());
    Scintilla_LinkLexers();
#endif

// Supprime pour la gestion multi-lingues
//    CWinAppEx::InitInstance();


    // Initialisation standard
    // Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
    // de votre exécutable final, vous devez supprimer ci-dessous
    // les routines d'initialisation spécifiques dont vous n'avez pas besoin.
    // Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
    // TODO : modifiez cette chaîne avec des informations appropriées,
    // telles que le nom de votre société ou organisation
    SetRegistryKey(m_versionInfos.GetCompanyName().c_str());

    //First free the string allocated by MFC at CWinApp startup.
    //The string is allocated before InitInstance is called.
    free((void*)m_pszProfileName);
    //Change the name of the .INI file.
    //The CWinApp destructor will free the memory.
    // Ce nom est utilise pour la sauvegarde des parametres
    strReg = m_versionInfos.GetProductName() + "MFCFP";
    m_pszProfileName = _tcsdup(strReg.c_str());

    LoadStdProfileSettings(4);  // Charge les options de fichier INI standard (y compris les derniers fichiers utilisés)
    // Inscrire les modèles de document de l'application. Ces modèles
    //  lient les documents, fenêtres frame et vues entre eux
    
    // creation du manager de doc specifique afin de gerer specifiquement les repertoires
    // de sauvegarde des diffents documents.
    // cf http://www.codeguru.com/cpp/w-d/dislog/commondialogs/article.php/c1967
    m_pDocManager = new COngTVDocManager;

    // Creation doc template pour les scripts LUA (uniquement si DLL scintilla disponible)
    if (NULL != m_hSciDLL)
    {
        m_pNewLuaDocTemplate = new CMultiDocTemplate( IDR_LUATYPE
                                                    , RUNTIME_CLASS(CLuaDoc)
                                                    , RUNTIME_CLASS(CLuaChildFrame)
                                                    , RUNTIME_CLASS(CLuaView)
                                                    );
        if (!m_pNewLuaDocTemplate)
            return FALSE;
        AddDocTemplate(m_pNewLuaDocTemplate);
    }

    // Installe la police DINA
    HRSRC hRes   = FindResource(NULL, MAKEINTRESOURCE(IDR_DINA), _T("DINA"));
    PVOID lpFont = LockResource(LoadResource(NULL, hRes)); 
    DWORD dwSize = SizeofResource(NULL, hRes), cFonts = 0;
    m_hDinaFont = AddFontMemResourceEx(lpFont, dwSize, NULL, &cFonts);
    ASSERT(cFonts > 0);

    // crée la fenêtre frame MDI principale
    CMainFrame* pMainFrame = new CMainFrame;
    // On parse la ligne de commande
    CCmdLine cmdLine;
    cmdLine.SplitLine(__argc, __argv);
    // On indique le fichier de configuration ("" par defaut)
    std::string configFileName = cmdLine.GetSafeArgument("-cnx", 0, "");
    pMainFrame->SetConfigFile(configFileName);

    m_pMainWnd = pMainFrame;
    if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainFrame;
        return FALSE;
    }

    // La fenêtre principale a été initialisée et peut donc être affichée et mise à jour
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();

    return TRUE;
}