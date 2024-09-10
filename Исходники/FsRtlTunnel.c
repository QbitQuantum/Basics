void TestFsRtlInitializeTunnelCache()
{
    SIZE_T eq;
    T = ExAllocatePool(PagedPool, sizeof(TUNNEL));
    ok(T != NULL, "PTUNEL is NULL after allocated memory\n");
    Tb = ExAllocatePool(PagedPool, sizeof(TUNNEL));
    ok(Tb != NULL, "PTUNEL is NULL after allocated memory\n");

    memset((void*)T, 0, sizeof(TUNNEL));
    memset((void*)Tb, 0, sizeof(TUNNEL));

    FsRtlInitializeTunnelCache(T);

    eq = RtlCompareMemory((const VOID*)T, (const VOID*)Tb,  sizeof(TUNNEL));

    ok ( eq != sizeof(TUNNEL), "FsRtlInitializeTunnelCache function did not change anything in the memory at the address PTUNEL.\n"); 
}