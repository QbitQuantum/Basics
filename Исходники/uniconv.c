static void
SelectUnicodeRange(AG_Event *event)
{
	char text[4][128];
	AG_Treetbl *tt = AG_PTR(1);
	AG_TlistItem *it = AG_PTR(2);
	struct unicode_range *range = it->p1;
	const struct unicode_range *next_range = NULL;
	Uint32 i, end;
	char *c;

	for (i = 0; i < unicodeRangeCount; i++) {
		if ((&unicodeRanges[i] == range) &&
		    (i+1 < unicodeRangeCount)) {
			next_range = &unicodeRanges[i+1];
			break;
		}
	}
	end = (next_range != NULL) ? next_range->start-1 : 0xffff;

	AG_TreetblClearRows(tt);
	
	for (i = range->start; i < end; i++) {
		if (i == 10)
			continue;
        
		/* prep column 0 */
		unitext[0] = i;
		AG_ExportUnicode(AG_UNICODE_TO_UTF8, utf8text, unitext,
		    sizeof(unitext));
		Snprintf(text[0], sizeof(text[0]), "%s", utf8text);
        
		/* prep column 1 */
		utf8seq[0] = '\0';
		for (c = &utf8text[0]; *c != '\0'; c++) {
			char s[4];
            
			Snprintf(s, sizeof(s), "%x", (unsigned char)*c);
			Strlcat(utf8seq, s, sizeof(utf8seq));
		}
		Snprintf(text[1], sizeof(text[1]), "%s", utf8seq);
        
		AG_TreetblAddRow(tt, NULL, i, "%s,%s", text[0], text[1]);
	}
}