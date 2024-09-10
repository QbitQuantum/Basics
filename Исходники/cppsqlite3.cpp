int CppSQLite3DB::updateBlob(const CString& szTableName, const CString& szFieldName, const unsigned char* data, int dataLength, const CString& szWhere)
{

    CString sql = CString("update ") + szTableName + " set " + szFieldName + "=? where " + szWhere;

    CppSQLite3Statement statement = compileStatement(sql);
    statement.bind(1, data, dataLength);

    return statement.execDML();
}