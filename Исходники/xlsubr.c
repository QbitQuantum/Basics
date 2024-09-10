/* xlgetkeyarg - get a keyword argument */
int xlgetkeyarg P2C(LVAL, key, LVAL *, pval)
{
#if 0
    LVAL *argv=xlargv;
    int argc=xlargc;
    for (argv = xlargv, argc = xlargc; (argc -= 2) >= 0; argv += 2) {
	if (*argv == key) {
	    *pval = *++argv;

	    /* delete the used argument */
	    if (argc>0) MEMMOVE(argv-1, argv+1, argc*sizeof(LVAL));
	    xlargc -=2;

	    return (TRUE);
	}
    }
    return (FALSE);
#else
    int argc = xlargc;
    int result = FALSE;
    int i, first;
    LVAL *argv = xlargv;

    /* First check if we have an even number of arguments remaining */
    if (( argc & 1 )) {
        xlfail( "keyword value missing" );
        return FALSE;
    }
    /*
     * Argument count is ok, now we traverse the remaining key-value-pairs to
     * search for the requested key. During the traversal, we move the
     * matching argument to the front of the remaining arguments, so used
     * arguments get popped off the stack only at the front, no entries are
     * overwritten. 
     * Tricky: keyword processing is specified to take only the leftmost
     * occurence of a key-value-pair in the argument list and ignore the
     * others - to allow the C-macro xllastarg to work correctly, we search
     * all remaining arguments and move the unused pairs to the front of the
     * remaining arguments but just behind the used one. This method allows the
     * function xlbaktrace to print a correct arguments during a backtrace as
     * no arguments are overwritten (this has been the case in the old
     * implementation above) but only their order gets changed. Remind: the
     * sorting is stable (the leftmost key od a duplicate remains the
     * leftmost).
     * FIXME:
     * Still untreated is the occurence of :allow_other_keys in the argument
     * list: xllastarg should be in closer contact with this function to do
     * the correct thing. However: I do not expect functions having so complex
     * argument-lists implemented in C, so the provided macros will work fine.
     * From: [email protected] (Wolfgang Kechel - Patzschke + Rasp GmbH)
     */
     for ( i = first = 0; i < argc; i += 2 ) {
         if ( argv[i] == key ) {
             if ( ! result ) {
                 *pval = xlargv[i+1];
                 result = TRUE;
             }
             if ( i != first ) {
                 LVAL temp[2];
                 int j;

                 temp[0] = argv[i];
                 temp[1] = argv[i+1];
                 for ( j = i+1; j > first; --j )
                     argv[j] = argv[j-2];
                 argv[first] = temp[0];
                 argv[first+1] = temp[1];
             }
             first += 2;
         }
     }
     xlargc -= first;
     xlargv += first;
     return result;
#endif
}