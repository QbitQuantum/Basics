khm_int32
kmmint_read_module_info(kmm_module_i * m) {
    /* the only fields we can count on at this point are m->name and
       m->path */
    DWORD t;
    size_t cb;
    WORD lang;
    khm_int32 rv = KHM_ERROR_SUCCESS;
    struct lang_code *languages;
    int n_languages;
    int i;
    wchar_t resname[256];       /* the resource names are a lot shorter */
    wchar_t * r;
    VS_FIXEDFILEINFO *vff;
    UINT c;

    assert(m->name);
    assert(m->path);

    t = TRUE;
    cb = GetFileVersionInfoSize(m->path,
                                &t);
    /* if successful, cb gets the size in bytes of the version info
       structure and sets t to zero */
    if (t) {
        return KHM_ERROR_NOT_FOUND;
    } else if (cb == 0) {
        _report_mr1(KHERR_WARNING, MSG_RMI_NOT_FOUND, _dupstr(m->path));
        return KHM_ERROR_INVALID_PARAM;
    }

    if (m->version_info) {
        PFREE(m->version_info);
        m->version_info = NULL;
    }

    m->version_info = PMALLOC(cb);
#ifdef DEBUG
    assert(m->version_info);
#endif

    if(!GetFileVersionInfo(m->path,
                           t, (DWORD) cb, m->version_info)) {
        rv = KHM_ERROR_NOT_FOUND;
        _report_mr1(KHERR_WARNING, MSG_RMI_NOT_FOUND, _dupstr(m->path));
        _location(L"GetFileVersionInfo");
        goto _cleanup;
    }

    if(!VerQueryValue(m->version_info,
                     L"\\VarFileInfo\\Translation",
                     (LPVOID*) &languages,
                     &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_NO_TRANS, _dupstr(m->path));
        _location(L"VerQueryValue");
        goto _cleanup;
    }

    n_languages = (int) (c / sizeof(*languages));

    /* Try searching for the user's default language first */
    lang = GetUserDefaultLangID();
    for (i = 0; i < n_languages; i++) {
        if(languages[i].language == lang)
            break;
    }

    /* If not, try the system default */
    if (i >= n_languages) {
        lang = GetSystemDefaultLangID();
        for (i=0; i<n_languages; i++)
            if (languages[i].language == lang)
                break;
    }

    /* Then try EN_US */
    if (i >= n_languages) {
        lang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
        for (i=0; i<n_languages; i++)
            if (languages[i].language == lang)
                break;
    }

    /* Language neutral? */
    if (i >= n_languages) {
        lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
        for (i=0; i<n_languages; i++)
            if (languages[i].language == lang)
                break;
    }

    /* Just use the first one? */
    if (i >= n_languages) {
        i = 0;
    }

    if (i >= n_languages) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr0(KHERR_WARNING, MSG_RMI_NO_LOCAL);
        goto _cleanup;
    }

    /* check module name */
    StringCbPrintf(resname, sizeof(resname),
                   L"\\StringFileInfo\\%04x%04x\\" TEXT(NIMV_MODULE),
                   languages[i].language,
                   languages[i].codepage);

    if (!VerQueryValue(m->version_info,
                       resname, (LPVOID *) &r, &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING, 
                    _cstr(TEXT(NIMV_MODULE)));
        goto _cleanup;
    }

    if (c > KMM_MAXCB_NAME ||
        FAILED(StringCbLength(r, KMM_MAXCB_NAME, &cb))) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_TOO_LONG,
                    _cstr(TEXT(NIMV_MODULE)));
        goto _cleanup;
    }

    if (wcscmp(r, m->name)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr2(KHERR_WARNING, MSG_RMI_MOD_MISMATCH,
                    _dupstr(r), _dupstr(m->name));
        goto _cleanup;
    }

    /* check API version */
    StringCbPrintf(resname, sizeof(resname),
                   L"\\StringFileInfo\\%04x%04x\\" TEXT(NIMV_APIVER),
                   languages[i].language,
                   languages[i].codepage);

    if (!VerQueryValue(m->version_info,
                       resname, (LPVOID *) &r, &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING, 
                    _cstr(TEXT(NIMV_APIVER)));
        goto _cleanup;
    }

    if (c > KMM_MAXCB_NAME ||
        FAILED(StringCbLength(r, KMM_MAXCB_NAME, &cb))) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_TOO_LONG,
                    _cstr(TEXT(NIMV_APIVER)));
        goto _cleanup;
    }

    t = wcstol(r, NULL, 10);

    rv = kmmint_check_api_version(t);

    if (KHM_FAILED(rv)) {
        _report_mr2(KHERR_WARNING, MSG_RMI_API_MISMATCH,
                    _int32(t), _int32(KH_VERSION_API));
        goto _cleanup;
    }

    /* Looks good.  Now load the description, copyright, support URI
       and file versions */
    if (m->description) {
        PFREE(m->description);
        m->description = NULL;
    }

    StringCbPrintf(resname, sizeof(resname),
                   L"\\StringFileInfo\\%04x%04x\\FileDescription",
                   languages[i].language,
                   languages[i].codepage);

    if (!VerQueryValue(m->version_info,
                       resname, (LPVOID *) &r, &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING, 
                    _cstr(L"FileDescription"));
        goto _cleanup;
    }

    if (c > KMM_MAXCB_DESC ||
        FAILED(StringCbLength(r, KMM_MAXCB_DESC, &cb))) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_TOO_LONG,
                    _cstr(L"FileDescription"));
        goto _cleanup;
    }

    cb += sizeof(wchar_t);

    m->description = PMALLOC(cb);
