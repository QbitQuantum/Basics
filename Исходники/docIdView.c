void doLabContacts(struct cart *theCart)
{
char *subId = cartString(theCart, "lab");
cartWebStart(cart, database, "ENCODE DCC:  Contacts for submission: %s",subId);
struct sqlConnection *conn = sqlConnect(database);
char query[10 * 1024];
struct sqlResult *sr;
char **row;

printf("<a href=docIdView?db=%s> Return </a><BR>", database);
safef(query, sizeof query, "select user_id from %s where id = %s ", "projects",subId);
char *userId = sqlQuickString(conn, query);

safef(query, sizeof query, "select name,email,pi from %s where id = '%s' ", "users",userId);
sr = sqlGetResult(conn, query);
printf("<pre>");
while ((row = sqlNextRow(sr)) != NULL)
    {
    printf("Name:  %s\nEmail: %s\nPI:    %s", row[0], row[1], row[2]);
    }

sqlFreeResult(&sr);
sqlDisconnect(&conn);
cartWebEnd();
}