static BOOL kpc_bindparameter(ATOMID idfName, WORD h, LPFETCH lpFetch,
                              int nParam, ATOMID idMode, 
                              WORD wType, OBJECTID idObj, ATOMID idSlot,
                              BOOL bLive)
{
    WORD wMode;
    WORD sqlType = SQL_LONGVARCHAR, scale = 0, nullable = SQL_NO_NULLS;
    DWORD colDef = RET_BUFFER_LEN - 1;
    LPPARAM lpParams, lpParam;
    LPDESC lpDesc;
    WORD wNumParams = 0;
    DWORD dwLen;
    RETCODE code;
    
    if (idMode == Symbol(INPUT))
        wMode = SQL_PARAM_INPUT;
    else if (idMode == Symbol(OUTPUT))
        wMode = SQL_PARAM_OUTPUT;
    else if (idMode == Symbol(INPUT_OUTPUT))
        wMode = SQL_PARAM_INPUT_OUTPUT;
    
    code = SQLDescribeParam(lpFetch->hstmt, nParam,
                            &sqlType, &colDef, &scale, &nullable);
    
    switch (code) {
      case SQL_SUCCESS:
      case SQL_SUCCESS_WITH_INFO:
          break;
      case SQL_INVALID_HANDLE:
          return KPC_HANDLE_ERROR(IDE_INVALID_HANDLE, h);
      default:
          sql_error(idfName, SQL_NULL_HDBC, lpFetch->hstmt);
          if (!stricmp(sqlstate, "IM001"))
          {
              if (nParam < 1)
                  return KPC_ERROR(IDE_OUTOF_RANGE, KppAddAtomInt(nParam));
              if (!num_params(idfName, h, lpFetch->hstmt, &wNumParams))
                  return ERROR;
              if (nParam > wNumParams)
                  return KPC_ERROR(IDE_OUTOF_RANGE, KppAddAtomInt(nParam));
              
              sqlType = SQL_LONGVARCHAR;
              colDef = RET_BUFFER_LEN - 1;
              nullable = SQL_NO_NULLS;
          }
          else
              return ERROR;
    }

    if (!lpFetch->params)
    {
        if (!wNumParams && 
            !num_params(idfName, h, lpFetch->hstmt, &wNumParams))
            return ERROR;

        lpParams = calloc(sizeof(PARAM), wNumParams);
        if (!lpParams)
            return KPC_ERROR(IDE_OUTOF_MEMORY, NULLID);
    }
    else
        lpParams = lpFetch->params;
    
    lpParam = lpParams + nParam - 1;
    lpDesc = &lpParam->desc;
    lpDesc->sqlType = sqlType;
    lpDesc->colDef = colDef;
    lpDesc->scale = scale;
    lpDesc->nullable = nullable;

    if (lpFetch->wXParamRows)
    {
        lpDesc->pdwLen = calloc(sizeof(DWORD), lpFetch->wXParamRows + 1);
        if (!lpDesc->pdwLen)
            return KPC_ERROR(IDE_OUTOF_MEMORY, NULLID);
    }
    else
        lpDesc->pdwLen = &lpDesc->dwLen;
                  
    if (!fill_bind(idfName, lpDesc, &lpParam->data, 
                   lpFetch->wXParamRows, &dwLen))
    {
        free_params(lpParams, lpFetch->wNumParams);
        return ERROR;
    }
    else
    {
        lpParam->wMode = wMode;
        lpParam->wType = wType;
        lpParam->idObj = idObj;
        lpParam->idSlot = idSlot;
        lpDesc->colDef = dwLen;
        lpFetch->wNumParams = wNumParams;
        lpFetch->params = lpParams;
        
        if (bLive)
        {
            int i = -1;
            
            while (++i <= lpFetch->wXParamRows)
                lpDesc->pdwLen[i] = SQL_LEN_DATA_AT_EXEC(0);
        }
        else if (!set_parameter_value(idfName, lpParam, lpFetch->wXParamRows))
            return ERROR;
    }
    
    code = SQLBindParameter(lpFetch->hstmt, nParam, wMode, 
                            lpDesc->cType, lpDesc->sqlType,
                            lpDesc->colDef, lpDesc->scale,
                            lpDesc->address, dwLen, lpDesc->pdwLen);
    
    switch (code) {
      case SQL_SUCCESS:
      case SQL_SUCCESS_WITH_INFO:
          lpParam->bound = TRUE;
          return TRUE;
      case SQL_INVALID_HANDLE:
          return KPC_HANDLE_ERROR(IDE_INVALID_HANDLE, h);
      default:
          return sql_error(idfName, SQL_NULL_HDBC, lpFetch->hstmt);
    }          
}