/*
 * Called when we need to persist our state.
 */
void Appearance::save(char *szIni, char *szIniGroup, BOOL bIsForExport, char *prefix)
{
	char iBuf[32];

	AtlTrace("Writing label to %s\n", szIni);

	WritePrivateProfileString(szIniGroup, LABEL_FORMAT, labelFormat, szIni);
	WritePrivateProfileString(szIniGroup, LABEL_SELECTOR, labelSelector, szIni);
	WritePrivateProfileString(szIniGroup, LABEL_METER, itoa(getLabelMeterIndex(), iBuf, 10), szIni);
}