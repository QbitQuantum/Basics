void DbgInfoCheck (void)
/* Do checks on all hll debug info symbols when assembly is complete */
{
    /* When parsing the debug statements for HLL symbols, we have already
    ** tagged the functions to their asm counterparts. This wasn't done for
    ** C symbols, since we will allow forward declarations. So we have to
    ** resolve the normal C symbols now.
    */
    unsigned I;
    for (I = 0; I < CollCount (&HLLDbgSyms); ++I) {

        /* Get the next symbol */
        HLLDbgSym* S = CollAtUnchecked (&HLLDbgSyms, I);

        /* Ignore functions and auto symbols, because the later live on the
        ** stack and don't have corresponding asm symbols.
        */
        if (HLL_IS_FUNC (S->Flags) || HLL_GET_SC (S->Flags) == HLL_SC_AUTO) {
            continue;
        }

        /* Safety */
        CHECK (S->Sym == 0 && S->Scope != 0);

        /* Search for the symbol name */
        S->Sym = SymFindAny (S->Scope, GetStrBuf (S->AsmName));
        if (S->Sym == 0) {
            PError (&S->Pos, "Assembler symbol '%s' not found",
                    GetString (S->AsmName));
        } else {
            /* Set the backlink */
            S->Sym->HLLSym = S;
        }

    }
}