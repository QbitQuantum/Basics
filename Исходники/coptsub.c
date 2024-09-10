unsigned OptSub3 (CodeSeg* S)
/* Search for a call to decaxn and replace it by an 8 bit sub if the X register
** is not used later.
*/
{
    unsigned Changes = 0;

    /* Walk over the entries */
    unsigned I = 0;
    while (I < CS_GetEntryCount (S)) {

        CodeEntry* E;

        /* Get next entry */
        E = CS_GetEntry (S, I);

        /* Check for the sequence */
        if (E->OPC == OP65_JSR                          &&
            strncmp (E->Arg, "decax", 5) == 0           &&
            IsDigit (E->Arg[5])                         &&
            E->Arg[6] == '\0'                           &&
            !RegXUsed (S, I+1)) {

            CodeEntry* X;
            const char* Arg;

            /* Insert new code behind the sequence */
            X = NewCodeEntry (OP65_SEC, AM65_IMP, 0, 0, E->LI);
            CS_InsertEntry (S, X, I+1);

            Arg = MakeHexArg (E->Arg[5] - '0');
            X = NewCodeEntry (OP65_SBC, AM65_IMM, Arg, 0, E->LI);
            CS_InsertEntry (S, X, I+2);

            /* Delete the old code */
            CS_DelEntry (S, I);

            /* Remember, we had changes */
            ++Changes;

        }

        /* Next entry */
        ++I;

    }

    /* Return the number of changes made */
    return Changes;
}