/*--------------------------------------------------------------------------*/
int sci_drawaxis(char *fname, void* pvApiCtx)
{
    /** XXXXX : un point en suspens c'est le "S" ou une adresse est
     *  stockees ds un unsigned long : est ce sufisant ?
     */
    static rhs_opts opts[] =
    {
        { -1, "dir", -1, 0, 0, NULL},
        { -1, "fontsize", -1, 0, 0, NULL},
        { -1, "format_n", -1, 0, 0, NULL},
        { -1, "seg", -1, 0, 0, NULL},
        { -1, "sub_int", -1, 0, 0, NULL},
        { -1, "textcolor", -1, 0, 0, NULL},
        { -1, "tics", -1, 0, 0, NULL},
        { -1, "ticscolor", -1, 0, 0, NULL},
        { -1, "val", -1, 0, 0, NULL},
        { -1, "x", -1, 0, 0, NULL},
        { -1, "y", -1, 0, 0, NULL},
        { -1, NULL, -1, 0, 0, NULL}
    };

    int iSubwinUID = 0;
    int minrhs = -1, maxrhs = 0, minlhs = 0, maxlhs = 1, nopt = 0;
    char dir = 'l', *format = NULL, tics = 'v', **val = NULL;
    int fontsize = -1, sub_int = 2, seg_flag = 1, textcolor = -1, ticscolor = -1;
    double *x = NULL, *y = NULL;
    int nx = 0, ny = 0, ntics;
    int nb_tics_labels = -1;
    int iRhs = nbInputArgument(pvApiCtx);

    nopt = NumOpt(pvApiCtx);

    CheckInputArgument(pvApiCtx, minrhs, maxrhs + nopt);
    CheckOutputArgument(pvApiCtx, minlhs, maxlhs);

    if (getOptionals(pvApiCtx, fname, opts) == 0)
    {
        /* error */
        return 0;
    }

    iSubwinUID = getOrCreateDefaultSubwin();

    if (opts[0].iPos != -1)
    {
        char* pstDir = NULL;
        //CheckLength
        if (opts[0].iRows != 1 || opts[0].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: %d expected.\n"), fname, opts[0].iPos, opts[0].iRows);
            return 1;
        }

        if (getAllocatedSingleString(pvApiCtx, opts[0].piAddr, &pstDir))
        {
            return 1;
        }
        dir = pstDir[0];
        freeAllocatedSingleString(pstDir);
    }
    if (opts[1].iPos != -1)
    {
        double dblSize = 0;
        //CheckScalar
        if (opts[1].iRows != 1 || opts[1].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, opts[1].iPos);
            return 1;
        }

        getScalarDouble(pvApiCtx, opts[1].piAddr, &dblSize);
        fontsize = (int)dblSize;
    }
    if (opts[2].iPos != -1)
    {
        /* verfier ce que l'on recoit avec "" XXX */
        if (getAllocatedSingleString(pvApiCtx, opts[2].piAddr, &format))
        {
            return 1;
        }
    }

    if (opts[3].iPos != -1)
    {
        double dblSeq = 0;
        //CheckScalar
        if (opts[3].iRows != 1 || opts[3].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, opts[3].iPos);
            freeAllocatedSingleString(format);
            return 1;
        }


        getScalarDouble(pvApiCtx, opts[3].piAddr, &dblSeq);
        seg_flag = (int)dblSeq;
    }

    if (opts[4].iPos != -1)
    {
        double dblSub = 0;
        //CheckScalar
        if (opts[4].iRows != 1 || opts[4].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, opts[4].iPos);
            freeAllocatedSingleString(format);
            return 1;
        }

        getScalarDouble(pvApiCtx, opts[4].piAddr, &dblSub);
        sub_int = (int)dblSub;
    }

    if (opts[5].iPos != -1)
    {
        double dblColor = 0;
        //CheckScalar
        if (opts[5].iRows != 1 || opts[5].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, opts[5].iPos);
            freeAllocatedSingleString(format);
            return 1;
        }

        getScalarDouble(pvApiCtx, opts[5].piAddr, &dblColor);
        textcolor = (int)dblColor;
    }

    if (opts[6].iPos != -1)
    {
        char* pstTics = NULL;
        //CheckLength
        if (opts[6].iRows != 1 || opts[6].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: %d expected.\n"), fname, opts[6].iPos, opts[6].iRows);
            freeAllocatedSingleString(format);
            return 1;
        }

        if (getAllocatedSingleString(pvApiCtx, opts[6].piAddr, &pstTics))
        {
            return 1;
        }
        tics = pstTics[0];
        freeAllocatedSingleString(pstTics);
    }

    if (opts[7].iPos != -1)
    {
        double dblColor = 0;
        //CheckScalar
        if (opts[7].iRows != 1 || opts[7].iCols != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, opts[7].iPos);
            freeAllocatedSingleString(format);
            return 1;
        }

        getScalarDouble(pvApiCtx, opts[7].piAddr, &dblColor);
        ticscolor = (int)dblColor;
    }

    if (opts[8].iPos != -1)
    {
        if (getAllocatedMatrixOfString(pvApiCtx, opts[8].piAddr, &opts[8].iRows, &opts[8].iCols, &val))
        {
            return 1;
        }
    }

    if (opts[9].iPos != -1)
    {
        getMatrixOfDouble(pvApiCtx, opts[9].piAddr, &opts[9].iRows, &opts[9].iCols, &x);
        nx = opts[9].iRows * opts[9].iCols; /* F.Leray OK here opts[9].iRows and opts[9].iCols are integers. */
    }
    else
    {
        static double x_def[1];
        double *bounds;
        int iCurrentSubwinUID = getCurrentSubWin();

        getGraphicObjectProperty(iCurrentSubwinUID, __GO_DATA_BOUNDS__, jni_double_vector, (void **)&bounds);
        nx = 1;
        x = x_def;
        if (dir == 'l')
        {
            x_def[0] = bounds[0];    /* xMin */
        }
        else if (dir == 'r')
        {
            x_def[0] = bounds[1];    /* xMax */
        }
    }

    if (opts[10].iPos != -1)
    {
        getMatrixOfDouble(pvApiCtx, opts[10].piAddr, &opts[10].iRows, &opts[10].iCols, &y);
        ny = opts[10].iRows * opts[10].iCols;
    }
    else
    {
        static double y_def[1];
        double *bounds;
        int iCurrentSubwinUID = getCurrentSubWin();

        getGraphicObjectProperty(iCurrentSubwinUID, __GO_DATA_BOUNDS__, jni_double_vector, (void **)&bounds);
        ny = 1;
        y = y_def;
        if (dir == 'd')
        {
            y_def[0] = bounds[2];    /* yMin */
        }
        else if (dir == 'u')
        {
            y_def[0] = bounds[3];    /* yMax */
        }
    }

    /* compatibility test */
    switch (tics)
    {
        case 'r':
            if (check_xy(fname, dir, 3, opts[9].iPos, opts[9].iRows, opts[9].iCols, x,
                         opts[10].iPos, opts[10].iRows, opts[10].iCols, y, &ntics) == 0)
            {
                ReturnArguments(pvApiCtx);
                freeAllocatedSingleString(format);
                freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
                return 0;
            }
            break;
        case 'i':
            if (check_xy(fname, dir, 4, opts[9].iPos, opts[9].iRows, opts[9].iCols, x,
                         opts[10].iPos, opts[10].iRows, opts[10].iCols, y, &ntics) == 0)
            {
                ReturnArguments(pvApiCtx);
                freeAllocatedSingleString(format);
                freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
                return 0;
            }
            break;
        case 'v':
            if (check_xy(fname, dir, -1, opts[9].iPos, opts[9].iRows, opts[9].iCols, x,
                         opts[10].iPos, opts[10].iRows, opts[10].iCols, y, &ntics) == 0)
            {
                ReturnArguments(pvApiCtx);
                freeAllocatedSingleString(format);
                freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
                return 0;
            }
            break;
        default:
            Scierror(999, _("%: Wrong value for %s '%c': '%s', '%s' and '%s' expected.\n"), fname, "tics", dir, "r", "v", "i");
            freeAllocatedSingleString(format);
            freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
            return 0;
    }

    if (val != NULL)
    {
        //CheckLength
        if (opts[8].iRows * opts[8].iCols != ntics)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: %d expected.\n"), fname, opts[8].iPos, opts[8].iRows * opts[8].iCols);
            freeAllocatedSingleString(format);
            freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
            return 1;
        }

        nb_tics_labels = opts[8].iRows * opts[8].iCols;
    }

    Objdrawaxis(dir, tics, x, &nx, y, &ny, val, sub_int, format, fontsize, textcolor, ticscolor, 'n', seg_flag, nb_tics_labels);

    freeAllocatedSingleString(format);
    if (val != NULL)
    {
        freeAllocatedMatrixOfString(opts[8].iRows, opts[8].iCols, val);
    }
    createScalarHandle(pvApiCtx, iRhs + 1, getHandle(getCurrentObject()));
    AssignOutputVariable(pvApiCtx, 1) = iRhs + 1;
    ReturnArguments(pvApiCtx);
    return 0;
}