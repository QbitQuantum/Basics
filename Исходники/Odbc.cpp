std::string getOdbcError(unsigned int handletype, const SQLHANDLE& handle)
{
    
    std::ostringstream err;
    SQLCHAR sqlstate[6];
    SQLCHAR message[SQL_MAX_MESSAGE_LENGTH];
    SQLINTEGER NativeError;
    SQLSMALLINT i, MsgLen;
    SQLRETURN rc2;

    // Get the status records.
    i = 1;
    while ((rc2 = SQLGetDiagRecA(handletype, handle, i, sqlstate, &NativeError,
                                 message, sizeof(message), &MsgLen)) != SQL_NO_DATA && rc2 >= 0)
    {       
        err << "(" << i << ") " << "\nSQLState:" << (char*)&sqlstate[0];
        err << "\nNativeError: " << (long)NativeError;
        err << "\nMessage: " << &message[0];
        //err << "\nMsgLen: " + (long)MsgLen;

        i++;
    }

    return err.str();
}