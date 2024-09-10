// HANDLE VwCreateWin(
// VApiHandle hWndParent, int X, int Y, int nWidth, int nHeight, 
// WCHAR* wszRegName, WCHAR* wszNewName, BOOL bIsAlpha)
SQInteger VwCreateWin(HSQUIRRELVM v)
{
    SQInteger        nargs           = sq_gettop(v);
    SQInteger        nWndParent      = 0;
    HWND             hWndParent      = NULL;
    CUIImage*        pImg            = NULL;
    CScriptMgr*      pMgr            = NULL;
    CPaintManagerUI* pPM             = NULL;
    int              X               = 0;
    int              Y               = 0;
    int              nWidth          = 0;
    int              nHeight         = 0;
    const SQChar*    pwszRegName     = NULL;
    const SQChar*    pwszNewName     = NULL;
    WCHAR            wszNewName[60]  = {0};
    SQBool           bIsAlphaWin     = NULL;
    WinMgrItem*      pWinMgrIt       = NULL;
    HWND             hWnd            = NULL;
    CWindowWnd*      pWinObj         = NULL;
    SQInteger        nRet            = 0;
    CMarkupNode*     pRootXm         = NULL;

    if (!v || 8 + 1 != nargs) {goto _Exit_;}
    if (OT_INTEGER != sq_gettype(v, 2)) {goto _Exit_;}
    if (OT_INTEGER != sq_gettype(v, 3)) {goto _Exit_;}
    if (OT_INTEGER != sq_gettype(v, 4)) {goto _Exit_;}
    if (OT_INTEGER != sq_gettype(v, 5)) {goto _Exit_;}
    if (OT_INTEGER != sq_gettype(v, 6)) {goto _Exit_;}
    if (OT_STRING != sq_gettype(v, 7)) {goto _Exit_;}
    if (OT_STRING != sq_gettype(v, 8)) {goto _Exit_;}
    if (OT_BOOL != sq_gettype(v, 9)) {goto _Exit_;}

    sq_getinteger(v, 2, &nWndParent);
    sq_getinteger(v, 3, &X);
    sq_getinteger(v, 4, &Y);
    sq_getinteger(v, 5, &nWidth);
    sq_getinteger(v, 6, &nHeight);
    sq_getstring(v, 7, &pwszRegName);
    //sq_getinteger(v, 8, &wszNewName);
    sq_getbool(v, 9, &bIsAlphaWin);

    swprintf_s(wszNewName, 60, L"%x", ::GetTickCount());

    if (nWndParent) {
        hWndParent = QiHwHandleToWin(nWndParent)->pWinObj->GetHWND();
    }

    pMgr = (CScriptMgr*)sq_getforeignptr(v);
    if (!pMgr) {goto _Exit_;}
    pPM = pMgr->GetManager();
    if (!pPM || !pPM->GetWinMgr()) {goto _Exit_;}

    pWinMgrIt = pPM->GetWinMgr()->FindWinByName(pwszRegName);
    if (!pWinMgrIt) {goto _Exit_;}

    // 新建立个模板，因为需要可重复用以前的名字
    pRootXm = new CMarkupNode(*pWinMgrIt->pWinXML);
    pWinObj = new CWindowTemplate(pWinMgrIt->pWinObj);
    pWinObj->GetPM()->SetWinMgr(pPM->GetWinMgr());
    pWinObj->SetDefaultResource(pRootXm);

    pWinMgrIt = pPM->GetWinMgr()->AddOneWin(pWinObj, 
        wszNewName, pRootXm, X, Y, nWidth, 
        nHeight, pWinMgrIt->dwStyle, pWinMgrIt->dwExStyle, &pWinMgrIt->ExInfo);

    if (!bIsAlphaWin) {
        hWnd = pWinObj->Create(hWndParent, pwszNewName,
            pWinMgrIt->dwStyle, pWinMgrIt->dwExStyle,
            X, Y, nWidth, nHeight, 0);
    } else {
        hWnd = pWinObj->CreateAlphaWin(hWndParent, pwszNewName,
            pWinMgrIt->dwStyle | WS_EX_LAYERED, pWinMgrIt->dwExStyle,
            X, Y, nWidth, nHeight);
    }

    if (!hWnd) {goto _Exit_;}

    nRet = QiHwObjToHandle(pWinMgrIt);

_Exit_:
    sq_pushinteger(v, nRet);
    return 1;
}