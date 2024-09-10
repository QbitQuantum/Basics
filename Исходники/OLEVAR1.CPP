COleVariant::COleVariant(LPCITEMIDLIST pidl)
{
    AfxVariantInit(this);

    if (pidl != NULL)
    {
        // walk through entries in the list and accumulate their size

        UINT cbTotal = 0;
        SAFEARRAY *psa = NULL;
        LPCITEMIDLIST pidlWalker = pidl;

        while (pidlWalker->mkid.cb)
        {
            cbTotal += pidlWalker->mkid.cb;
            pidlWalker = (LPCITEMIDLIST)
                         (((LPBYTE)pidlWalker) + pidlWalker->mkid.cb);
        }

        // add the base structure size
        cbTotal += sizeof(ITEMIDLIST);

        // get a safe array for them
        psa = SafeArrayCreateVector(VT_UI1, 0, cbTotal);

        // copy it and set members
        if (psa != NULL)
        {
            memcpy(psa->pvData, (LPBYTE) pidl, cbTotal);
            vt = VT_ARRAY | VT_UI1;
            parray = psa;
        }
    }
}