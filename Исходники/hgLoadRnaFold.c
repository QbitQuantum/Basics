void hgLoadRnaFold(char *database, char *table, char *foldDir)
/* hgLoadRnaFold - Load a directory full of RNA fold files into database. */
{
char path[PATH_LEN];
struct slName *dirList, *dirEl;
struct lineFile *lf;
char *line, *word, *s, c;
FILE *f = hgCreateTabFile(tabDir, table);
int count = 0;

dirList = listDir(foldDir, "*");
for (dirEl = dirList; dirEl != NULL; dirEl = dirEl->next)
    {
    char *name = dirEl->name;
    if (sameString(name, "CVS"))
        continue;
    safef(path, sizeof(path), "%s/%s", foldDir, name);
    lf = lineFileOpen(path, TRUE);
    if (!lineFileNext(lf, &line, NULL))
        {
	if (warnEmpty)
	    {
	    warn("%s is empty, skipping\n", name);
	    lineFileClose(&lf);
	    continue;
	    }
	else
	    errAbort("%s is empty\n", name);
	}
    if (!isupper(line[0]))
	notFold(path, 1);
    fprintf(f, "%s\t", name);	/* Save name */
    fprintf(f, "%s\t", line);	/* Save sequence */
    lineFileNeedNext(lf, &line, NULL);
    c = line[0];
    if (c != '.' && c != '(')
        notFold(path, 2);
    word = nextWord(&line);
    fprintf(f, "%s\t", word);	/* Save nested parenthesis */

    /* Parse out (energy) term at end of line. */
    s = strchr(line, '(');
    if (s == NULL)
        notFold(path, 3);
    word = skipLeadingSpaces(s+1);
    if (word == NULL || (!word[0] == '-' && !isdigit(word[0])))
        notFold(path, 4);
    if ((s = strchr(word, ')')) == NULL)
        notFold(path, 5);
    *s = 0;
    fprintf(f, "%s\n", word);
    
    lineFileClose(&lf);
    ++count;
    }
printf("Parsed %d files\n", count);
if (doLoad)
    {
    struct sqlConnection *conn = sqlConnect(database);
    rnaFoldCreateTable(conn, table);
    hgLoadTabFile(conn, tabDir, table, &f);
    hgRemoveTabFile(tabDir, table);
    sqlDisconnect(&conn);
    }
}