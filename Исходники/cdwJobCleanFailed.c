void cdwJobCleanFailed(int submitId)
/* Check out the symlink to determine its type. */
{

struct sqlConnection *conn = sqlConnect("cdw");

struct dyString *query = dyStringNew(0);
sqlDyStringPrintf(query, 
 "select id, commandLine, startTime, endTime, returnCode, pid from cdwJob where submitId=%d "
"order by commandLine,CAST(returnCode AS unsigned)", 
 submitId);
 // NOTE we need this CAST on returnCode since it can be -1. we want success 0 first.

// TODO DO we need to add any other conditions such as distinguishing
// between running, queued, and done?

/* Scan through result set finding redundant rows beyond success row. */
struct sqlResult *sr = sqlGetResult(conn, query->string);
char **row;
char *lastCommand = "";
boolean success = FALSE;
struct slInt *list = NULL;
struct slInt *e;
while ((row = sqlNextRow(sr)) != NULL)
    {
    unsigned int id = sqlUnsigned(row[0]);
    char *commandLine = row[1];
    unsigned long startTime = sqlUnsignedLong(row[2]);
    unsigned long endTime = sqlUnsignedLong(row[3]);
    int returnCode = sqlSigned(row[4]);
    unsigned int pid = sqlUnsigned(row[5]);
    verbose(2, "%u\t%s\t%lu\t%lu\t%d\t%u\t%u\n", id, commandLine, startTime, endTime, returnCode, pid, submitId);
    if (sameString(lastCommand, commandLine))
	{
	if (success)  // we already succeeded, the old failure is unwanted baggage.
	    {
	    e = slIntNew(id);  // or add it to a list of rows whose ids should get removed
	    slAddHead(&list, e);
	    }
	}
    else
	{
	if (returnCode == 0)
	    success = TRUE;
	else
	    success = FALSE;
	}
    // note fields pid and submitId are defined as signed integers in cdwJob table, probably should be unsigned.
    lastCommand = cloneString(commandLine);
    }
                                                                              
sqlFreeResult(&sr);

slReverse(&list);
for(e=list;e;e=e->next)
    {
    dyStringClear(query);
    sqlDyStringPrintf(query, "delete from cdwJob where id=%u", (unsigned int) e->val);
    //printf("%s\n", query->string);
    sqlUpdate(conn, query->string);
    }

/* Clean up and go home */
dyStringFree(&query);

sqlDisconnect(&conn);


}