/* FIXME: this creates an ANSI storage, try to find conditions under which
 * Unicode translation fails
 */
static void testProps(void)
{
    static const WCHAR szDot[] = { '.',0 };
    static const WCHAR szPrefix[] = { 's','t','g',0 };
    static WCHAR propName[] = { 'p','r','o','p',0 };
    static char val[] = "l33t auth0r";
    WCHAR filename[MAX_PATH];
    HRESULT hr;
    IStorage *storage = NULL;
    IPropertySetStorage *propSetStorage = NULL;
    IPropertyStorage *propertyStorage = NULL;
    PROPSPEC spec;
    PROPVARIANT var;
    CLIPDATA clipdata;
    unsigned char clipcontent[] = "foobar";
    GUID anyOldGuid = { 0x12345678,0xdead,0xbeef, {
     0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07 } };

    if(!GetTempFileNameW(szDot, szPrefix, 0, filename))
        return;

    DeleteFileW(filename);

    hr = StgCreateDocfile(filename,
     STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, &storage);
    ok(hr == S_OK, "StgCreateDocfile failed: 0x%08x\n", hr);

    if(!pStgCreatePropSetStg)
    {
        IStorage_Release(storage);
        DeleteFileW(filename);
        return;
    }
    hr = pStgCreatePropSetStg(storage, 0, &propSetStorage);
    ok(hr == S_OK, "StgCreatePropSetStg failed: 0x%08x\n", hr);

    hr = IPropertySetStorage_Create(propSetStorage,
     &FMTID_SummaryInformation, NULL, PROPSETFLAG_ANSI,
     STGM_READWRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE,
     &propertyStorage);
    ok(hr == S_OK, "IPropertySetStorage_Create failed: 0x%08x\n", hr);

    hr = IPropertyStorage_WriteMultiple(propertyStorage, 0, NULL, NULL, 0);
    ok(hr == S_OK, "WriteMultiple with 0 args failed: 0x%08x\n", hr);
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, NULL, NULL, 0);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);

    /* test setting one that I can't set */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_DICTIONARY;
    var.vt = VT_I4;
    U(var).lVal = 1;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == STG_E_INVALIDPARAMETER,
     "Expected STG_E_INVALIDPARAMETER, got 0x%08x\n", hr);

    /* test setting one by name with an invalid propidNameFirst */
    spec.ulKind = PRSPEC_LPWSTR;
    U(spec).lpwstr = propName;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var,
     PID_DICTIONARY);
    ok(hr == STG_E_INVALIDPARAMETER,
     "Expected STG_E_INVALIDPARAMETER, got 0x%08x\n", hr);

    /* test setting behavior (case-sensitive) */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_BEHAVIOR;
    U(var).lVal = 1;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == STG_E_INVALIDPARAMETER,
     "Expected STG_E_INVALIDPARAMETER, got 0x%08x\n", hr);

    /* set one by value.. */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    U(var).lVal = 1;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);

    /* set one by name */
    spec.ulKind = PRSPEC_LPWSTR;
    U(spec).lpwstr = propName;
    U(var).lVal = 2;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var,
     PID_FIRST_USABLE);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);

    /* set a string value */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PIDSI_AUTHOR;
    var.vt = VT_LPSTR;
    U(var).pszVal = val;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);

    /* set a clipboard value */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PIDSI_THUMBNAIL;
    var.vt = VT_CF;
    clipdata.cbSize = sizeof clipcontent + sizeof (ULONG);
    clipdata.ulClipFmt = CF_ENHMETAFILE;
    clipdata.pClipData = clipcontent;
    U(var).pclipdata = &clipdata;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);


    /* check reading */
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 0, NULL, NULL);
    ok(hr == S_FALSE, "ReadMultiple with 0 args failed: 0x%08x\n", hr);
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    /* read by propid */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_I4 && U(var).lVal == 1,
     "Didn't get expected type or value for property (got type %d, value %d)\n",
     var.vt, U(var).lVal);
    /* read by name */
    spec.ulKind = PRSPEC_LPWSTR;
    U(spec).lpwstr = propName;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_I4 && U(var).lVal == 2,
     "Didn't get expected type or value for property (got type %d, value %d)\n",
     var.vt, U(var).lVal);
    /* read string value */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PIDSI_AUTHOR;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_LPSTR && !lstrcmpA(U(var).pszVal, val),
     "Didn't get expected type or value for property (got type %d, value %s)\n",
     var.vt, U(var).pszVal);
    PropVariantClear(&var);

    /* read clipboard format */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PIDSI_THUMBNAIL;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_CF, "variant type wrong\n");
    ok(U(var).pclipdata->ulClipFmt == CF_ENHMETAFILE,
        "clipboard type wrong\n");
    ok(U(var).pclipdata->cbSize == sizeof clipcontent + sizeof (ULONG),
        "clipboard size wrong\n");
    ok(!memcmp(U(var).pclipdata->pClipData, clipcontent, sizeof clipcontent),
        "clipboard contents wrong\n");
    ok(S_OK == PropVariantClear(&var), "failed to clear variant\n");

    /* check deleting */
    hr = IPropertyStorage_DeleteMultiple(propertyStorage, 0, NULL);
    ok(hr == S_OK, "DeleteMultiple with 0 args failed: 0x%08x\n", hr);
    hr = IPropertyStorage_DeleteMultiple(propertyStorage, 1, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    /* contrary to what the docs say, you can't delete the dictionary */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_DICTIONARY;
    hr = IPropertyStorage_DeleteMultiple(propertyStorage, 1, &spec);
    ok(hr == STG_E_INVALIDPARAMETER,
     "Expected STG_E_INVALIDPARAMETER, got 0x%08x\n", hr);
    /* now delete the first value.. */
    U(spec).propid = PID_FIRST_USABLE;
    hr = IPropertyStorage_DeleteMultiple(propertyStorage, 1, &spec);
    ok(hr == S_OK, "DeleteMultiple failed: 0x%08x\n", hr);
    /* and check that it's no longer readable */
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_FALSE, "Expected S_FALSE, got 0x%08x\n", hr);

    hr = IPropertyStorage_Commit(propertyStorage, STGC_DEFAULT);
    ok(hr == S_OK, "Commit failed: 0x%08x\n", hr);

    /* check reverting */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);
    hr = IPropertyStorage_Revert(propertyStorage);
    ok(hr == S_OK, "Revert failed: 0x%08x\n", hr);
    /* now check that it's still not there */
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_FALSE, "Expected S_FALSE, got 0x%08x\n", hr);
    /* set an integer value again */
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    var.vt = VT_I4;
    U(var).lVal = 1;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);
    /* commit it */
    hr = IPropertyStorage_Commit(propertyStorage, STGC_DEFAULT);
    ok(hr == S_OK, "Commit failed: 0x%08x\n", hr);
    /* set it to a string value */
    var.vt = VT_LPSTR;
    U(var).pszVal = val;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);
    /* revert it */
    hr = IPropertyStorage_Revert(propertyStorage);
    ok(hr == S_OK, "Revert failed: 0x%08x\n", hr);
    /* Oddly enough, there's no guarantee that a successful revert actually
     * implies the value wasn't saved.  Maybe transactional mode needs to be
     * used for that?
     */

    IPropertyStorage_Release(propertyStorage);
    propertyStorage = NULL;
    IPropertySetStorage_Release(propSetStorage);
    propSetStorage = NULL;
    IStorage_Release(storage);
    storage = NULL;

    /* now open it again */
    hr = StgOpenStorage(filename, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
     NULL, 0, &storage);
    ok(hr == S_OK, "StgOpenStorage failed: 0x%08x\n", hr);

    hr = pStgCreatePropSetStg(storage, 0, &propSetStorage);
    ok(hr == S_OK, "StgCreatePropSetStg failed: 0x%08x\n", hr);

    hr = IPropertySetStorage_Open(propSetStorage, &FMTID_SummaryInformation,
     STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &propertyStorage);
    ok(hr == S_OK, "IPropertySetStorage_Open failed: 0x%08x\n", hr);

    /* check properties again */
    spec.ulKind = PRSPEC_LPWSTR;
    U(spec).lpwstr = propName;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_I4 && U(var).lVal == 2,
     "Didn't get expected type or value for property (got type %d, value %d)\n",
     var.vt, U(var).lVal);
    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PIDSI_AUTHOR;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);
    ok(var.vt == VT_LPSTR && !lstrcmpA(U(var).pszVal, val),
     "Didn't get expected type or value for property (got type %d, value %s)\n",
     var.vt, U(var).pszVal);
    PropVariantClear(&var);

    IPropertyStorage_Release(propertyStorage);
    IPropertySetStorage_Release(propSetStorage);
    IStorage_Release(storage);

    DeleteFileW(filename);

    /* Test creating a property set storage with a random GUID */
    hr = StgCreateDocfile(filename,
     STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, &storage);
    ok(hr == S_OK, "StgCreateDocfile failed: 0x%08x\n", hr);

    if(!pStgCreatePropSetStg)
    {
        IStorage_Release(storage);
        DeleteFileW(filename);
        return;
    }
    hr = pStgCreatePropSetStg(storage, 0, &propSetStorage);
    ok(hr == S_OK, "StgCreatePropSetStg failed: 0x%08x\n", hr);

    hr = IPropertySetStorage_Create(propSetStorage,
     &anyOldGuid, NULL, PROPSETFLAG_ANSI,
     STGM_READWRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE,
     &propertyStorage);
    ok(hr == S_OK, "IPropertySetStorage_Create failed: 0x%08x\n", hr);

    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    var.vt = VT_I4;
    U(var).lVal = 1;
    hr = IPropertyStorage_WriteMultiple(propertyStorage, 1, &spec, &var, 0);
    ok(hr == S_OK, "WriteMultiple failed: 0x%08x\n", hr);

    hr = IPropertyStorage_Commit(propertyStorage, STGC_DEFAULT);
    ok(hr == S_OK, "Commit failed: 0x%08x\n", hr);

    IPropertyStorage_Release(propertyStorage);
    IPropertySetStorage_Release(propSetStorage);
    IStorage_Release(storage);
    propertyStorage = NULL;

    /* now open it again */
    hr = StgOpenStorage(filename, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
     NULL, 0, &storage);
    ok(hr == S_OK, "StgOpenStorage failed: 0x%08x\n", hr);

    hr = pStgCreatePropSetStg(storage, 0, &propSetStorage);
    ok(hr == S_OK, "StgCreatePropSetStg failed: 0x%08x\n", hr);

    hr = IPropertySetStorage_Open(propSetStorage, &anyOldGuid,
     STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &propertyStorage);
    ok(hr == S_OK, "IPropertySetStorage_Open failed: 0x%08x\n", hr);

    spec.ulKind = PRSPEC_PROPID;
    U(spec).propid = PID_FIRST_USABLE;
    hr = IPropertyStorage_ReadMultiple(propertyStorage, 1, &spec, &var);
    ok(hr == S_OK, "ReadMultiple failed: 0x%08x\n", hr);

    ok(var.vt == VT_I4 && U(var).lVal == 1,
     "Didn't get expected type or value for property (got type %d, value %d)\n",
     var.vt, U(var).lVal);

    IPropertyStorage_Release(propertyStorage);
    IPropertySetStorage_Release(propSetStorage);
    IStorage_Release(storage);

    DeleteFileW(filename);
}