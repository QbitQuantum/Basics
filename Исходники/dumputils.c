/*
 * processSQLNamePattern
 *
 * Scan a wildcard-pattern string and generate appropriate WHERE clauses
 * to limit the set of objects returned.  The WHERE clauses are appended
 * to the already-partially-constructed query in buf.  Returns whether
 * any clause was added.
 *
 * conn: connection query will be sent to (consulted for escaping rules).
 * buf: output parameter.
 * pattern: user-specified pattern option, or NULL if none ("*" is implied).
 * have_where: true if caller already emitted "WHERE" (clauses will be ANDed
 * onto the existing WHERE clause).
 * force_escape: always quote regexp special characters, even outside
 * double quotes (else they are quoted only between double quotes).
 * schemavar: name of query variable to match against a schema-name pattern.
 * Can be NULL if no schema.
 * namevar: name of query variable to match against an object-name pattern.
 * altnamevar: NULL, or name of an alternative variable to match against name.
 * visibilityrule: clause to use if we want to restrict to visible objects
 * (for example, "pg_catalog.pg_table_is_visible(p.oid)").  Can be NULL.
 *
 * Formatting note: the text already present in buf should end with a newline.
 * The appended text, if any, will end with one too.
 */
bool
processSQLNamePattern(PGconn *conn, PQExpBuffer buf, const char *pattern,
					  bool have_where, bool force_escape,
					  const char *schemavar, const char *namevar,
					  const char *altnamevar, const char *visibilityrule)
{
	PQExpBufferData schemabuf;
	PQExpBufferData namebuf;
	int			encoding = PQclientEncoding(conn);
	bool		inquotes;
	const char *cp;
	int			i;
	bool		added_clause = false;

#define WHEREAND() \
	(appendPQExpBufferStr(buf, have_where ? "  AND " : "WHERE "), \
	 have_where = true, added_clause = true)

	if (pattern == NULL)
	{
		/* Default: select all visible objects */
		if (visibilityrule)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s\n", visibilityrule);
		}
		return added_clause;
	}

	initPQExpBuffer(&schemabuf);
	initPQExpBuffer(&namebuf);

	/*
	 * Parse the pattern, converting quotes and lower-casing unquoted letters.
	 * Also, adjust shell-style wildcard characters into regexp notation.
	 *
	 * We surround the pattern with "^(...)$" to force it to match the whole
	 * string, as per SQL practice.  We have to have parens in case the string
	 * contains "|", else the "^" and "$" will be bound into the first and
	 * last alternatives which is not what we want.
	 *
	 * Note: the result of this pass is the actual regexp pattern(s) we want
	 * to execute.  Quoting/escaping into SQL literal format will be done
	 * below using appendStringLiteralConn().
	 */
	appendPQExpBufferStr(&namebuf, "^(");

	inquotes = false;
	cp = pattern;

	while (*cp)
	{
		char		ch = *cp;

		if (ch == '"')
		{
			if (inquotes && cp[1] == '"')
			{
				/* emit one quote, stay in inquotes mode */
				appendPQExpBufferChar(&namebuf, '"');
				cp++;
			}
			else
				inquotes = !inquotes;
			cp++;
		}
		else if (!inquotes && isupper((unsigned char) ch))
		{
			appendPQExpBufferChar(&namebuf,
								  pg_tolower((unsigned char) ch));
			cp++;
		}
		else if (!inquotes && ch == '*')
		{
			appendPQExpBufferStr(&namebuf, ".*");
			cp++;
		}
		else if (!inquotes && ch == '?')
		{
			appendPQExpBufferChar(&namebuf, '.');
			cp++;
		}
		else if (!inquotes && ch == '.')
		{
			/* Found schema/name separator, move current pattern to schema */
			resetPQExpBuffer(&schemabuf);
			appendPQExpBufferStr(&schemabuf, namebuf.data);
			resetPQExpBuffer(&namebuf);
			appendPQExpBufferStr(&namebuf, "^(");
			cp++;
		}
		else if (ch == '$')
		{
			/*
			 * Dollar is always quoted, whether inside quotes or not. The
			 * reason is that it's allowed in SQL identifiers, so there's a
			 * significant use-case for treating it literally, while because
			 * we anchor the pattern automatically there is no use-case for
			 * having it possess its regexp meaning.
			 */
			appendPQExpBufferStr(&namebuf, "\\$");
			cp++;
		}
		else
		{
			/*
			 * Ordinary data character, transfer to pattern
			 *
			 * Inside double quotes, or at all times if force_escape is true,
			 * quote regexp special characters with a backslash to avoid
			 * regexp errors.  Outside quotes, however, let them pass through
			 * as-is; this lets knowledgeable users build regexp expressions
			 * that are more powerful than shell-style patterns.
			 */
			if ((inquotes || force_escape) &&
				strchr("|*+?()[]{}.^$\\", ch))
				appendPQExpBufferChar(&namebuf, '\\');
			i = PQmblen(cp, encoding);
			while (i-- && *cp)
			{
				appendPQExpBufferChar(&namebuf, *cp);
				cp++;
			}
		}
	}

	/*
	 * Now decide what we need to emit.  Note there will be a leading "^(" in
	 * the patterns in any case.
	 */
	if (namebuf.len > 2)
	{
		/* We have a name pattern, so constrain the namevar(s) */

		appendPQExpBufferStr(&namebuf, ")$");
		/* Optimize away a "*" pattern */
		if (strcmp(namebuf.data, "^(.*)$") != 0)
		{
			WHEREAND();
			if (altnamevar)
			{
				appendPQExpBuffer(buf, "(%s ~ ", namevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				appendPQExpBuffer(buf, "\n        OR %s ~ ", altnamevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				appendPQExpBufferStr(buf, ")\n");
			}
			else
			{
				appendPQExpBuffer(buf, "%s ~ ", namevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				appendPQExpBufferChar(buf, '\n');
			}
		}
	}

	if (schemabuf.len > 2)
	{
		/* We have a schema pattern, so constrain the schemavar */

		appendPQExpBufferStr(&schemabuf, ")$");
		/* Optimize away a "*" pattern */
		if (strcmp(schemabuf.data, "^(.*)$") != 0 && schemavar)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s ~ ", schemavar);
			appendStringLiteralConn(buf, schemabuf.data, conn);
			appendPQExpBufferChar(buf, '\n');
		}
	}
	else
	{
		/* No schema pattern given, so select only visible objects */
		if (visibilityrule)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s\n", visibilityrule);
		}
	}

	termPQExpBuffer(&schemabuf);
	termPQExpBuffer(&namebuf);

	return added_clause;
#undef WHEREAND
}