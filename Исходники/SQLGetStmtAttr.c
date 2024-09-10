SQLRETURN SQL_API
SQLGetStmtAttrA(SQLHSTMT StatementHandle,
                SQLINTEGER Attribute,
                SQLPOINTER ValuePtr,
                SQLINTEGER BufferLength,
                SQLINTEGER *StringLengthPtr)
{
    return SQLGetStmtAttr(StatementHandle,
                          Attribute,
                          ValuePtr,
                          BufferLength,
                          StringLengthPtr);
}