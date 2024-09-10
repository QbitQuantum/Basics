void clrcmdline(char * const str, const unsigned orgx, const unsigned orgy)
{
	if(str) {
		goxy(orgx, orgy);
		fputmc(' ', strlen(str) + 1, stdout);
		strset(str, 0);
	}
	goxy(orgx, orgy);
}