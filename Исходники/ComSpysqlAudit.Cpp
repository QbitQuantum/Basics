STDMETHODIMP CComSpySqlAudit::Init(LPCWSTR pwszDSN, LPCWSTR pwszUser, LPCWSTR pwszPw)
{
    WCHAR wszBuffer[1024];
    SQLRETURN rc;

    if (m_henv || m_hstmt || m_hdbc)
        return E_UNEXPECTED; //did you call Init() twice?
    
    rc = SQLAllocEnv( &m_henv );
    if (!SQL_SUCCEEDED(rc))
    {
        ATLTRACE(L"CComSpySqlAudit::Init() - SQLAllocEnv failed with code %d\n", rc);
        goto Error;
    }
    

    //Allocate the Connection handle 
    rc = SQLAllocConnect( m_henv, &m_hdbc );
    if (!SQL_SUCCEEDED(rc))
    {         
        ATLTRACE(L"CComSpySqlAudit::Init() - SQLAllocConnect failed with code %d\n", rc);
        goto Error;        
    }
    

    SQLSetConnectOption(m_hdbc, SQL_LOGIN_TIMEOUT, 5);
    
    rc = SQLConnect( m_hdbc, SqlStringArg(pwszDSN), SQL_NTS,
                             SqlStringArg(pwszUser), SQL_NTS,
                             SqlStringArg(pwszPw), SQL_NTS);
    if (!SQL_SUCCEEDED(rc))
    {         
        ATLTRACE(L"CComSpySqlAudit::Init() - SQLConnect failed with code %d\n", rc);
        goto Error;
    }

    
    //Allocate the statement handle 
    rc = SQLAllocStmt( m_hdbc, &m_hstmt);
    if (!SQL_SUCCEEDED(rc))
    {         
        ATLTRACE(L"CComSpySqlAudit::Init() - SQLAllocStmt failed with code %d\n", rc);
        goto Error;
    }
    //
    //    verify the table existence
    //
    {    
        for (int i=0; i < ARRAYSIZE(pwszTables); i++)
        {
            HRESULT hrString = StringCchPrintfEx(
                wszBuffer, ARRAYSIZE(wszBuffer),
                NULL, NULL, STRSAFE_NO_TRUNCATION,
                L"CREATE TABLE dbo.%s (Ct int NOT NULL )", pwszTables[i]);
            _ASSERTE(SUCCEEDED(hrString));

            rc = SQLExecDirect(m_hstmt, SqlStringArg(wszBuffer), SQL_NTS);
            if (SQL_SUCCEEDED(rc))
            {
                // this means the table is not in the db

                //Clean up the table just created and exit 
                hrString = StringCchPrintfEx(wszBuffer, ARRAYSIZE(wszBuffer),
                    NULL, NULL, STRSAFE_NO_TRUNCATION,
                    L"drop table %s", pwszTables[i]);
                _ASSERTE(SUCCEEDED(hrString));

                rc = SQLExecDirect(m_hstmt, SqlStringArg(wszBuffer), SQL_NTS);
                ATLTRACE(L"Table %s is not in the Database.\n", pwszTables[i]);
                goto Error;
            }
        }    
    }
        
    return S_OK;

Error:
    if (m_hstmt)
    {
        SQLFreeStmt( m_hstmt, SQL_DROP );    
    }

    if (m_hdbc)
    {
       rc = SQLDisconnect( m_hdbc);
       SQLFreeConnect( m_hdbc);
       if (m_henv)
         SQLFreeEnv( m_henv );
    }

    m_hdbc = m_hstmt  = m_henv = NULL;
    
    return E_FAIL;    
    
}