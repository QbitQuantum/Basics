static int32_t
snmp_import_object(struct snmp_toolinfo *snmptoolctx)
{
	char *string;
	int i;
	int32_t tok;
	struct snmp_oid2str *oid2str;

	if (snmp_import_head(snmptoolctx) < 0)
		return (-1);

	if ((oid2str = calloc(1, sizeof(struct snmp_oid2str))) == NULL) {
		syslog(LOG_ERR, "calloc() failed: %s", strerror(errno));
		return (-1);
	}

	if ((string = strdup(nexttok)) == NULL) {
		syslog(LOG_ERR, "strdup() failed: %s", strerror(errno));
		free(oid2str);
		return (-1);
	}

	oid2str->string = string;
	oid2str->strlen = strlen(nexttok);

	asn_append_oid(&(oid2str->var), &(current_oid));
	if (snmp_suboid_append(&(oid2str->var), (asn_subid_t) val) < 0)
		goto error;

	/*
	 * Prepared the entry - now figure out where to insert it.
	 * After the object we have following options:
	 * 1) new line, blank, ) - then it is an enum oid -> snmp_enumlist;
	 * 2) new line , ( - nonleaf oid -> snmp_nodelist;
	 * 2) ':' - table entry - a variable length SYNTAX_TYPE (one or more)
	 *     may follow and second string must end line -> snmp_tablelist;
	 * 3) OID , string  ) - this is a trap entry or a leaf -> snmp_oidlist;
	 * 4) SYNTAX_TYPE, string (not always), get/set modifier - always last
	 *     and )- this is definitely a leaf.
	 */

	switch (tok = gettoken(snmptoolctx)) {
	    case  ')':
		if ((i = snmp_enum_insert(snmptoolctx, oid2str)) < 0)
			goto error;
		if (i == 0) {
			free(oid2str->string);
			free(oid2str);
		}
		return (1);

	    case '(':
		if (snmp_suboid_append(&current_oid, (asn_subid_t) val) < 0)
			goto error;

		/* 
		 * Ignore the error for nodes since the .def files currently
		 * contain different strings for 1.3.6.1.2.1 - mibII. Only make
		 * sure the memory is freed and don't complain.
		 */
		if ((i = snmp_node_insert(snmptoolctx, oid2str)) <= 0) {
			free(string);
			free(oid2str);
		}
		return (snmp_import_object(snmptoolctx));

	    case ':':
		if (snmp_suboid_append(&current_oid, (asn_subid_t) val) < 0)
			goto error;
		if (snmp_import_table(snmptoolctx, oid2str) < 0)
			goto error;
		/*
		 * A different table entry type was malloced and the data is
		 * contained there.
		 */
		free(oid2str);
		return (1);

	    case TOK_TYPE:
		/* FALLTHROUGH */
	    case TOK_DEFTYPE:
		/* FALLTHROUGH */
	    case TOK_ENUM:
	    	/* FALLTHROUGH */
	    case TOK_BITS:
		if (snmp_import_leaf(snmptoolctx, &tok, oid2str) < 0)
				goto error;
		return (1);

	    default:
		warnx("Unexpected token at line %d - %s", input->lno,
		    input->fname);
		break;
	}

error:
	snmp_mapping_entryfree(oid2str);

	return (-1);
}