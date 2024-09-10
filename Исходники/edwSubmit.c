void doValidatedEmail(struct edwSubmit *submit, boolean isComplete)
/* Send an email with info on all validated files */
{
struct sqlConnection *conn = edwConnect();
struct edwUser *user = edwUserFromId(conn, submit->userId);
struct dyString *message = dyStringNew(0);
/* Is this submission has no new file at all */
if ((submit->oldFiles != 0) && (submit->newFiles == 0) &&
    (submit->metaChangeCount == 0)  && isEmpty(submit->errorMessage)
     && (submit->fileIdInTransit == 0))
    {
    dyStringPrintf(message, "Your submission from %s is completed, but validation was not performed for this submission since all files in validate.txt have been previously submitted and validated.\n", submit->url);
    mailViaPipe(user->email, "EDW Validation Results", message->string, edwDaemonEmail);
    sqlDisconnect(&conn);
    dyStringFree(&message);
    return;
    }

if (isComplete)
    dyStringPrintf(message, "Your submission from %s is completely validated\n", submit->url);
else
    dyStringPrintf(message, 
	"Your submission hasn't validated after 24 hours, something is probably wrong\n"
	"at %s\n", submit->url);
dyStringPrintf(message, "\n#accession\tsubmitted_file_name\tnotes\n");
char query[512];
sqlSafef(query, sizeof(query),
    "select licensePlate,submitFileName "
    " from edwFile left join edwValidFile on edwFile.id = edwValidFile.fileId "
    " where edwFile.submitId = %u and edwFile.id != %u"
    , submit->id, submit->submitFileId);
struct sqlResult *sr = sqlGetResult(conn, query);
char **row;

while ((row = sqlNextRow(sr)) != NULL)
    {
    char *licensePlate = row[0];
    char *submitFileName = row[1];
    dyStringPrintf(message, "%s\t%s\t", naForNull(licensePlate), submitFileName);
    if (licensePlate == NULL)
        {
	dyStringPrintf(message, "Not validating");
	}
    dyStringPrintf(message, "\n");
    }
sqlFreeResult(&sr);

mailViaPipe(user->email, "EDW Validation Results", message->string, edwDaemonEmail);
sqlDisconnect(&conn);
dyStringFree(&message);
}