static void test_winmodule(void)
{
    _AtlCreateWndData create_data[3];
    _ATL_WIN_MODULE winmod;
    void *p;
    HRESULT hres;

    winmod.cbSize = 0xdeadbeef;
    hres = AtlWinModuleInit(&winmod);
    ok(hres == E_INVALIDARG, "AtlWinModuleInit failed: %08x\n", hres);

    winmod.cbSize = sizeof(winmod);
    winmod.m_pCreateWndList = (void*)0xdeadbeef;
    winmod.m_csWindowCreate.LockCount = 0xdeadbeef;
    winmod.m_rgWindowClassAtoms.m_aT = (void*)0xdeadbeef;
    winmod.m_rgWindowClassAtoms.m_nSize = 0xdeadbeef;
    winmod.m_rgWindowClassAtoms.m_nAllocSize = 0xdeadbeef;
    hres = AtlWinModuleInit(&winmod);
    ok(hres == S_OK, "AtlWinModuleInit failed: %08x\n", hres);
    ok(!winmod.m_pCreateWndList, "winmod.m_pCreateWndList = %p\n", winmod.m_pCreateWndList);
    ok(winmod.m_csWindowCreate.LockCount == -1, "winmod.m_csWindowCreate.LockCount = %d\n",
       winmod.m_csWindowCreate.LockCount);
    ok(winmod.m_rgWindowClassAtoms.m_aT == (void*)0xdeadbeef, "winmod.m_rgWindowClassAtoms.m_aT = %p\n",
       winmod.m_rgWindowClassAtoms.m_aT);
    ok(winmod.m_rgWindowClassAtoms.m_nSize == 0xdeadbeef, "winmod.m_rgWindowClassAtoms.m_nSize = %d\n",
       winmod.m_rgWindowClassAtoms.m_nSize);
    ok(winmod.m_rgWindowClassAtoms.m_nAllocSize == 0xdeadbeef, "winmod.m_rgWindowClassAtoms.m_nAllocSize = %d\n",
       winmod.m_rgWindowClassAtoms.m_nAllocSize);

    InitializeCriticalSection(&winmod.m_csWindowCreate);

    AtlWinModuleAddCreateWndData(&winmod, create_data, (void*)0xdead0001);
    ok(winmod.m_pCreateWndList == create_data, "winmod.m_pCreateWndList != create_data\n");
    ok(create_data[0].m_pThis == (void*)0xdead0001, "unexpected create_data[0].m_pThis %p\n", create_data[0].m_pThis);
    ok(create_data[0].m_dwThreadID == GetCurrentThreadId(), "unexpected create_data[0].m_dwThreadID %x\n",
       create_data[0].m_dwThreadID);
    ok(!create_data[0].m_pNext, "unexpected create_data[0].m_pNext %p\n", create_data[0].m_pNext);

    AtlWinModuleAddCreateWndData(&winmod, create_data+1, (void*)0xdead0002);
    ok(winmod.m_pCreateWndList == create_data+1, "winmod.m_pCreateWndList != create_data\n");
    ok(create_data[1].m_pThis == (void*)0xdead0002, "unexpected create_data[1].m_pThis %p\n", create_data[1].m_pThis);
    ok(create_data[1].m_dwThreadID == GetCurrentThreadId(), "unexpected create_data[1].m_dwThreadID %x\n",
       create_data[1].m_dwThreadID);
    ok(create_data[1].m_pNext == create_data, "unexpected create_data[1].m_pNext %p\n", create_data[1].m_pNext);

    AtlWinModuleAddCreateWndData(&winmod, create_data+2, (void*)0xdead0003);
    ok(winmod.m_pCreateWndList == create_data+2, "winmod.m_pCreateWndList != create_data\n");
    ok(create_data[2].m_pThis == (void*)0xdead0003, "unexpected create_data[2].m_pThis %p\n", create_data[2].m_pThis);
    ok(create_data[2].m_dwThreadID == GetCurrentThreadId(), "unexpected create_data[2].m_dwThreadID %x\n",
       create_data[2].m_dwThreadID);
    ok(create_data[2].m_pNext == create_data+1, "unexpected create_data[2].m_pNext %p\n", create_data[2].m_pNext);

    p = AtlWinModuleExtractCreateWndData(&winmod);
    ok(p == (void*)0xdead0003, "unexpected AtlWinModuleExtractCreateWndData result %p\n", p);
    ok(winmod.m_pCreateWndList == create_data+1, "winmod.m_pCreateWndList != create_data\n");
    ok(create_data[2].m_pNext == create_data+1, "unexpected create_data[2].m_pNext %p\n", create_data[2].m_pNext);

    create_data[1].m_dwThreadID = 0xdeadbeef;

    p = AtlWinModuleExtractCreateWndData(&winmod);
    ok(p == (void*)0xdead0001, "unexpected AtlWinModuleExtractCreateWndData result %p\n", p);
    ok(winmod.m_pCreateWndList == create_data+1, "winmod.m_pCreateWndList != create_data\n");
    ok(!create_data[0].m_pNext, "unexpected create_data[0].m_pNext %p\n", create_data[0].m_pNext);
    ok(!create_data[1].m_pNext, "unexpected create_data[1].m_pNext %p\n", create_data[1].m_pNext);

    p = AtlWinModuleExtractCreateWndData(&winmod);
    ok(!p, "unexpected AtlWinModuleExtractCreateWndData result %p\n", p);
    ok(winmod.m_pCreateWndList == create_data+1, "winmod.m_pCreateWndList != create_data\n");
}