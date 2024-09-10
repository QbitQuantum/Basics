    WXMainToolbar(wxFrame *parent)
    {
        m_tb = wxXmlResource::Get()->LoadToolBar(parent, "toolbar");
        m_idUpdate = XRCID("toolbar_update");

#ifdef __WXGTK3__
        gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(Toolbar())), GTK_STYLE_CLASS_PRIMARY_TOOLBAR);
        SetIcon(0 , "document-open-symbolic");
        SetIcon(1 , "document-save-symbolic");
        SetIcon(3 , "poedit-validate-symbolic");
        SetIcon(4 , "poedit-update-symbolic");
        SetIcon(6 , "sidebar-symbolic");
#endif

#ifdef __WXMSW__
        // De-uglify the toolbar a bit on Windows 10:
        if (IsWindows10OrGreater())
        {
            if (wxUxThemeIsActive())
            {
                wxUxThemeHandle hTheme(m_tb, L"ExplorerMenu::Toolbar");
                m_tb->SetBackgroundColour(wxRGBToColour(::GetThemeSysColor(hTheme, COLOR_WINDOW)));
            }

            unsigned padding = PX(4);
            ::SendMessage((HWND) m_tb->GetHWND(), TB_SETPADDING, 0, MAKELPARAM(padding, padding));
        }
        m_tb->SetDoubleBuffered(true);
#endif
    }