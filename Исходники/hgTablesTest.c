int tableSize(char *db, char *table)
/* Return number of rows in table. */
{
struct sqlConnection *conn = sqlConnect(db);
int size = sqlTableSize(conn, table);
sqlDisconnect(&conn);
return size;
}