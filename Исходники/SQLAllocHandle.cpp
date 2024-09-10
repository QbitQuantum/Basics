    SQLRETURN UncaughtOdbcEntry()
    {
        SQLRETURN error = SQL_ERROR;
        ENV* env;
        DBC* dbc;
    
        switch (mHandleType)
        {
            case SQL_HANDLE_ENV:
                error = rets_SQLAllocEnv(mOutputHandlePtr);
                break;

            case SQL_HANDLE_DBC:
                env = static_cast<ENV*>(mInputHandle);
                error = env->SQLAllocConnect(mOutputHandlePtr);
                break;

            case SQL_HANDLE_STMT:
                dbc = static_cast<DBC*>(mInputHandle);
                error = dbc->SQLAllocStmt(mOutputHandlePtr);
                break;

            default:
                return SQL_ERROR;
        }

        return error;
    }