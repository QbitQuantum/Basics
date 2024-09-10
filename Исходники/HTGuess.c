PRIVATE BOOL is_html (char * buf)
{
    char * p = strchr(buf,'<');

    if (p && (!strncasecomp(p, "<HTML>", 6) ||
	      !strncasecomp(p, "<!DOCTYPE HTML", 13) ||
	      !strncasecomp(p, "<HEAD", 5) ||
	      !strncasecomp(p, "<TITLE>", 7) ||
	      !strncasecomp(p, "<BODY>", 6) ||
	      !strncasecomp(p, "<PLAINTEXT>", 11) ||
	      (p[0]=='<' && TOUPPER(p[1]) == 'H' && p[3]=='>')))
	return YES;
    else
	return NO;
}