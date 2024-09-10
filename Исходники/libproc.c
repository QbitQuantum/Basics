int Pxlookup_by_name(struct ps_prochandle *P, Lmid_t lmid, const char *oname, const char *sname, GElf_Sym *symp, void *sip)
{
    int ol = 0, sl = 0;
    char *Mask;
    const char *obj = oname;
    struct lookup_uc uc;

    if (sname == NULL)
        return -1;

    if (oname == NULL)
        obj = "*";
    else if (strcmp("a.out", oname) == 0)
        obj = P->exe_module->name;
    Mask = malloc((ol = strlen(obj)) + (sl = strlen(sname)) + 2);
    strncpy(Mask, obj, ol);
    strncpy(&Mask[ol++], "!", 1);
    strncpy(&Mask[ol], sname, sl);
    Mask[ol + sl] = 0;

    memset(symp, 0, sizeof(GElf_Sym));
    uc.ps = P;
    uc.cd = symp;
    uc.f = NULL;

    if (SymEnumSymbols(P->phandle, 0, Mask, MyEnumSymbolsCallback, &uc) == FALSE) {
        dprintf("SymEnumSymbols failed (%d): %x\n", P->pid, GetLastError());
        free(Mask);
        return -1;
    }
    free(Mask);

    if (symp->st_value != 0)
        return 0;

    return dw_lookup_by_name(P, oname, sname, symp);
}