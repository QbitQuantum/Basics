static void test_CredUIPromptForCredentials(void)
{
    static const WCHAR wszServerName[] = {'W','i','n','e','T','e','s','t',0};
    DWORD ret;
    WCHAR username[256];
    WCHAR password[256];
    CREDUI_INFOW credui_info;
    BOOL save = FALSE;

    credui_info.cbSize = sizeof(credui_info);
    credui_info.hwndParent = NULL;
    credui_info.pszMessageText = NULL;
    credui_info.hbmBanner = NULL;

    ret = CredUIConfirmCredentialsW(NULL, TRUE);
    ok(ret == ERROR_INVALID_PARAMETER /* 2003 + */ || ret == ERROR_NOT_FOUND /* XP */,
        "CredUIConfirmCredentials should have returned ERROR_INVALID_PARAMETER or ERROR_NOT_FOUND instead of %d\n", ret);

    ret = CredUIConfirmCredentialsW(wszServerName, TRUE);
    ok(ret == ERROR_NOT_FOUND, "CredUIConfirmCredentials should have returned ERROR_NOT_FOUND instead of %d\n", ret);

    username[0] = '\0';
    password[0] = '\0';
    ret = CredUIPromptForCredentialsW(NULL, NULL, NULL, 0, username,
                                      ARRAY_SIZE(username),
                                      password, ARRAY_SIZE(password),
                                      NULL, CREDUI_FLAGS_ALWAYS_SHOW_UI);
    ok(ret == ERROR_INVALID_FLAGS, "CredUIPromptForCredentials should have returned ERROR_INVALID_FLAGS instead of %d\n", ret);

    ret = CredUIPromptForCredentialsW(NULL, NULL, NULL, 0, username,
                                      ARRAY_SIZE(username),
                                      password, ARRAY_SIZE(password),
                                      NULL, CREDUI_FLAGS_ALWAYS_SHOW_UI | CREDUI_FLAGS_GENERIC_CREDENTIALS);
    ok(ret == ERROR_INVALID_PARAMETER, "CredUIPromptForCredentials should have returned ERROR_INVALID_PARAMETER instead of %d\n", ret);

    ret = CredUIPromptForCredentialsW(NULL, wszServerName, NULL, 0, username,
                                      ARRAY_SIZE(username),
                                      password, ARRAY_SIZE(password),
                                      NULL, CREDUI_FLAGS_SHOW_SAVE_CHECK_BOX);
    ok(ret == ERROR_INVALID_PARAMETER, "CredUIPromptForCredentials should have returned ERROR_INVALID_PARAMETER instead of %d\n", ret);

    if (winetest_interactive)
    {
        static const WCHAR wszCaption1[] = {'C','R','E','D','U','I','_','F','L','A','G','S','_','E','X','P','E','C','T','_','C','O','N','F','I','R','M','A','T','I','O','N',0};
        static const WCHAR wszCaption2[] = {'C','R','E','D','U','I','_','F','L','A','G','S','_','I','N','C','O','R','R','E','C','T','_','P','A','S','S','W','O','R','D','|',
            'C','R','E','D','U','I','_','F','L','A','G','S','_','E','X','P','E','C','T','_','C','O','N','F','I','R','M','A','T','I','O','N',0};
        static const WCHAR wszCaption3[] = {'C','R','E','D','U','I','_','F','L','A','G','S','_','D','O','_','N','O','T','_','P','E','R','S','I','S','T','|',
            'C','R','E','D','U','I','_','F','L','A','G','S','_','E','X','P','E','C','T','_','C','O','N','F','I','R','M','A','T','I','O','N',0};
        static const WCHAR wszCaption4[] = {'C','R','E','D','U','I','_','F','L','A','G','S','_','P','E','R','S','I','S','T','|',
            'C','R','E','D','U','I','_','F','L','A','G','S','_','E','X','P','E','C','T','_','C','O','N','F','I','R','M','A','T','I','O','N',0};

        ret = CredUIPromptForCredentialsW(NULL, wszServerName, NULL, 0, username,
                                          ARRAY_SIZE(username),
                                          password, ARRAY_SIZE(password),
                                          &save, CREDUI_FLAGS_EXPECT_CONFIRMATION);
        ok(ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "CredUIPromptForCredentials failed with error %d\n", ret);
        if (ret == ERROR_SUCCESS)
        {
            ret = CredUIConfirmCredentialsW(wszServerName, FALSE);
            ok(ret == ERROR_SUCCESS, "CredUIConfirmCredentials failed with error %d\n", ret);
        }

        credui_info.pszCaptionText = wszCaption1;
        ret = CredUIPromptForCredentialsW(&credui_info, wszServerName, NULL, ERROR_ACCESS_DENIED,
                                          username, ARRAY_SIZE(username),
                                          password, ARRAY_SIZE(password),
                                          &save, CREDUI_FLAGS_EXPECT_CONFIRMATION);
        ok(ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "CredUIPromptForCredentials failed with error %d\n", ret);
        if (ret == ERROR_SUCCESS)
        {
            ret = CredUIConfirmCredentialsW(wszServerName, FALSE);
            ok(ret == ERROR_SUCCESS, "CredUIConfirmCredentials failed with error %d\n", ret);
        }

        credui_info.pszCaptionText = wszCaption2;
        ret = CredUIPromptForCredentialsW(&credui_info, wszServerName, NULL, 0,
                                          username, ARRAY_SIZE(username),
                                          password, ARRAY_SIZE(password),
                                          NULL, CREDUI_FLAGS_INCORRECT_PASSWORD|CREDUI_FLAGS_EXPECT_CONFIRMATION);
        ok(ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "CredUIPromptForCredentials failed with error %d\n", ret);
        if (ret == ERROR_SUCCESS)
        {
            ret = CredUIConfirmCredentialsW(wszServerName, FALSE);
            ok(ret == ERROR_SUCCESS, "CredUIConfirmCredentials failed with error %d\n", ret);
        }


        save = TRUE;
        credui_info.pszCaptionText = wszCaption3;
        ret = CredUIPromptForCredentialsW(&credui_info, wszServerName, NULL, 0,
                                          username, ARRAY_SIZE(username),
                                          password, ARRAY_SIZE(password),
                                          &save, CREDUI_FLAGS_DO_NOT_PERSIST|CREDUI_FLAGS_EXPECT_CONFIRMATION);
        ok(ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "CredUIPromptForCredentials failed with error %d\n", ret);
        ok(save, "save flag should have been untouched\n");

        save = FALSE;
        credui_info.pszCaptionText = wszCaption4;
        ret = CredUIPromptForCredentialsW(&credui_info, wszServerName, NULL, 0,
                                          username, ARRAY_SIZE(username),
                                          password, ARRAY_SIZE(password),
                                          &save, CREDUI_FLAGS_PERSIST|CREDUI_FLAGS_EXPECT_CONFIRMATION);
        ok(ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "CredUIPromptForCredentials failed with error %d\n", ret);
        ok(!save, "save flag should have been untouched\n");
        if (ret == ERROR_SUCCESS)
        {
            ret = CredUIConfirmCredentialsW(wszServerName, FALSE);
            ok(ret == ERROR_SUCCESS, "CredUIConfirmCredentials failed with error %d\n", ret);
        }

    }
}