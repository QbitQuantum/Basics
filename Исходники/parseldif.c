/*
 * Lies die erste Zeile eines beliebigen Records nach position `offset' in `s'.
 * Setze *pos (falls pos != 0).
 * Liefere 0 bei Erfolg, -1 sonst.
 * Bei Erfolg:
 *   - pos ist die exakte Anfangsposition.
 *   - Setze *key auf den Schluessel (falls key != 0).
 *   - Setze *dn auf den Distinguished Name (falls dn != 0).
 * EOF ist kein Fehler und liefert *key = 0 (falls key != 0);
 *
 * Der Schluessel ist dabei
 *   "delete" fuer "changetype: delete"
 *   "modify" fuer "changetype: modify"
 *   "rename" fuer "changetype: moddn" und "changetype: modrdn",
 *   "add" fuer "changetype: add" erlauben wir mal ganz frech ebenfalls
 * oder andernfalls der Wert von "ldapvi-key: ...", das als erste
 * Zeile im attrval-record erscheinen muss.
 */
static int
ldif_read_header(GString *tmp1, GString *tmp2,
		 FILE *s, long offset, char **key, char **dn, long *pos)
{
	char **rdns = 0;
	char *k;
	char *d;
	long pos2;

	if (offset != -1)
		if (fseek(s, offset, SEEK_SET) == -1) syserr();
	do {
		if (pos)
			if ( (*pos = ftell(s)) == -1) syserr();
		if (ldif_read_line(s, tmp1, tmp2) == -1) return -1;
		if (tmp1->len == 0 && feof(s)) {
			if (key) *key = 0;
			return 0;
		}
		if (!strcmp(tmp1->str, "version")) {
			if (strcmp(tmp2->str, "1")) {
				fputs("Error: Invalid file format.\n", stderr);
				return -1;
			}
			tmp1->len = 0;
		}
	} while (!tmp1->len);

	rdns = ldap_explode_dn(tmp2->str, 0);
	if (!rdns) {
		fputs("Error: Invalid distinguished name string.\n", stderr);
		return -1;
	}
	if (dn)
		d = xdup(tmp2->str);

	if ( (pos2 = ftell(s)) == -1) syserr();

	if (ldif_read_line(s, tmp1, tmp2) == -1) {
		if (dn) free(d);
		return -1;
	}
	if (!strcmp(tmp1->str, "ldapvi-key"))
		k = tmp2->str;
	else if (!strcmp(tmp1->str, "changetype")) {
		if (!strcmp(tmp2->str, "modrdn"))
			k = "rename";
		else if (!strcmp(tmp2->str, "moddn"))
			k = "rename";
		else if (!strcmp(tmp2->str, "delete")
			 || !strcmp(tmp2->str, "modify")
			 || !strcmp(tmp2->str, "add"))
			k = tmp2->str;
		else {
			fputs("Error: invalid changetype.\n", stderr);
			if (dn) free(d);
			return -1;
		}
	} else if (!strcmp(tmp1->str, "control")) {
		fputs("Error: Sorry, 'control:' not supported.\n", stderr);
		if (dn) free(d);
		return -1;
	} else {
		k = "add";
		if (fseek(s, pos2, SEEK_SET) == -1) syserr();
	}

	if (key) *key = xdup(k);
	if (dn) *dn = d;
	ldap_value_free(rdns);
	return 0;
}