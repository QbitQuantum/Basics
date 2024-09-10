void DirectoryObjectPickerUnitTests::Test_DirectoryObjectPicker_Raw()
{
    CComPtr<IDsObjectPicker> p = NULL;

    CPPUNIT_ASSERT(S_OK == CoCreateInstance(CLSID_DsObjectPicker, NULL, CLSCTX_INPROC_SERVER, 
		IID_IDsObjectPicker, reinterpret_cast<LPVOID *>(& p)));

    DSOP_INIT_INFO InitInfo;
    DSOP_SCOPE_INIT_INFO Scopes[] =
    {
        {
            sizeof(DSOP_SCOPE_INIT_INFO),
            DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE |
            DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE |
            DSOP_SCOPE_TYPE_GLOBAL_CATALOG |
            DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN |
            DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN |
            DSOP_SCOPE_TYPE_WORKGROUP |
            DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN |
            DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN,
            0,
            {
                {
                    DSOP_FILTER_COMPUTERS,
                    0,
                    0
                },
                DSOP_DOWNLEVEL_FILTER_COMPUTERS |
                DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS |
                DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS
            },
            NULL,
            NULL,
            S_OK
        },
    };

    InitInfo.cbSize = sizeof(InitInfo);
    InitInfo.pwzTargetComputer = NULL;
    InitInfo.cDsScopeInfos = sizeof(Scopes) / sizeof(Scopes[0]);
    InitInfo.aDsScopeInfos = Scopes;
    InitInfo.flOptions = DSOP_SCOPE_TYPE_TARGET_COMPUTER;
    InitInfo.cAttributesToFetch = 0;
    InitInfo.apwzAttributeNames = NULL;

    CPPUNIT_ASSERT(S_OK == p->Initialize(& InitInfo));

    HWND hwndParent = ::GetConsoleWindow();
    if (hwndParent == NULL) hwndParent = ::GetForegroundWindow();

    CComPtr<IDataObject> pdo;
    CPPUNIT_ASSERT(SUCCEEDED(p->InvokeDialog(hwndParent, &pdo)));
}