static BOOL createdirectdraw(void)
{
    HRESULT rc;

    SetRect(&rect_before_create, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    rc = DirectDrawCreate(NULL, &lpDD, NULL);
    ok(rc==DD_OK || rc==DDERR_NODIRECTDRAWSUPPORT, "DirectDrawCreateEx returned: %x\n", rc);
    if (!lpDD) {
        trace("DirectDrawCreateEx() failed with an error %x\n", rc);
        return FALSE;
    }
    return TRUE;
}