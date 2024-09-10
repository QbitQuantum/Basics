bool qca_have_systemstore()
{
    bool ok = false;
    HCERTSTORE hSystemStore;
    hSystemStore = CertOpenSystemStoreA(0, "ROOT");
    if(hSystemStore)
        ok = true;
    CertCloseStore(hSystemStore, 0);
    return ok;
}