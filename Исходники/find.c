/**
 *  Find the short option descriptor for the current option
 *
 * @param pOpts      option data
 * @param optValue   option flag character
 * @param pOptState  state about current option
 */
LOCAL tSuccess
opt_find_short(tOptions* pOpts, uint_t optValue, tOptState* pOptState)
{
    tOptDesc*  pRes = pOpts->pOptDesc;
    int        ct   = pOpts->optCt;

    /*
     *  Search the option list
     */
    do  {
        if (optValue != pRes->optValue)
            continue;

        if (SKIP_OPT(pRes)) {
            if (  (pRes->fOptState == (OPTST_OMITTED | OPTST_NO_INIT))
               && (pRes->pz_Name != NULL)) {
                if ((pOpts->fOptSet & OPTPROC_ERRSTOP) == 0)
                    return FAILURE;
        
                fprintf(stderr, zDisabledErr, pOpts->pzProgPath, pRes->pz_Name);
                if (pRes->pzText != NULL)
                    fprintf(stderr, SET_OFF_FMT, pRes->pzText);
                fputc(NL, stderr);
                (*pOpts->pUsageProc)(pOpts, EXIT_FAILURE);
                /* NOTREACHED */
                _exit(EXIT_FAILURE); /* to be certain */
            }
            goto short_opt_error;
        }

        pOptState->pOD     = pRes;
        pOptState->optType = TOPT_SHORT;
        return SUCCESS;

    } while (pRes++, --ct > 0);

    /*
     *  IF    the character value is a digit
     *    AND there is a special number option ("-n")
     *  THEN the result is the "option" itself and the
     *       option is the specially marked "number" option.
     */
    if (  IS_DEC_DIGIT_CHAR(optValue)
       && (pOpts->specOptIdx.number_option != NO_EQUIVALENT) ) {
        pOptState->pOD = \
        pRes           = pOpts->pOptDesc + pOpts->specOptIdx.number_option;
        (pOpts->pzCurOpt)--;
        pOptState->optType = TOPT_SHORT;
        return SUCCESS;
    }

 short_opt_error:

    /*
     *  IF we are to stop on errors (the default, actually)
     *  THEN call the usage procedure.
     */
    if ((pOpts->fOptSet & OPTPROC_ERRSTOP) != 0) {
        fprintf(stderr, zIllOptChr, pOpts->pzProgPath, optValue);
        (*pOpts->pUsageProc)(pOpts, EXIT_FAILURE);
        /* NOTREACHED */
        _exit(EXIT_FAILURE); /* to be certain */
    }

    return FAILURE;
}