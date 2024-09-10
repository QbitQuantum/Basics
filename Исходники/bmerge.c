SEXP bmerge(SEXP iArg, SEXP xArg, SEXP icolsArg, SEXP xcolsArg, SEXP isorted, SEXP rollarg, SEXP rollendsArg, SEXP nomatch, SEXP retFirstArg, SEXP retLengthArg, SEXP allLen1Arg)
{
    int xN, iN, protecti=0;
    roll = 0.0;
    nearest = FALSE;
    enc_warn = TRUE;
    if (isString(rollarg)) {
        if (strcmp(CHAR(STRING_ELT(rollarg,0)),"nearest") != 0) error("roll is character but not 'nearest'");
        roll=1.0;
        nearest=TRUE;       // the 1.0 here is just any non-0.0, so roll!=0.0 can be used later
    } else {
        if (!isReal(rollarg)) error("Internal error: roll is not character or double");
        roll = REAL(rollarg)[0];   // more common case (rolling forwards or backwards) or no roll when 0.0
    }
    rollabs = fabs(roll);

    i = iArg;
    x = xArg;  // set globals so bmerge_r can see them.
    if (!isInteger(icolsArg)) error("Internal error: icols is not integer vector");
    if (!isInteger(xcolsArg)) error("Internal error: xcols is not integer vector");
    if (LENGTH(icolsArg) > LENGTH(xcolsArg)) error("Internal error: length(icols) [%d] > length(xcols) [%d]", LENGTH(icolsArg), LENGTH(xcolsArg));
    icols = INTEGER(icolsArg);
    xcols = INTEGER(xcolsArg);
    xN = LENGTH(VECTOR_ELT(x,0));
    iN = LENGTH(VECTOR_ELT(i,0));
    ncol = LENGTH(icolsArg);    // there may be more sorted columns in x than involved in the join
    for(int col=0; col<ncol; col++) {
        if (icols[col]==NA_INTEGER) error("Internal error. icols[%d] is NA", col);
        if (xcols[col]==NA_INTEGER) error("Internal error. xcols[%d] is NA", col);
        if (icols[col]>LENGTH(i) || icols[col]<1) error("icols[%d]=%d outside range [1,length(i)=%d]", col, icols[col], LENGTH(i));
        if (xcols[col]>LENGTH(x) || xcols[col]<1) error("xcols[%d]=%d outside range [1,length(x)=%d]", col, xcols[col], LENGTH(x));
        int it = TYPEOF(VECTOR_ELT(i, icols[col]-1));
        int xt = TYPEOF(VECTOR_ELT(x, xcols[col]-1));
        if (it != xt) error("typeof x.%s (%s) != typeof i.%s (%s)", CHAR(STRING_ELT(getAttrib(x,R_NamesSymbol),xcols[col]-1)), type2char(xt), CHAR(STRING_ELT(getAttrib(i,R_NamesSymbol),icols[col]-1)), type2char(it));
    }
    if (!isInteger(retFirstArg) || LENGTH(retFirstArg)!=iN) error("retFirst must be integer vector the same length as nrow(i)");
    retFirst = INTEGER(retFirstArg);
    if (!isInteger(retLengthArg) || LENGTH(retLengthArg)!=iN) error("retLength must be integer vector the same length as nrow(i)");
    retLength = INTEGER(retLengthArg);
    if (!isLogical(allLen1Arg) || LENGTH(allLen1Arg) != 1) error("allLen1 must be a length 1 logical vector");
    allLen1 = LOGICAL(allLen1Arg);
    if (!isLogical(rollendsArg) || LENGTH(rollendsArg) != 2) error("rollends must be a length 2 logical vector");
    rollends = LOGICAL(rollendsArg);

    if (nearest && TYPEOF(VECTOR_ELT(i, icols[ncol-1]-1))==STRSXP) error("roll='nearest' can't be applied to a character column, yet.");

    for (int j=0; j<iN; j++) {
        // defaults need to populated here as bmerge_r may well not touch many locations, say if the last row of i is before the first row of x.
        retFirst[j] = INTEGER(nomatch)[0];   // default to no match for NA goto below
        // retLength[j] = 0;   // TO DO: do this to save the branch below and later branches at R level to set .N to 0
        retLength[j] = INTEGER(nomatch)[0]==0 ? 0 : 1;
    }
    allLen1[0] = TRUE;  // All-0 and All-NA are considered all length 1 according to R code currently. Really, it means any(length>1).

    o = NULL;
    if (!LOGICAL(isorted)[0]) {
        SEXP order = PROTECT(vec_init(length(icolsArg), ScalarInteger(1))); // rep(1, length(icolsArg))
        SEXP oSxp = PROTECT(forder(i, icolsArg, ScalarLogical(FALSE), ScalarLogical(TRUE), order, ScalarLogical(FALSE)));
        protecti += 2;
        if (!LENGTH(oSxp)) o = NULL;
        else o = INTEGER(oSxp);
    }

    if (iN) bmerge_r(-1,xN,-1,iN,0,1,1);

    UNPROTECT(protecti);
    return(R_NilValue);
}