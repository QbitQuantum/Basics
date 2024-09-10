SQLRETURN SQLSetCursorNameA( SQLHSTMT statement_handle,
           SQLCHAR *cursor_name,
           SQLSMALLINT name_length )
{
    return SQLSetCursorName( statement_handle,
           cursor_name,
           name_length );
}