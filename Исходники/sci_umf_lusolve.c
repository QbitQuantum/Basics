int sci_umf_lusolve(char* fname, unsigned long l)
{
    SciErr sciErr;

    int mb      = 0;
    int nb      = 0;
    int it_flag = 0;
    int i       = 0;
    int j       = 0;

    int NoTranspose = 0;
    int NoRaffinement = 0;
    SciSparse AA;
    CcsSparse A;

    /* umfpack stuff */
    double Info[UMFPACK_INFO]; // double *Info = (double *) NULL;
    double Control[UMFPACK_CONTROL];
    void* Numeric = NULL;
    int lnz = 0, unz = 0, n = 0, n_col = 0, nz_udiag = 0, umf_flag = 0;
    int* Wi = NULL;
    int mW = 0;
    double *W = NULL;

    int iComplex = 0;

    int* piAddr1 = NULL;
    int* piAddr2 = NULL;
    int* piAddr3 = NULL;
    int* piAddr4 = NULL;

    double* pdblBR = NULL;
    double* pdblBI = NULL;
    double* pdblXR = NULL;
    double* pdblXI = NULL;

    int mA              = 0; // rows
    int nA              = 0; // cols
    int iNbItem         = 0;
    int* piNbItemRow    = NULL;
    int* piColPos       = NULL;
    double* pdblSpReal  = NULL;
    double* pdblSpImg   = NULL;

    /* Check numbers of input/output arguments */
    CheckInputArgument(pvApiCtx, 2, 4);
    CheckOutputArgument(pvApiCtx, 1, 1);

    /* First get arg #1 : the pointer to the LU factors */
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 1;
    }

    sciErr = getPointer(pvApiCtx, piAddr1, &Numeric);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 1;
    }

    /* Check if this pointer is a valid ref to a umfpack LU numeric object */
    if ( ! IsAdrInList(Numeric, ListNumeric, &it_flag) )
    {
        Scierror(999, _("%s: Wrong value for input argument #%d: Must be a valid reference to (umf) LU factors.\n"), fname, 1);
        return 1;
    }

    /*  get some parameters of the factorization (for some checking) */
    if ( it_flag == 0 )
    {
        umfpack_di_get_lunz(&lnz, &unz, &n, &n_col, &nz_udiag, Numeric);
    }
    else
    {
        iComplex = 1;
        umfpack_zi_get_lunz(&lnz, &unz, &n, &n_col, &nz_udiag, Numeric);
    }

    if ( n != n_col )
    {
        Scierror(999, _("%s: An error occurred: %s.\n"), fname, _("This is not a factorization of a square matrix"));
        return 1;
    }

    if ( nz_udiag < n )
    {
        Scierror(999, _("%s: An error occurred: %s.\n"), fname, _("This is a factorization of a singular matrix"));
        return 1;
    }

    /* Get now arg #2 : the vector b */
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 1;
    }

    if (isVarComplex(pvApiCtx, piAddr2))
    {
        iComplex = 1;
        sciErr = getComplexMatrixOfDouble(pvApiCtx, piAddr2, &mb, &nb, &pdblBR, &pdblBI);
    }
    else
    {
        sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &mb, &nb, &pdblBR);
    }

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 1;
    }

    if (mb != n || nb < 1)    /* test if the right hand side is compatible */
    {
        Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, 2);
        return 1;
    }

    /* allocate memory for the solution x */
    if (iComplex)
    {
        sciErr = allocComplexMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, mb, nb, &pdblXR, &pdblXI);
    }
    else
    {
        sciErr = allocMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, mb, nb, &pdblXR);
    }

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 1;
    }

    /*  selection between the different options :
     *   -- solving Ax=b or A'x=b (Note: we could add  A.'x=b)
     *   -- with or without raffinement
     */

    if (nbInputArgument(pvApiCtx) == 2)
    {
        NoTranspose = 1;
        NoRaffinement = 1;
    }
    else  /* 3 or 4 input arguments but the third must be a string */
    {
        char* pStr = NULL;
        sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddr3);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 1;
        }

        getAllocatedSingleString(pvApiCtx, piAddr3, &pStr);
        if (strcmp(pStr, "Ax=b") == 0)
        {
            NoTranspose = 1;
        }
        else if ( strcmp(pStr, "A'x=b") == 0 )
        {
            NoTranspose = 0;
        }
        else
        {
            Scierror(999, _("%s: Wrong input argument #%d: '%s' or '%s' expected.\n"), fname, 3, "Ax=b", "A'x=b");
            return 1;
        }

        if (nbInputArgument(pvApiCtx) == 4)
        {
            sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddr4);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 1;
            }

            if (isVarComplex(pvApiCtx, piAddr4))
            {
                AA.it = 1;
                sciErr = getComplexSparseMatrix(pvApiCtx, piAddr4, &mA, &nA, &iNbItem, &piNbItemRow, &piColPos, &pdblSpReal, &pdblSpImg);
            }
            else
            {
                AA.it = 0;
                sciErr = getSparseMatrix(pvApiCtx, piAddr4, &mA, &nA, &iNbItem, &piNbItemRow, &piColPos, &pdblSpReal);
            }

            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 1;
            }

            // fill struct sparse
            AA.m     = mA;
            AA.n     = nA;
            AA.nel   = iNbItem;
            AA.mnel  = piNbItemRow;
            AA.icol  = piColPos;
            AA.R     = pdblSpReal;
            AA.I     = pdblSpImg;

            /*  some check... but we can't be sure that the matrix corresponds to the LU factors */
            if ( mA != nA || mA != n || AA.it != it_flag )
            {
                Scierror(999, _("%s: Wrong size for input argument #%d: %s.\n"), fname, 4, _("Matrix is not compatible with the given LU factors"));
                return 1;
            }

            NoRaffinement = 0;
        }
        else
        {
            NoRaffinement = 1;   /* only 3 input var => no raffinement */
        }
    }

    /* allocate memory for umfpack_di_wsolve usage or umfpack_zi_wsolve usage*/
    Wi = (int*)MALLOC(n * sizeof(int));

    if (it_flag == 1)
    {
        if (NoRaffinement)
        {
            mW = 4 * n;
        }
        else
        {
            mW = 10 * n;
        }
    }
    else
    {
        if (NoRaffinement)
        {
            mW = n;
        }
        else
        {
            mW = 5 * n;
        }
    }

    W = (double*)MALLOC(mW * sizeof(double));

    if (NoRaffinement == 0)
    {
        SciSparseToCcsSparse(&AA, &A);
    }
    else
    {
        A.p = NULL;
        A.irow = NULL;
        A.R = NULL;
        A.I = NULL;
    }

    /* get the pointer for b */
    if (it_flag == 1  &&  pdblBI == NULL)
    {
        int iSize = mb * nb * sizeof(double);
        pdblBI = (double*)MALLOC(iSize);
        memset(pdblBI, 0x00, iSize);
    }

    /* init Control */
    if (it_flag == 0)
    {
        umfpack_di_defaults(Control);
    }
    else
    {
        umfpack_zi_defaults(Control);
    }

    if (NoRaffinement)
    {
        Control[UMFPACK_IRSTEP] = 0;
    }

    if (NoTranspose)
    {
        umf_flag = UMFPACK_A;
    }
    else
    {
        umf_flag = UMFPACK_At;
    }

    if (it_flag == 0)
    {
        for (j = 0; j < nb ; j++)
        {
            umfpack_di_wsolve(umf_flag, A.p, A.irow, A.R, &pdblXR[j * mb], &pdblBR[j * mb], Numeric, Control, Info, Wi, W);
        }

        if (iComplex == 1)
        {
            for (j = 0; j < nb ; j++)
            {
                umfpack_di_wsolve(umf_flag, A.p, A.irow, A.R, &pdblXI[j * mb], &pdblBI[j * mb], Numeric, Control, Info, Wi, W);
            }
        }
    }
    else
    {
        for (j = 0; j < nb ; j++)
        {
            umfpack_zi_wsolve(umf_flag, A.p, A.irow, A.R, A.I, &pdblXR[j * mb], &pdblXI[j * mb], &pdblBR[j * mb], &pdblBI[j * mb], Numeric, Control, Info, Wi, W);
        }
    }

    if (isVarComplex(pvApiCtx, piAddr2) == 0)
    {
        FREE(pdblBI);
    }

    freeCcsSparse(A);

    FREE(W);
    FREE(Wi);

    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    ReturnArguments(pvApiCtx);
    return 0;
}