/*--------------------------------------------------------------------------*/
int sci_delete(char *fname, unsigned long fname_len)
{
    SciErr sciErr;

    int* piAddrl1 = NULL;
    long long* l1 = NULL;
    int* piAddrl2 = NULL;
    char* l2 = NULL;

    int m1 = 0, n1 = 0, lw = 0;
    unsigned long hdl = 0;
    int nb_handles = 0, i = 0, dont_overload = 0;
    int iObjUID = 0;
    int iFigureUID = 0;
    int* piChildrenUID = NULL;
    int iChildrenCount = 0;
    int* childrencount = &iChildrenCount;
    int iHidden = 0;
    int *piHidden = &iHidden;

    int iParentUID = 0;
    int* piParentUID = &iParentUID;
    int iParentType = -1;
    int *piParentType = &iParentType;
    int iObjType = -1;
    int *piObjType = &iObjType;

    CheckInputArgument(pvApiCtx, 0, 1);
    CheckOutputArgument(pvApiCtx, 0, 1);

    if (nbInputArgument(pvApiCtx) == 0)               /* Delete current object */
    {
        iObjUID = getCurrentObject();
        if (iObjUID == 0)
        {
            //No current object, we can leave
            AssignOutputVariable(pvApiCtx, 1) = 0;
            ReturnArguments(pvApiCtx);
            return 0;
        }

        hdl = (unsigned long)getHandle(iObjUID);
        dont_overload = 1;
        nb_handles = 1;
    }
    else
    {
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddrl1);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 1;
        }

        switch (getInputArgumentType(pvApiCtx, 1))
        {
            case sci_matrix:
            {
                if (isEmptyMatrix(pvApiCtx, piAddrl1))
                {
                    AssignOutputVariable(pvApiCtx, 1) = 0;
                    ReturnArguments(pvApiCtx);
                    return 1;
                }
                else
                {
                    Scierror(202, _("%s: Wrong type for input argument #%d: Handle matrix expected.\n"), fname, 1);
                    return 1;
                }
                break;
            }
            case sci_handles:      /* delete Entity given by a handle */

                // Retrieve a matrix of handle at position 1.
                sciErr = getMatrixOfHandle(pvApiCtx, piAddrl1, &m1, &n1, &l1); /* Gets the Handle passed as argument */
                if (sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    Scierror(202, _("%s: Wrong type for input argument #%d: Handle matrix expected.\n"), fname, 1);
                    return 1;
                }

                nb_handles = m1 * n1;

                if (nbInputArgument(pvApiCtx) == 2)
                {
                    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddrl2);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 1;
                    }

                    // Retrieve a matrix of double at position 2.
                    if (getAllocatedSingleString(pvApiCtx, piAddrl2, &l2))   /* Gets the command name */
                    {
                        Scierror(202, _("%s: Wrong type for argument #%d: A string expected.\n"), fname, 2);
                        return 1;
                    }
                }
                hdl = (unsigned long) * (l1); /* Puts the value of the Handle to hdl */
                break;
            case sci_strings:      /* delete("all") */
                CheckInputArgument(pvApiCtx, 1, 1);
                sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddrl2);
                if (sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    return 1;
                }

                // Retrieve a matrix of double at position 1.
                if (getAllocatedSingleString(pvApiCtx, piAddrl2, &l2))
                {
                    Scierror(202, _("%s: Wrong type for argument #%d: A string expected.\n"), fname, 1);
                    return 1;
                }

                if (strcmp((l2), "all") == 0)
                {
                    int i = 0;
                    int iFigureNumber = sciGetNbFigure();

                    if (iFigureNumber == 0)
                    {
                        //no graphic windows, we can leave
                        AssignOutputVariable(pvApiCtx, 1) = 0;
                        ReturnArguments(pvApiCtx);
                        return 0;
                    }

                    iFigureUID = getCurrentFigure();

                    getGraphicObjectProperty(iFigureUID, __GO_CHILDREN_COUNT__, jni_int, (void **)&childrencount);

                    getGraphicObjectProperty(iFigureUID, __GO_CHILDREN__, jni_int_vector, (void **)&piChildrenUID);

                    for (i = 0; i < childrencount[0]; ++i)
                    {
                        getGraphicObjectProperty(piChildrenUID[i], __GO_HIDDEN__, jni_bool, (void **)&piHidden);
                        if (iHidden == 0)
                        {
                            deleteGraphicObject(piChildrenUID[i]);
                        }
                    }
                    /*
                     * Clone a new Axes object using the Axes model which is then
                     * attached to the 'cleaned' Figure.
                     */
                    cloneAxesModel(iFigureUID);

                    AssignOutputVariable(pvApiCtx, 1) = 0;
                    ReturnArguments(pvApiCtx);

                    return 0;
                }
                else
                {
                    Scierror(999, _("%s: Wrong value for input argument #%d: '%s' expected.\n"), fname, 1, "all");
                    return 0;
                }
                break;
            default:
                // Overload
                lw = 1 + nbArgumentOnStack(pvApiCtx) - nbInputArgument(pvApiCtx);
                C2F(overload) (&lw, "delete", 6);
                return 0;
        }
    }

    for (i = 0; i < nb_handles; i++)
    {
        int iTemp = 0;
        if (nbInputArgument(pvApiCtx) != 0)
        {
            hdl = (unsigned long) * (l1 + i); /* Puts the value of the Handle to hdl */
        }

        iObjUID = getObjectFromHandle(hdl);

        if (iObjUID == 0)
        {
            Scierror(999, _("%s: The handle is not valid.\n"), fname);
            return 0;
        }

        if (isFigureModel(iObjUID) || isAxesModel(iObjUID))
        {
            Scierror(999, _("This object cannot be deleted.\n"));
            return 0;
        }

        /* Object type */
        getGraphicObjectProperty(iObjUID, __GO_TYPE__, jni_int, (void **)&piObjType);
        if (iObjType == __GO_AXES__)
        {
            /* Parent object */
            iParentUID = getParentObject(iObjUID);
            /* Parent type */
            getGraphicObjectProperty(iParentUID, __GO_TYPE__, jni_int, (void **)&piParentType);
        }

        if (iObjType == __GO_LABEL__)
        {
            Scierror(999, _("A Label object cannot be deleted.\n"));
            return 0;
        }

        //bug #11485 : duplicate pobjUID before delete it.
        iTemp = iObjUID;
        deleteGraphicObject(iObjUID);

        /*
         ** All figure must have at least one axe child.
         ** If the last one is removed, add a new default one.
         */
        if (iObjType == __GO_AXES__ && iParentType == __GO_FIGURE__)
        {
            int iChild = 0;
            int iChildCount = 0;
            int *piChildCount = &iChildCount;
            char **pstChildren = NULL;
            int iChildType = -1;
            int *piChildType = &iChildType;
            int iAxesFound = 0;
            int iDefaultAxes = -1;
            int *piDefaultAxes = &iDefaultAxes;

            getGraphicObjectProperty(iParentUID, __GO_CHILDREN_COUNT__, jni_int, (void **)&piChildCount);
            getGraphicObjectProperty(iParentUID, __GO_CHILDREN__, jni_int_vector, (void **)&piChildrenUID);
            getGraphicObjectProperty(iParentUID, __GO_DEFAULT_AXES__, jni_bool, (void **)&piDefaultAxes);

            for (iChild = 0; iChild < iChildCount; iChild++)
            {
                getGraphicObjectProperty(piChildrenUID[iChild], __GO_TYPE__, jni_int, (void **)&piChildType);
                if (iChildType == __GO_AXES__)
                {
                    if (getCurrentSubWin() == iTemp) // Current axes has been deleted
                    {
                        setCurrentSubWin(piChildrenUID[iChild]);
                    }
                    iAxesFound = 1;
                    break;
                }
            }
            if (!iAxesFound && iDefaultAxes != 0)
            {

                /*
                 * Clone a new Axes object using the Axes model which is then
                 * attached to the newly created Figure.
                 */
                cloneAxesModel(iParentUID);
            }
        }
    }

    if (!dont_overload)
    {
        // Overload
        lw = 1 + nbArgumentOnStack(pvApiCtx) - nbInputArgument(pvApiCtx);
        C2F(overload) (&lw, "delete", 6);
    }
    else
    {
        AssignOutputVariable(pvApiCtx, 1) = 0;
        ReturnArguments(pvApiCtx);
    }

    if (l2)
    {
        freeAllocatedSingleString(l2);
    }

    return 0;
}