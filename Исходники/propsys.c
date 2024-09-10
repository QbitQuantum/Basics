static void test_PSRefreshPropertySchema(void)
{
    HRESULT ret;

    ret = PSRefreshPropertySchema();
    todo_wine
    ok(ret == CO_E_NOTINITIALIZED,
       "Expected PSRefreshPropertySchema to return CO_E_NOTINITIALIZED, got 0x%08x\n", ret);

    CoInitialize(NULL);

    ret = PSRefreshPropertySchema();
    ok(ret == S_OK,
       "Expected PSRefreshPropertySchema to return S_OK, got 0x%08x\n", ret);

    CoUninitialize();
}