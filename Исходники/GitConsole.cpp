GitConsole::GitConsole(wxWindow* parent, GitPlugin* git)
    : GitConsoleBase(parent)
    , m_git(git)
{
    // set the font to fit the C++ lexer default font
    LexerConf::Ptr_t lexCpp = EditorConfigST::Get()->GetLexer("text");
    if(lexCpp) {
        lexCpp->Apply(m_stcLog);
    }
    m_bitmapLoader = new BitmapLoader();
    GitImages m_images;
    m_bitmaps = m_bitmapLoader->MakeStandardMimeMap();
    m_modifiedBmp = m_bitmapLoader->LoadBitmap("subversion/16/modified");
    m_untrackedBmp = m_bitmapLoader->LoadBitmap("subversion/16/unversioned");
    m_folderBmp = m_bitmapLoader->LoadBitmap("mime/16/folder");
    m_newBmp = m_images.Bitmap("gitFileAdd");
    m_deleteBmp = m_bitmapLoader->LoadBitmap("subversion/16/deleted");

    EventNotifier::Get()->Connect(
        wxEVT_GIT_CONFIG_CHANGED, wxCommandEventHandler(GitConsole::OnConfigurationChanged), NULL, this);
    EventNotifier::Get()->Connect(
        wxEVT_WORKSPACE_CLOSED, wxCommandEventHandler(GitConsole::OnWorkspaceClosed), NULL, this);
    EventNotifier::Get()->Connect(
        wxEVT_CL_THEME_CHANGED, wxCommandEventHandler(GitConsole::OnEditorThemeChanged), NULL, this);
    clConfig conf("git.conf");
    GitEntry data;
    conf.ReadItem(&data);
    m_isVerbose = (data.GetFlags() & GitEntry::Git_Verbose_Log);

    m_splitter->SetSashPosition(data.GetGitConsoleSashPos());
    m_auibar->AddTool(
        XRCID("git_reset_repository"), _("Reset"), m_images.Bitmap("gitResetRepo"), _("Reset repository"));
    m_auibar->AddSeparator();

    m_auibar->AddTool(XRCID("git_pull"), _("Pull"), m_images.Bitmap("gitPull"), _("Pull remote changes"));
    m_auibar->SetToolDropDown(XRCID("git_pull"), true);
    m_auibar->AddTool(XRCID("git_commit"), _("Commit"), m_images.Bitmap("gitCommitLocal"), _("Commit local changes"));
    m_auibar->AddTool(XRCID("git_push"), _("Push"), m_images.Bitmap("gitPush"), _("Push local changes"));
    m_auibar->AddTool(XRCID("git_rebase"), _("Rebase"), m_images.Bitmap("gitRebase"), _("Rebase"));
    m_auibar->SetToolDropDown(XRCID("git_rebase"), true);
    m_auibar->AddSeparator();
    m_auibar->AddTool(XRCID("git_commit_diff"), _("Diffs"), m_images.Bitmap("gitDiffs"), _("Show current diffs"));
    m_auibar->AddTool(
        XRCID("git_browse_commit_list"), _("Log"), m_images.Bitmap("gitCommitedFiles"), _("Browse commit history"));
#ifdef __WXMSW__
    m_auibar->AddSeparator();
    m_auibar->AddTool(XRCID("git_msysgit"),
                      _("Open MSYS Git"),
                      m_images.Bitmap("msysgit"),
                      _("Open MSYS Git at the current file location"));
#endif

    wxAuiToolBarItemArray append_items;
    PopulateAuiToolbarOverflow(append_items, m_images);
    m_auibar->AddSeparator();
    for(size_t i = 0; i < append_items.GetCount(); ++i) {
        const wxAuiToolBarItem& item = append_items.Item(i);
        m_auibar->AddTool(item.GetId(), item.GetLabel(), item.GetBitmap(), item.GetLabel(), (wxItemKind)item.GetKind());
    }
    m_auibar->Realize();

    Bind(wxEVT_AUITOOLBAR_TOOL_DROPDOWN,
         wxAuiToolBarEventHandler(GitConsole::OnGitPullDropdown),
         this,
         XRCID("git_pull"));
    Bind(wxEVT_AUITOOLBAR_TOOL_DROPDOWN,
         wxAuiToolBarEventHandler(GitConsole::OnGitRebaseDropdown),
         this,
         XRCID("git_rebase"));

    // Adjust the h-scrollbar of git log
    ::clRecalculateSTCHScrollBar(m_stcLog);
}