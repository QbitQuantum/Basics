void PEXPORT InitCompiledAtoms(HANDLE hResInst, unsigned size, unsigned base)
{
    unsigned i;

    CompiledAtoms = GLOBALALLOC(GHND, size * sizeof(ATOMID));
    lpCA = (ATOMID far *) GLOBALLOCK(CompiledAtoms);

    for (i = 0; i < size; ++i) {
        LoadString(hResInst, i + base, return_buffer, RET_BUFFER_LEN);
        lpCA[i] = KppAddAtom(return_buffer);
        KppSetAtomNoReclaim(lpCA[i]);
    }

    GLOBALUNLOCK(CompiledAtoms);
}    