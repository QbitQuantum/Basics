static bool import_integer(int* pvCtx, int _iDatasetId, int _iItemPos, int *_piAddress, char *_pstVarname)
{
    int iRet = 0;
    int iDims = 0;
    int* piDims = NULL;
    int iComplex = 0;
    int iSize = 0;
    int iPrec = 0;
    SciErr sciErr;

    iRet = getDatasetInfo(_iDatasetId, &iComplex, &iDims, NULL);
    if (iRet < 0)
    {
        return false;
    }

    piDims = (int*)MALLOC(sizeof(int) * iDims);
    iSize = getDatasetInfo(_iDatasetId, &iComplex, &iDims, piDims);

    iRet = getDatasetPrecision(_iDatasetId, &iPrec);
    if (iRet)
    {
        FREE(piDims);
        return false;
    }

    switch (iPrec)
    {
        case SCI_INT8:
        {
            char *pcData = NULL;

            pcData = (char *)MALLOC(sizeof(char) * iSize);
            iRet = readInteger8Matrix(_iDatasetId, pcData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfInteger8(pvCtx, _pstVarname, piDims[0], piDims[1], pcData);
            }
            else
            {
                sciErr = createMatrixOfInteger8InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], pcData);
            }

            FREE(pcData);
        }
        break;
        case SCI_UINT8:
        {
            unsigned char *pucData = NULL;

            pucData = (unsigned char *)MALLOC(sizeof(unsigned char) * iSize);
            iRet = readUnsignedInteger8Matrix(_iDatasetId, pucData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfUnsignedInteger8(pvCtx, _pstVarname, piDims[0], piDims[1], pucData);
            }
            else
            {
                sciErr = createMatrixOfUnsignedInteger8InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], pucData);
            }

            FREE(pucData);
        }
        break;
        case SCI_INT16:
        {
            short *psData = NULL;

            psData = (short *)MALLOC(sizeof(short) * iSize);
            iRet = readInteger16Matrix(_iDatasetId, psData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfInteger16(pvCtx, _pstVarname, piDims[0], piDims[1], psData);
            }
            else
            {
                sciErr = createMatrixOfInteger16InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], psData);
            }

            FREE(psData);
        }
        break;
        case SCI_UINT16:
        {
            unsigned short *pusData = NULL;

            pusData = (unsigned short *)MALLOC(sizeof(unsigned short) * iSize);
            iRet = readUnsignedInteger16Matrix(_iDatasetId, pusData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfUnsignedInteger16(pvCtx, _pstVarname, piDims[0], piDims[1], pusData);
            }
            else
            {
                sciErr = createMatrixOfUnsignedInteger16InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], pusData);
            }

            FREE(pusData);
        }
        break;
        case SCI_INT32:
        {
            int *piData = NULL;

            piData = (int *)MALLOC(sizeof(int) * iSize);
            iRet = readInteger32Matrix(_iDatasetId, piData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfInteger32(pvCtx, _pstVarname, piDims[0], piDims[1], piData);
            }
            else
            {
                sciErr = createMatrixOfInteger32InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], piData);
            }

            FREE(piData);
        }
        break;
        case SCI_UINT32:
        {
            unsigned int *puiData = NULL;

            puiData = (unsigned int *)MALLOC(sizeof(unsigned int) * iSize);
            iRet = readUnsignedInteger32Matrix(_iDatasetId, puiData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfUnsignedInteger32(pvCtx, _pstVarname, piDims[0], piDims[1], puiData);
            }
            else
            {
                sciErr = createMatrixOfUnsignedInteger32InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], puiData);
            }

            FREE(puiData);
        }
        break;
        case SCI_INT64:
        {
#ifdef __SCILAB_INT64__
            long long *pllData = NULL;

            pllData = (long long *)MALLOC(sizeof(long long) * iSize);
            iRet = readInteger64Matrix(_iDatasetId, pllData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfInteger64(pvCtx, _pstVarname, piDims[0], piDims[1], pllData);
            }
            else
            {
                sciErr = createMatrixOfInteger64InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], pllData);
            }

            FREE(pllData);
#else
            FREE(piDims);
            return false;
#endif
        }
        break;
        case SCI_UINT64:
        {
#ifdef __SCILAB_INT64__
            unsigned long long *pullData = NULL;

            pullData = (unsigned long long *)MALLOC(sizeof(unsigned long long) * iSize);
            iRet = readUnsignedInteger64Matrix(_iDatasetId, pullData);
            if (iRet)
            {
                FREE(piDims);
                return false;
            }

            if (_piAddress == NULL)
            {
                sciErr = createNamedMatrixOfUnsignedInteger64(pvCtx, _pstVarname, piDims[0], piDims[1], pullData);
            }
            else
            {
                sciErr = createMatrixOfUnsignedInteger64InNamedList(pvCtx, _pstVarname, _piAddress, _iItemPos, piDims[0], piDims[1], pullData);
            }

            FREE(pullData);
#else
            FREE(piDims);
            return false;
#endif
        }
        break;
        default:
            return false;
    }

    FREE(piDims);

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return false;
    }

    return true;
}