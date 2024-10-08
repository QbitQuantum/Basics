static int
doit(gzFile *infp)
{
	int		i, skip = 0;
	time_t		curtime, ll_time;
	char		*user, node[TBDB_FLEN_NODEID * 2], prog[128];
	char		buf[BUFSIZ], *bp, uid_idx[128], tmp[BUFSIZ];
	struct tm	tm;
	MYSQL_RES	*dbres;
	MYSQL_ROW	dbrow;
	
	while (1) {
		if (gzgets(infp, buf, BUFSIZ) == NULL)
			break;

		/*
		 * If the line does not contain a newline, then we skip it
		 * and try to sync up again. We consider ourselves synced
		 * when the buffer contains a newline in it.
		 */
		if (buf[strlen(buf) - 1] != '\n') {
			skip = 1;
			continue;
		}
		if (skip) {
			skip = 0;
			continue;
 		}

		/*
		 * Thank dog for strptime! Convert the syslog timestamp
		 * into a tm, and then into regular unix time.
		 */
		time(&curtime);
		localtime_r(&curtime, &tm);
		if ((bp = strptime(buf, "%b %e %T", &tm)) == NULL) {
			continue;
		}
		ll_time = mktime(&tm);

		/*
		 * If the constructed time is in the future, then we have
		 * year off by one (cause we are possibly looking at files
		 * created in the previous year). Set the year back by one,
		 * and redo.
		 */
		if (ll_time > curtime) {
			tm.tm_year--;
			ll_time = mktime(&tm);
		}

		/*
		 * Scanf the next part, which looks like:
		 *
		 *	node progname[pid]:
		 *
		 * Ensure we match the proper number of items.
		 */
		bzero(node, sizeof(node));
		if ((sscanf(bp, "%s %s:", node, prog) != 2))
			continue;

		/*
		 * Only sshd matters to us.
		 */
		if (strncmp(prog, SSHD, strlen(SSHD)))
			continue;

		/*
		 * Okay, these kinds of strings matter.
		 *
		 *	FreeBSD:	"Accepted rsa for USER" 
		 *	Linux 6.2:	"log: RSA authentication for USER"
		 *	Linux 7.1:	"session opened for user USER"
		 *      (several ssh2): "Accepted publickey for USER"
		 *      (several ssh2): "Accepted password for USER"
		 *      (several ssh2): "Accepted keyboard-interactive for USER"
		 */
#define L1	"Accepted rsa for "
#define L2	"session opened for user "
#define L3	"log: RSA authentication for "
#define L4	"Accepted publickey for "
#define L5	"Accepted password for "
#define L6	"Accepted keyboard-interactive for "
		
		/* Skip to end of program[pid]: and trailing space */
		bp = strchr(bp, ':');
		bp += 2;

		if (strncmp(bp, L1, strlen(L1)) == 0) {
		  /*fprintf(stdout,"Hit L1: ");*/
			bp += strlen(L1);
		}
		else if (strncmp(bp, L2, strlen(L2)) == 0) {
		  /*fprintf(stdout,"Hit L2: ");*/
			bp += strlen(L2);
		}
		else if (strncmp(bp, L3, strlen(L3)) == 0) {
		  /*fprintf(stdout,"Hit L3: ");*/
			bp += strlen(L3);
		}
		else if (strncmp(bp, L4, strlen(L4)) == 0) {
		  /*fprintf(stdout,"Hit L4: ");*/
			bp += strlen(L4);
		}
		else if (strncmp(bp, L5, strlen(L5)) == 0) {
		  /*fprintf(stdout,"Hit L5: ");*/
			bp += strlen(L5);
		}
		else if (strncmp(bp, L6, strlen(L6)) == 0) {
		  /*fprintf(stdout,"Hit L6: ");*/
			bp += strlen(L6);
		}
		else {
			continue;
		}

		/*
		 * The login name is the next token.
		 */
		if (! (user = strsep(&bp, " ")))
			continue;
		/*fprintf(stdout,"%s on %s\n",user,node);*/

		/* We do not care about ROOT logins. */
		if (strcasecmp(user, "ROOT") == 0)
			continue;

		dbres = mydb_query("select uid_idx from users where uid='%s' "
				   "and status!='archived' and status!='nonlocal'",
				   1, user);

		if (!dbres) {
			syslog(LOG_ERR, "DB error getting user %s", user);
			continue;
		}

		if (!mysql_num_rows(dbres)) {
			syslog(LOG_INFO, "No DB record for user %s", user);
			mysql_free_result(dbres);
			continue;
		}
		dbrow = mysql_fetch_row(dbres);
		strncpy(uid_idx, dbrow[0], sizeof(uid_idx));
		mysql_free_result(dbres);

		/*
		 * Safety first. 
		 */
		mydb_escape_string(tmp, uid_idx, strlen(uid_idx));
		strcpy(uid_idx, tmp);
		mydb_escape_string(tmp, node, strlen(node));
		strcpy(node, tmp);

		if (mydb_update("replace into uidnodelastlogin "
				"(uid, uid_idx, node_id, date, time) "
				"values ('%s', '%s', '%s', "
				"        FROM_UNIXTIME(%ld, '%%Y-%%m-%%d'), "
				"        FROM_UNIXTIME(%ld, '%%T')) ",
				user, uid_idx, node, ll_time, ll_time) == 0)
			break;

		if (strncmp(node, opshostname, strlen(node)) == 0 ||
		    strncmp(node, "ops", strlen(node)) == 0) {
			if (mydb_update("replace into userslastlogin "
					"(uid, uid_idx, date, time) "
					"values ('%s', '%s', "
					"  FROM_UNIXTIME(%ld, '%%Y-%%m-%%d'), "
					"  FROM_UNIXTIME(%ld, '%%T')) ",
					user, uid_idx, ll_time, ll_time) == 0)
				break;
		}
		else {
			if (mydb_update("replace into nodeuidlastlogin "
					"(node_id, uid_idx, uid, date, time) "
					"values ('%s', '%s', '%s', "
					"  FROM_UNIXTIME(%ld, '%%Y-%%m-%%d'), "
					"  FROM_UNIXTIME(%ld, '%%T')) ",
					node, uid_idx, user, ll_time, ll_time) == 0)
				break;
		}
	}
	return 0;
}