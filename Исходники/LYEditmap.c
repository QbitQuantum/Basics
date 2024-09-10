int EditBinding(int xlkc)
{
    int editaction, xleac = LYE_UNMOD;
    int c = xlkc & LKC_MASK;

    if (xlkc == -1)
	return LYE_NOP;		/* maybe LYE_ABORT? or LYE_FORM_LAC|LYK_UNKNOWN? */
#ifdef NOT_ASCII
    if (c < 256) {
	c = TOASCII(c);
    }
#endif
#ifdef USE_ALT_BINDINGS
    /*
     * Get intermediate code from one of the lynxkeycode+modifier tables if
     * applicable, otherwise get the lynxeditactioncode directly.  If we have
     * more than one modifier bits, the first currently wins.  - kw
     */
    if (xlkc & LKC_ISLECLAC) {
	return LKC2_TO_LEC(xlkc);
    } else if (xlkc & LKC_MOD1) {
	xleac = LKC_TO_LEC_M1(c);
    } else if (xlkc & LKC_MOD2) {
	xleac = LKC_TO_LEC_M2(c);
    } else if (xlkc & LKC_MOD3) {
	xleac = LKC_TO_LEC_M3(c);
    } else {
	xleac = UCH(CurrentLineEditor()[c]);
    }
#endif
    /*
     * If we have an intermediate code that says "same as without modifier",
     * look that up now; otherwise we are already done.  - kw
     */
    if (xleac == LYE_UNMOD) {
	editaction = CurrentLineEditor()[c];
    } else {
	editaction = xleac;
    }
    return editaction;
}