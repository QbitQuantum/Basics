void expRestoreTable(char *file)
/* Fill empty table with experiments in .ra file with id's */
{
struct hash *ra = NULL;
struct lineFile *lf = lineFileOpen(file, TRUE);
struct encodeExp *exp;
int ix = 1;
int expId;
char *accession;
char *key;

verbose(1, "Restoring experiments from file \'%s\' to table \'%s\'\n", file, table);
if (sqlRowCount(connExp, sqlCheckIdentifier(table)) != 0)
    errAbort("ERROR: table for restore must exist and be empty");

while ((ra = raNextRecord(lf)) != NULL)
    {
    exp = encodeExpFromRa(ra);

    /* save accession and id as we may stomp on these for to-delete experiments */
    accession = cloneString(exp->lab);
    expId = exp->ix;

    key = encodeExpKey(exp);
    while (ix < expId)
        {
        exp->accession = "DELETED";
        exp->ix = ix;
        verbose(3, "Adding row for deleted experiment %d\n", ix);
        encodeExpAdd(connExp, table, exp);
        ix++;
        }
    /* restore accession and id */
    exp->accession = accession;
    exp->ix = expId;
    encodeExpAdd(connExp, table, exp);
    verbose(3, "Adding row for experiment %d: %s\n", ix, key);
    ix++;
    }
verbose(1, "To complete restore, delete rows where accession=DELETED\n");
}