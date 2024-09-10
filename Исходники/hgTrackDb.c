void hgTrackDb(char *org, char *database, char *trackDbName, char *sqlFile, char *hgRoot,
               boolean strict)
/* hgTrackDb - Create trackDb table from text files. */
{
struct trackDb *td;
char tab[PATH_LEN];
safef(tab, sizeof(tab), "%s.tab", trackDbName);

struct trackDb *tdbList = buildTrackDb(org, database, hgRoot, strict);
tdbList = flatten(tdbList);
slSort(&tdbList, trackDbCmp);
verbose(1, "Loaded %d track descriptions total\n", slCount(tdbList));

/* Write to tab-separated file; hold off on html, since it must be encoded */
    {
    verbose(2, "Starting write of tabs to %s\n", tab);
    FILE *f = mustOpen(tab, "w");
    for (td = tdbList; td != NULL; td = td->next)
        {
        hVarSubstTrackDb(td, database);
        char *hold = td->html;
        td->html = "";
	subChar(td->type, '\t', ' ');	/* Tabs confuse things. */
	subChar(td->shortLabel, '\t', ' ');	/* Tabs confuse things. */
	subChar(td->longLabel, '\t', ' ');	/* Tabs confuse things. */
	trackDbTabOut(td, f);
        td->html = hold;
        }
    carefulClose(&f);
    verbose(2, "Wrote tab representation to %s\n", tab);
    }

/* Update database */
    {
    char *create, *end;
    char query[256];
    struct sqlConnection *conn = sqlConnect(database);

    /* Load in table definition. */
    readInGulp(sqlFile, &create, NULL);
    create = trimSpaces(create);
    create = substituteTrackName(create, trackDbName);
    end = create + strlen(create)-1;
    if (*end == ';') *end = 0;
    sqlRemakeTable(conn, trackDbName, create);

    /* Load in regular fields. */
    sqlSafef(query, sizeof(query), "load data local infile '%s' into table %s", tab, trackDbName);
    verbose(2, "sending mysql \"%s\"\n", query);
    sqlUpdate(conn, query);
    verbose(2, "done tab file load");

    /* Load in html and settings fields. */
    for (td = tdbList; td != NULL; td = td->next)
	{
        if (isEmpty(td->html))
	    {
	    if (strict && !trackDbLocalSetting(td, "parent") && !trackDbLocalSetting(td, "superTrack") &&
	        !sameString(td->track,"cytoBandIdeo"))
		{
		fprintf(stderr, "Warning: html missing for %s %s %s '%s'\n",org, database, td->track, td->shortLabel);
		}
	    }
	else
	    {
	    updateBigTextField(conn,  trackDbName, "tableName", td->track, "html", td->html);
	    }
	if (td->settingsHash != NULL)
	    {
	    char *settings = settingsFromHash(td->settingsHash);
	    updateBigTextField(conn, trackDbName, "tableName", td->track,
	        "settings", settings);
	    if (showSettings)
		{
		verbose(1, "%s: type='%s';", td->track, td->type);
		if (isNotEmpty(settings))
		    {
		    char *oneLine = replaceChars(settings, "\n", "; ");
		    eraseTrailingSpaces(oneLine);
		    verbose(1, " %s", oneLine);
		    freeMem(oneLine);
		    }
		verbose(1, "\n");
		}
	    freeMem(settings);
	    }
	}

    sqlDisconnect(&conn);
    verbose(1, "Loaded database %s\n", database);
    }
}