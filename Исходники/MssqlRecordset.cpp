bool CMssqlRecordset::Init(CMssqlConnection *parent, HSTMT hStmt, const char *command)
{
    m_bEof = false;
    m_parent = parent;
    m_hStmt = hStmt;

    m_parent->m_lasterror=SQLExecDirect(m_hStmt,(SQLWCHAR*)(const wchar_t *)cvs::wide(command),SQL_NTS);
    CServerIo::trace(1,"MSSQL Execute Done");

    if((!SQL_SUCCEEDED(m_parent->m_lasterror))&&(m_parent->m_lasterror!=SQL_NEED_DATA))
    {
        GetStmtError();
        return false;
    }

    if(m_parent->m_lasterror==SQL_NEED_DATA)
    {
        SQLPOINTER pParmID;
        SQLRETURN retcode=SQL_SUCCESS, putret;
        char *dataptr, *dataput;
        SQLINTEGER dataoff, datasiz;
        SQLINTEGER chunk=1024;

        CServerIo::trace(1,"MSSQL Execute requires more data");
        retcode = SQLParamData(m_hStmt, &pParmID);
        if (retcode == SQL_NEED_DATA)
        {
            for(std::map<int,CSqlVariant>::iterator i = parent->m_bindVars.begin(); i!=parent->m_bindVars.end(); ++i)
            {
                switch(i->second.type())
                {
                case CSqlVariant::vtString:
                    if (parent->m_sqlv[i->first].ws.length()+1<256)
                        CServerIo::trace(1,"MSSQL Execute this parameter is too small to be a BLOB");
                    else
                    {
                        //dataput = (char *)((const char *)parent->m_sqlv[i->first].cs.c_str());
                        //dataoff=0; datasiz = (SQLINTEGER)(parent->m_sqlv[i->first].cs.size()+1);
                        dataput = (char *)((const char *)parent->m_sqlv[i->first].ws.c_str());
                        dataoff=0;
                        datasiz = (SQLINTEGER)(parent->m_sqlv[i->first].ws.size()+1);

                        //CServerIo::trace(1,"MSSQL Needs data - so put the data %d, size %d",(int)i->first,(int)parent->m_sqlv[i->first].cs.size()+1);
                        CServerIo::trace(1,"MSSQL Needs data - so put the data %d, size %d",(int)i->first,(int)parent->m_sqlv[i->first].ws.size()+1);
                        for (dataptr=dataput; dataoff<datasiz; dataoff+=chunk)
                        {
                            CServerIo::trace(1,"MSSQL put data %d offset %d bytes N\"%0.25s...%0.25s\"",dataoff,
                                             (dataoff+chunk>datasiz)?datasiz-dataoff:chunk,
                                             (const char *)cvs::narrow((const wchar_t *)(dataptr+dataoff)),
                                             ((const char *)cvs::narrow((const wchar_t *)(dataptr+dataoff))+(((dataoff+chunk>datasiz)?datasiz-dataoff:chunk)+1-25)));
                            putret=SQLPutData(m_hStmt, (SQLPOINTER)(dataptr+(sizeof(wchar_t)*dataoff)), (dataoff+chunk>datasiz)?(sizeof(wchar_t)*(datasiz-dataoff)):(sizeof(wchar_t)*chunk));
                            if(!SQL_SUCCEEDED(putret))
                            {
                                m_parent->m_lasterror = putret;
                                GetStmtError();
                                return false;
                            }
                            /*switch (putret)
                            {
                            case SQL_SUCCESS:
                            	CServerIo::trace(1,"SQL Put Data returned SQL_SUCCESS");
                            	break;
                            case SQL_SUCCESS_WITH_INFO:
                            	CServerIo::trace(1,"SQL Put Data returned SQL_SUCCESS_WITH_INFO");
                            	break;
                            case SQL_STILL_EXECUTING:
                            	CServerIo::trace(1,"SQL Put Data returned SQL_STILL_EXECUTING");
                            	break;
                            case SQL_ERROR:
                            	CServerIo::trace(1,"SQL Put Data returned SQL_ERROR");
                            	break;
                            case SQL_INVALID_HANDLE:
                            	CServerIo::trace(1,"SQL Put Data returned SQL_INVALID_HANDLE");
                            	break;
                            default:
                            	CServerIo::trace(1,"SQL Put Data returned some other error.");
                            }*/
                        }
                        CServerIo::trace(1,"MSSQL call ParamData again");
                        retcode = SQLParamData(m_hStmt, &pParmID);
                        if (retcode==SQL_SUCCESS)
                            CServerIo::trace(1,"MSSQL call ParamData returned OK - no more data");
                        else if (retcode==SQL_NEED_DATA)
                            CServerIo::trace(1,"MSSQL call ParamData returned need more data");
                    }
                    break;
                default:
                    break;
                }
            }
        } else {
            retcode=SQL_SUCCESS;
        }
        if (retcode==SQL_SUCCESS)
            CServerIo::trace(1,"MSSQL call ParamData returned OK - no more data");
        else if (retcode==SQL_NEED_DATA)
            CServerIo::trace(1,"MSSQL call ParamData returned need more data");
        else if(!SQL_SUCCEEDED(retcode))
        {
            CServerIo::trace(1,"MSSQL call ParamData returned some sort of failure so returning...");
            m_parent->m_lasterror = retcode;
            GetStmtError();
            return false;
        }
    }

    CServerIo::trace(1,"MSSQL Execute all complete now get the Number of Result Columns");
    if(!SQL_SUCCEEDED(m_parent->m_lasterror = SQLNumResultCols(m_hStmt,&m_num_fields)))
    {
        GetStmtError();
        return false;
    }

    m_sqlfields.resize(m_num_fields);
    for(SQLSMALLINT n=0; n<m_num_fields; n++)
    {
        SQLRETURN rc;

        SQLWCHAR szCol[128];
        SQLSMALLINT len = sizeof(szCol);
        rc = m_parent->m_lasterror = SQLDescribeCol(hStmt,n+1,szCol,sizeof(szCol),&len,&m_sqlfields[n].type,&m_sqlfields[n].size,&m_sqlfields[n].decimal,&m_sqlfields[n].null);
        if(!SQL_SUCCEEDED(rc))
        {
            GetStmtError();
            return false;
        }
        szCol[len]='\0';
        m_sqlfields[n].field = n;
        m_sqlfields[n].hStmt = m_hStmt;
        m_sqlfields[n].name = szCol;

        SQLINTEGER fldlen = 0;
        SQLSMALLINT ctype;
        switch(m_sqlfields[n].type)
        {
        case SQL_UNKNOWN_TYPE:
            CServerIo::trace(1,"Unable to bind column %s as it is SQL_UNKNOWN_TYPE",(const char *)szCol);
            break; // Don't bind
        case SQL_CHAR:
        case SQL_VARCHAR:
            ctype = SQL_C_WCHAR;
            fldlen = m_sqlfields[n].size;
            break;
        case SQL_DECIMAL:
            ctype = SQL_C_WCHAR;
            fldlen = m_sqlfields[n].size + m_sqlfields[n].decimal + 1;
            break;
        case SQL_NUMERIC:
        case SQL_INTEGER:
        case SQL_SMALLINT:
            ctype = SQL_C_LONG;
            fldlen = sizeof(long);
            break;
        case SQL_FLOAT:
        case SQL_REAL:
        case SQL_DOUBLE:
            ctype = SQL_C_DOUBLE;
            fldlen = sizeof(double);
            break;
        case SQL_DATETIME:
            ctype = SQL_C_WCHAR;
            fldlen = 64;
            break;
        }
        m_sqlfields[n].ctype = ctype;
        m_sqlfields[n].fldlen = fldlen;
        if(m_sqlfields[n].fldlen)
        {
            m_sqlfields[n].data = malloc(m_sqlfields[n].fldlen);
            if(!SQL_SUCCEEDED(m_parent->m_lasterror = SQLBindCol(m_hStmt,n+1,m_sqlfields[n].ctype,m_sqlfields[n].data,m_sqlfields[n].fldlen,&m_sqlfields[n].datalen)))
            {
                GetStmtError();
                CServerIo::trace(1,"Unable to bind column %s due to error",(const char*)szCol);
                return false;
            }
        }
    }

    if(m_num_fields)
    {
        if(!Next() && !m_bEof)
            return false;
    }

    return true;
}