#ifdef DEBUG
    assert(m->description);
#endif
    StringCbCopy(m->description, cb, r);

    /* on to the support URI */
    if (m->support) {
        PFREE(m->support);
        m->support = NULL;
    }

    StringCbPrintf(resname, sizeof(resname),
                   L"\\StringFileInfo\\%04x%04x\\" TEXT(NIMV_SUPPORT),
                   languages[i].language,
                   languages[i].codepage);

    if (!VerQueryValue(m->version_info,
                       resname, (LPVOID *) &r, &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING,
                    _cstr(TEXT(NIMV_SUPPORT)));
        goto _cleanup;
    }

    if (c > KMM_MAXCB_SUPPORT ||
        FAILED(StringCbLength(r, KMM_MAXCB_SUPPORT, &cb))) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_TOO_LONG,
                    _cstr(TEXT(NIMV_SUPPORT)));
        goto _cleanup;
    }

    cb += sizeof(wchar_t);

    m->support = PMALLOC(cb);
#ifdef DEBUG
    assert(m->support);
#endif
    StringCbCopy(m->support, cb, r);

    /* the vendor/copyright */
    if (m->vendor) {
        PFREE(m->vendor);
        m->vendor = NULL;
    }

    StringCbPrintf(resname, sizeof(resname),
                   L"\\StringFileInfo\\%04x%04x\\LegalCopyright",
                   languages[i].language,
                   languages[i].codepage);

    if (!VerQueryValue(m->version_info,
                       resname, (LPVOID *) &r, &c)) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING, 
                    _cstr(L"LegalCopyright"));
        goto _cleanup;
    }

    if (c > KMM_MAXCB_SUPPORT ||
        FAILED(StringCbLength(r, KMM_MAXCB_SUPPORT, &cb))) {
        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_TOO_LONG,
                    _cstr(L"LegalCopyright"));
        goto _cleanup;
    }

    cb += sizeof(wchar_t);

    m->vendor = PMALLOC(cb);
#ifdef DEBUG
    assert(m->vendor);
#endif
    StringCbCopy(m->vendor, cb, r);

    if (!VerQueryValue(m->version_info,
                       L"\\",
                       (LPVOID *) &vff, &c) ||
        c != sizeof(*vff)) {

        rv = KHM_ERROR_INVALID_PARAM;
        _report_mr1(KHERR_WARNING, MSG_RMI_RES_MISSING, 
                    _cstr(L"Fixed Version Info"));
        goto _cleanup;
    }

    m->file_version.major = HIWORD(vff->dwFileVersionMS);
    m->file_version.minor = LOWORD(vff->dwFileVersionMS);
    m->file_version.patch = HIWORD(vff->dwFileVersionLS);
    m->file_version.aux   = LOWORD(vff->dwFileVersionLS);

    m->prod_version.major = HIWORD(vff->dwProductVersionMS);
    m->prod_version.minor = LOWORD(vff->dwProductVersionMS);
    m->prod_version.patch = HIWORD(vff->dwProductVersionLS);
    m->prod_version.aux   = LOWORD(vff->dwProductVersionLS);

    rv = KHM_ERROR_SUCCESS;

 _cleanup:
    if (KHM_FAILED(rv)) {
        if (m->version_info) {
            PFREE(m->version_info);
            m->version_info = NULL;
        }
    }

    return rv;
}