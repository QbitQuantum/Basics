NDArray *roper::getData()
{
    NDArray *pArray = NULL;
    VARIANT varData, varResult;
    short result;
    SAFEARRAY *pData;
    int dim;
    LONG lbound, ubound;
    size_t dims[ND_ARRAY_MAX_DIMS];
    int nDims;
    VARTYPE varType;
    NDDataType_t dataType;
    int docDataType;
    NDArrayInfo arrayInfo;
    void HUGEP *pVarData;
    bool typeMismatch;
    const char *functionName = "getData";
        
    VariantInit(&varData);
    VariantInit(&varResult);
    try {
        this->pDocFile->GetFrame(1, &varData);
        varResult = this->pDocFile->GetParam(DM_DATATYPE, &result);
        docDataType = varResult.lVal;
        pData = varData.parray;
        nDims = SafeArrayGetDim(pData);
        for (dim=0; dim<nDims; dim++) {
            SafeArrayGetLBound(pData, dim+1, &lbound);
            SafeArrayGetUBound(pData, dim+1, &ubound);
            dims[dim] = ubound - lbound + 1;
        }
        SafeArrayGetVartype(pData, &varType);
        typeMismatch = TRUE;
        switch (docDataType) {
            case X_BYTE:
                dataType = NDUInt8;
                typeMismatch = (varType != VT_UI1);
                break;
            case X_SHORT:
                dataType = NDInt16;
                typeMismatch = (varType != VT_I2);
                break;
            case X_UINT16:
                dataType = NDUInt16;
                typeMismatch = (varType != VT_I2);
                break;
            case X_LONG:
                dataType = NDInt32;
                typeMismatch = (varType != VT_I4);
                break;
            case X_ULONG:
                dataType = NDUInt32;
                typeMismatch = (varType != VT_I4);
                break;
            case X_FLOAT:
                dataType = NDFloat32;
                typeMismatch = (varType != VT_R4);
                break;
            case X_DOUBLE:
                dataType = NDFloat64;
                typeMismatch = (varType != VT_R8);
                break;
            default:
                asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
                    "%s:%s: unknown data type = %d\n", 
                    driverName, functionName, docDataType);
                return(NULL);
        }
        if (typeMismatch) {
            asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
                "%s:%s: data type mismatch: docDataType=%d, varType=%d\n", 
                driverName, functionName, docDataType, varType);
            return(NULL);
        }
        pArray = this->pNDArrayPool->alloc(nDims, dims, dataType, 0, NULL);
        pArray->getInfo(&arrayInfo);
        SafeArrayAccessData(pData, &pVarData);
        memcpy(pArray->pData, pVarData, arrayInfo.totalBytes);
        SafeArrayUnaccessData(pData);
        SafeArrayDestroy(pData);
        setIntegerParam(NDArraySize, arrayInfo.totalBytes);
        setIntegerParam(NDArraySizeX, (int)dims[0]);
        setIntegerParam(NDArraySizeY, (int)dims[1]);
        setIntegerParam(NDDataType, dataType);
    }
    catch(CException *pEx) {
        pEx->GetErrorMessage(this->errorMessage, sizeof(this->errorMessage));
        asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
            "%s:%s: exception = %s\n", 
            driverName, functionName, this->errorMessage);
        pEx->Delete();
        return(NULL);
    }
        
    return(pArray);
}