static void
extract_ps_from_filestream (FILE *f,
                            TrackerSparqlBuilder *preupdate,
                            TrackerSparqlBuilder *metadata)
{
	gchar *line;
	gsize length;
	gssize read_char;
	gsize accum;
	gsize max_bytes;

	line = NULL;
	length = 0;

	tracker_sparql_builder_predicate (metadata, "a");
	tracker_sparql_builder_object (metadata, "nfo:PaginatedTextDocument");

	/* 20 MiB should be enough! (original safe limit) */
	accum = 0;
	max_bytes = 20u << 20;

	/* Reuse the same buffer for all lines. Must be dynamically allocated with
	 * malloc family methods as getline() may re-size it with realloc() */
	length = 1024;
	line = g_malloc (length);

	/* Halt the whole when one of these conditions is met:
	 *  a) Reached max bytes to read
	 *  b) No more lines to read
	 */
	while ((accum < max_bytes) &&
	       (read_char = tracker_getline (&line, &length, f)) != -1) {
		gboolean pageno_atend = FALSE;
		gboolean header_finished = FALSE;

		/* Update accumulated bytes read */
		accum += read_char;

		line[read_char - 1] = '\0';  /* overwrite '\n' char */

		if (!header_finished && strncmp (line, "%%Copyright:", 12) == 0) {
			tracker_sparql_builder_predicate (metadata, "nie:copyright");
			tracker_sparql_builder_object_unvalidated (metadata, line + 13);
		} else if (!header_finished && strncmp (line, "%%Title:", 8) == 0) {
			tracker_sparql_builder_predicate (metadata, "nie:title");
			tracker_sparql_builder_object_unvalidated (metadata, line + 9);
		} else if (!header_finished && strncmp (line, "%%Creator:", 10) == 0) {
			tracker_sparql_builder_predicate (metadata, "nco:creator");
			tracker_sparql_builder_object_blank_open (metadata);
			tracker_sparql_builder_predicate (metadata, "a");
			tracker_sparql_builder_object (metadata, "nco:Contact");
			tracker_sparql_builder_predicate (metadata, "nco:fullname");
			tracker_sparql_builder_object_unvalidated (metadata, line + 11);
			tracker_sparql_builder_object_blank_close (metadata);
		} else if (!header_finished && strncmp (line, "%%CreationDate:", 15) == 0) {
			gchar *date;

			date = date_to_iso8601 (line + 16);
			if (date) {
				tracker_sparql_builder_predicate (metadata, "nie:contentCreated");
				tracker_sparql_builder_object_unvalidated (metadata, date);
				g_free (date);
			}
		} else if (strncmp (line, "%%Pages:", 8) == 0) {
			if (strcmp (line + 9, "(atend)") == 0) {
				pageno_atend = TRUE;
			} else {
				gint64 page_count;

				page_count = g_ascii_strtoll (line + 9, NULL, 10);
				tracker_sparql_builder_predicate (metadata, "nfo:pageCount");
				tracker_sparql_builder_object_int64 (metadata, page_count);
			}
		} else if (strncmp (line, "%%EndComments", 14) == 0) {
			header_finished = TRUE;

			if (!pageno_atend) {
				break;
			}
		}
	}

	/* Deallocate the buffer */
	if (line) {
		g_free (line);
	}
}