TEST_F(ShellTest, CreateAndResolveShortcut) {
    // FIXME i#12: Re-enable on XP when passes.
    if (GetWindowsVersion() < WIN_VISTA) {
        printf("WARNING: Disabling ShellTest.* on Pre-Vista, see i#12.\n");
        return;
    }


    HRESULT hr;
    IShellLinkW *shell;
    IPersistFile *persist = NULL;

    // Create a shortcut.
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                          IID_IShellLinkW, (LPVOID*)(&shell));
    EXPECT_TRUE(SUCCEEDED(hr));
    hr = shell->QueryInterface(IID_IPersistFile, (void**)(&persist));
    EXPECT_TRUE(SUCCEEDED(hr));
    hr = shell->SetPath(file_path_.c_str());
    EXPECT_TRUE(SUCCEEDED(hr));
    hr = shell->SetDescription(kLinkDescription);
    EXPECT_TRUE(SUCCEEDED(hr));
    hr = persist->Save(link_path_.c_str(), TRUE);
    EXPECT_TRUE(SUCCEEDED(hr));
    if (persist)
        persist->Release();
    if (shell)
        shell->Release();

    // Resolve it.

    // Get pointer to the IShellLink interface
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                          IID_IShellLinkW, (LPVOID*)&shell);
    EXPECT_TRUE(SUCCEEDED(hr));

    // Query IShellLink for the IPersistFile interface
    hr = shell->QueryInterface(IID_IPersistFile, (void**)(&persist));
    EXPECT_TRUE(SUCCEEDED(hr));

    // Load the shell link
    hr = persist->Load(link_path_.c_str(), STGM_READ);
    EXPECT_TRUE(SUCCEEDED(hr));

    // Try to find the target of a shortcut
    hr = shell->Resolve(0, SLR_NO_UI);
    EXPECT_TRUE(SUCCEEDED(hr));

    wchar_t link_target[MAX_PATH];
    hr = shell->GetPath(link_target, MAX_PATH, NULL, SLGP_UNCPRIORITY);
    EXPECT_TRUE(SUCCEEDED(hr));
    EXPECT_EQ(file_path_, link_target);

    wchar_t description[MAX_PATH];
    hr = shell->GetDescription(description, MAX_PATH);
    EXPECT_TRUE(SUCCEEDED(hr));
    EXPECT_STREQ(kLinkDescription, description);

    if (persist)
        persist->Release();
    if (shell)
        shell->Release();
}