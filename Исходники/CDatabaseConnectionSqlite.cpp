///////////////////////////////////////////////////////////////
//
// InsertQueryArgumentsSqlite
//
// Insert arguments and apply Sqlite escapement
//
///////////////////////////////////////////////////////////////
SString InsertQueryArgumentsSqlite ( const SString& strQuery, CLuaArguments* pArgs )
{
    SString strParsedQuery;

    // Walk through the query and replace the variable placeholders with the actual variables
    unsigned int uiLen = strQuery.length ();
    unsigned int a = 0;
    for ( unsigned int i = 0 ; i < uiLen ; i++ )
    {
        if ( strQuery[i] != SQL_VARIABLE_PLACEHOLDER )
        {
            // If we found a normal character, copy it into the destination buffer
            strParsedQuery += strQuery[i];
        }
        else
        {
            // Use ?? for unquoted strings
            bool bUnquotedStrings = strQuery[i+1] == SQL_VARIABLE_PLACEHOLDER;
            if ( bUnquotedStrings )
                i++;

            // If the placeholder is found, replace it with the variable
            CLuaArgument* pArgument = (*pArgs)[a++];

            // Check the type of the argument and convert it to a string we can process
            uint type = pArgument ? pArgument->GetType () : LUA_TNONE;
            if ( type == LUA_TBOOLEAN )
            {
                strParsedQuery += ( pArgument->GetBoolean() ) ? "1" : "0";
            }
            else
            if ( type == LUA_TNUMBER )
            {
                double dNumber = pArgument->GetNumber ();
                if ( dNumber == floor ( dNumber ) )
                    strParsedQuery += SString ( "%" PRId64, (long long)dNumber );
                else
                    strParsedQuery += SString ( "%f", dNumber );
            }
            else
            if ( type == LUA_TSTRING )
            {
                // Copy the string into the query, and escape '
                if ( !bUnquotedStrings ) strParsedQuery += '\'';
                SqliteEscape ( strParsedQuery, pArgument->GetString ().c_str (), pArgument->GetString ().length () );
                if ( !bUnquotedStrings ) strParsedQuery += '\'';
            }
            else
            {
                // If we don't have any content, put just output 2 quotes to indicate an empty variable
                strParsedQuery += "\'\'";
            }
        }
    }

    return strParsedQuery;
}