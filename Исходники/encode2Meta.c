struct mdbObj *getMdbList(char *database)
/* Get list of metaDb objects for a database. */
{
struct sqlConnection *conn = sqlConnect(database);
struct mdbObj *list = mdbObjsQueryAll(conn, metaTable);
sqlDisconnect(&conn);
return list;
}