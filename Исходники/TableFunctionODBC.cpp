StoragePtr TableFunctionODBC::executeImpl(const ASTPtr & ast_function, const Context & context) const
{
    const ASTFunction & args_func = typeid_cast<const ASTFunction &>(*ast_function);

    if (!args_func.arguments)
        throw Exception("Table function 'odbc' must have arguments.", ErrorCodes::LOGICAL_ERROR);

    ASTs & args = typeid_cast<ASTExpressionList &>(*args_func.arguments).children;

    if (args.size() != 2)
        throw Exception("Table function 'odbc' requires exactly 2 arguments: ODBC connection string and table name.",
            ErrorCodes::NUMBER_OF_ARGUMENTS_DOESNT_MATCH);

    for (int i = 0; i < 2; ++i)
        args[i] = evaluateConstantExpressionOrIdentifierAsLiteral(args[i], context);

    std::string connection_string = static_cast<const ASTLiteral &>(*args[0]).value.safeGet<String>();
    std::string table_name = static_cast<const ASTLiteral &>(*args[1]).value.safeGet<String>();

    Poco::Data::ODBC::SessionImpl session(connection_string, DBMS_DEFAULT_CONNECT_TIMEOUT_SEC);
    SQLHDBC hdbc = session.dbc().handle();

    SQLHSTMT hstmt = nullptr;

    if (Poco::Data::ODBC::Utility::isError(SQLAllocStmt(hdbc, &hstmt)))
        throw Poco::Data::ODBC::ODBCException("Could not allocate connection handle.");

    SCOPE_EXIT(SQLFreeStmt(hstmt, SQL_DROP));

    /// TODO Why not do SQLColumns instead?
    std::string query = "SELECT * FROM " + table_name + " WHERE 1 = 0";
    if (Poco::Data::ODBC::Utility::isError(Poco::Data::ODBC::SQLPrepare(hstmt, reinterpret_cast<SQLCHAR *>(&query[0]), query.size())))
        throw Poco::Data::ODBC::DescriptorException(session.dbc());

    if (Poco::Data::ODBC::Utility::isError(SQLExecute(hstmt)))
        throw Poco::Data::ODBC::StatementException(hstmt);

    SQLSMALLINT cols = 0;
    if (Poco::Data::ODBC::Utility::isError(SQLNumResultCols(hstmt, &cols)))
        throw Poco::Data::ODBC::StatementException(hstmt);

    /// TODO cols not checked

    NamesAndTypesList columns;
    for (SQLSMALLINT ncol = 1; ncol <= cols; ++ncol)
    {
        SQLSMALLINT type = 0;
        /// TODO Why 301?
        SQLCHAR column_name[301];
        /// TODO Result is not checked.
        Poco::Data::ODBC::SQLDescribeCol(hstmt, ncol, column_name, sizeof(column_name), NULL, &type, NULL, NULL, NULL);
        columns.emplace_back(reinterpret_cast<char *>(column_name), getDataType(type));
    }

    auto result = StorageODBC::create(table_name, connection_string, "", table_name, ColumnsDescription{columns});
    result->startup();
    return result;
}