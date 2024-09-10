/*
 * Handle gopher menus
 */
void gopher_menu(state *st)
{
	FILE *fp;
	sdirent dir[MAX_SDIRENT];
	struct tm *ltime;
	struct stat file;
	char buf[BUFSIZE];
	char pathname[BUFSIZE];
	char displayname[BUFSIZE];
	char encodedname[BUFSIZE];
	char timestr[20];
	char sizestr[20];
	char *parent;
	char *c;
	char type;
	int width;
	int num;
	int i;
	int n;

	/* Check for a gophermap */
	snprintf(pathname, sizeof(pathname), "%s/%s",
		st->req_realpath, st->map_file);

	if (stat(pathname, &file) == OK &&
	    (file.st_mode & S_IFMT) == S_IFREG) {

		/* Parse gophermap */
		if (gophermap(st, pathname, 0) == QUIT) {
			footer(st);
			return;
		}
	}

	else {
		/* Check for a gophertag */
		snprintf(pathname, sizeof(pathname), "%s/%s",
			st->req_realpath, st->tag_file);

		if (stat(pathname, &file) == OK &&
		    (file.st_mode & S_IFMT) == S_IFREG) {

			/* Read & output gophertag */
			if ((fp = fopen(pathname , "r"))) {

				fgets(buf, sizeof(buf), fp);
				chomp(buf);

				info(st, buf, TYPE_TITLE);
				info(st, EMPTY, TYPE_INFO);
				fclose(fp);
			}
		}

		/* No gophermap or tag found - print default header */
		else if (st->opt_header) {

			/* Use the selector as menu title */
			sstrlcpy(displayname, st->req_selector);

			/* Shorten too long titles */
			while (strlen(displayname) > (st->out_width - sizeof(HEADER_FORMAT))) {
				if ((c = strchr(displayname, '/')) == NULL) break;

				if (!*++c) break;
				sstrlcpy(displayname, c);
			}

			/* Output menu title */
			snprintf(buf, sizeof(buf), HEADER_FORMAT, displayname);
			info(st, buf, TYPE_TITLE);
			info(st, EMPTY, TYPE_INFO);
		}
	}

	/* Scan the directory */
	num = sortdir(st->req_realpath, dir, MAX_SDIRENT);
	if (num < 0) die(st, ERR_NOTFOUND, "WTF?");

	/* Create link to parent directory */
	if (st->opt_parent) {
		sstrlcpy(buf, st->req_selector);
		parent = dirname(buf);

		/* Root has no parent */
		if (strcmp(st->req_selector, ROOT) != MATCH) {

			/* Prevent double-slash */
			if (strcmp(parent, ROOT) == MATCH) parent++;

			/* Print link */
			printf("1%-*s\t%s/\t%s\t%i" CRLF,
				st->opt_date ? (st->out_width - 1) : (int) strlen(PARENT),
				PARENT, parent, st->server_host, st->server_port);
		}
	}

	/* Width of filenames for fancy listing */
	width = st->out_width - DATE_WIDTH - 15;

	/* Loop through the directory entries */
	for (i = 0; i < num; i++) {

		/* Get full path+name */
		snprintf(pathname, sizeof(pathname), "%s/%s",
			st->req_realpath, dir[i].name);

		/* Skip dotfiles and non world-readables */
		if (dir[i].name[0] == '.') continue;
		if ((dir[i].mode & S_IROTH) == 0) continue;

		/* Skip gophermaps and tags (but not dirs) */
		if ((dir[i].mode & S_IFMT) != S_IFDIR) {
			if (strcmp(dir[i].name, st->map_file) == MATCH) continue;
			if (strcmp(dir[i].name, st->tag_file) == MATCH) continue;
		}

		/* Skip files marked for hiding */
		for (n = 0; n < st->hidden_count; n++)
			if (strcmp(dir[i].name, st->hidden[n]) == MATCH) break;
		if (n < st->hidden_count) continue;	/* Cruel hack... */

		/* Generate display name with correct output charset */
		if (st->opt_iconv)
			sstrniconv(st->out_charset, displayname, dir[i].name);
		else
			sstrlcpy(displayname, dir[i].name);

		/* #OCT-encode filename */
		strnencode(encodedname, dir[i].name, sizeof(encodedname));

		/* Handle inline .gophermap */
		if (strstr(displayname, st->map_file) > displayname) {
			gophermap(st, pathname, 0);
			continue;
		}

		/* Handle directories */
		if ((dir[i].mode & S_IFMT) == S_IFDIR) {

			/* Check for a gophertag */
			snprintf(buf, sizeof(buf), "%s/%s",
				pathname, st->tag_file);

			if (stat(buf, &file) == OK &&
			    (file.st_mode & S_IFMT) == S_IFREG) {

				/* Use the gophertag as displayname */
				if ((fp = fopen(buf , "r"))) {

					fgets(buf, sizeof(buf), fp);
					chomp(buf);
					fclose(fp);

					/* Skip empty gophertags */
					if (*buf) {

						/* Convert to output charset */
						if (st->opt_iconv) sstrniconv(st->out_charset, displayname, buf);
						else sstrlcpy(displayname, buf);
					}

				}
			}

			/* Dir listing with dates */
			if (st->opt_date) {
				ltime = localtime(&dir[i].mtime);
				strftime(timestr, sizeof(timestr), DATE_FORMAT, ltime);

				/* Hack to get around UTF-8 byte != char */
				n = width - strcut(displayname, width);
				strrepeat(buf, ' ', n);

				printf("1%s%s   %s        -  \t%s%s/\t%s\t%i" CRLF,
					displayname,
					buf,
					timestr,
					st->req_selector,
					encodedname,
					st->server_host,
					st->server_port);
			}

			/* Regular dir listing */
			else {
				strcut(displayname, st->out_width);
				printf("1%s\t%s%s/\t%s\t%i" CRLF,
					displayname,
					st->req_selector,
					encodedname,
					st->server_host,
					st->server_port);
			}

			continue;
		}

		/* Skip special files (sockets, fifos etc) */
		if ((dir[i].mode & S_IFMT) != S_IFREG) continue;

		/* Get file type */
		type = gopher_filetype(st, pathname, st->opt_magic);

		/* File listing with dates & sizes */
		if (st->opt_date) {
			ltime = localtime(&dir[i].mtime);
			strftime(timestr, sizeof(timestr), DATE_FORMAT, ltime);
			strfsize(sizestr, dir[i].size, sizeof(sizestr));

			/* Hack to get around UTF-8 byte != char */
			n = width - strcut(displayname, width);
			strrepeat(buf, ' ', n);

			printf("%c%s%s   %s %s\t%s%s\t%s\t%i" CRLF, type,
				displayname,
				buf,
				timestr,
				sizestr,
				st->req_selector,
				encodedname,
				st->server_host,
				st->server_port);
		}

		/* Regular file listing */
		else {
			strcut(displayname, st->out_width);
			printf("%c%s\t%s%s\t%s\t%i" CRLF, type,
				displayname,
				st->req_selector,
				encodedname,
				st->server_host,
				st->server_port);
		}
	}

	/* Print footer */
	footer(st);
}