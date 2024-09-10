/** What to convert has SECURITY IMPLICATIONS. An attacker must not be allowed
 ** to insert abitrary data in the output.
 **
 ** So data is categorised according to its source, via an enum in anlghea3.h.
 ** In the following descriptions of the security levels, "convert" means
 ** converting e.g. < to &lt; and "escape" means using \< to prevent this
 ** happening. "unprintable" means characters set as unprintable in init.c:
 ** note that this is only known unprintable characters 0x00 - 0x1F, 0x7F,
 ** and in ISO-8859-* also 0x80-0x9F.
 **
 ** 1) AS_IS: Completely trusted string. Output as-is.
 ** 2) TRUSTED: E.g. a string from a language file. Also completely trusted. In
 **    single-byte mode, convert characters (for convenience not security), but
 **    allow any of the special characters to be escaped, even \< .
 **    In multibyte mode, output the string as-is.
 ** 3) FROM_CFG: An item read in from configuration. Unless we're in CGI mode,
 **    treat as case 2. In CGI mode, the input could have come from the form,
 **    so be more cautious to avoid cross-site scripting attacks. Specifically,
 **    convert all characters, allow only \& and \\ escapes, and use '?' in
 **    place of unprintable characters.
 ** 4) UNTRUSTED: E.g. data from the logfile. Do all conversions, don't allow
 **    any escapes, and use '?' in place of all unprintable characters.
 ** 5) IN_HREF: Special case for data from the config file which is being put
 **    inside an <a href=""> or <img src="">. As 3), but use %nm in place of
 **    unprintable characters. (NB data from the logfile which is put inside
 **    an href uses escfprintf() instead of this function.)
 **/
void htmlputs(FILE *outf, Outchoices *od, char *s, choice source) {
#ifdef EBCDIC
  extern unsigned char os_toascii[];
#endif
  extern logical cgi;
  extern logical unprintable[256];

  char w1[64];
  char *c;
  char *w = w1;
  int len = 0;

  if (source == FROM_CFG && !cgi)
    source = TRUSTED;

  if (source == TRUSTED && od->multibyte)
    source = AS_IS;

  if (source == AS_IS) {
    fputs(s, outf);
    return;
  }

  for (c = s; *c != '\0'; c++) {
    if (*c == '<') {
      PUTs(w, "&lt;", 0);
      len += 4;
    }
    else if (*c == '>') {
      PUTs(w, "&gt;", 0);
      len += 4;
    }
    else if (*c == '&') {
      PUTs(w, "&amp;", 0);
      len += 5;
    }
    else if (*c == '"') {
      PUTs(w, "&quot;", 0);
      len += 6;
    }
    else if (*c == '\\' &&  /* escape these chars in these circumstances: */
	     ((source == TRUSTED && (*(c + 1) == '<' || *(c + 1) == '>' ||
				     *(c + 1) == '&' || *(c + 1) == '"' ||
				     *(c + 1) == '\\'))
	      || (source == FROM_CFG && (*(c + 1) == '&' ||
					 *(c + 1) == '\\')))) {
      od->html = FALSE;
      PUTc(w, *(++c));
      len += 1;
    }
    else if (unprintable[(unsigned char)(*c)] && source != TRUSTED) {
      /* unprintable chars */
      if (source == IN_HREF) {
#ifdef EBCDIC
	sprintf(w, "%%%.2X", os_toascii[*c]);
#else
	sprintf(w, "%%%.2X", (unsigned char)(*c));
#endif
	w += 3;
	len += 3;
      }
      else {  /* source == FROM_CFG or UNTRUSTED */
	PUTc(w, '?');
	len += 1;
      }
    }
    else {  /* output non-special characters as-is */
      PUTc(w, *c);
      len += 1;
    }
    if (len > 56) {
      *w = '\0';
      fputs(w1, outf);
      w = w1;
      len = 0;
    }
  }
  *w = '\0';
  fputs(w1, outf);
}