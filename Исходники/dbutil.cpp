int DBUtil::QueryForInt(const char* sql, ...)
{
    SQL_INST* sqlinst = (SQL_INST*)dbHandle_;
    if(sqlinst == 0) {
        radlog(L_CONS|L_ERROR, "[DBUtil::QueryForInt] invalid instance");
        return -1;
    }

    char sqlbuf[4096];
    va_list args;
    va_start(args, sql);
    vsNprintf(sqlbuf, sizeof(sqlbuf), sql, args);
    va_end(args);

    Row row;
    int result = SelectFirstRowInternal(sqlinst, sqlbuf, row);
    if(result <= 0)
        return 0;
    else
        return atoi(row[0].c_str());
}