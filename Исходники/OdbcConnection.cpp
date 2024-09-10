    bool OdbcConnection::TryReadNextResult()
    {
        if (executionState == FetchRow)
        {

            SQLRETURN ret = SQLMoreResults(statement);
            if (ret == SQL_STILL_EXECUTING) 
            { 
                return false; 
            }
            if (ret == SQL_NO_DATA) 
            { 
                resultset->moreRows = false;
                statement.Free();
                executionState = Idle;
                return true;
            }
            else 
            {
                resultset->moreRows = true;
            }
            if (!SQL_SUCCEEDED(ret)) 
            { 
                statement.Throw();
            }

            executionState = CountingColumns;
        }

        return TryExecute(L"");
    }