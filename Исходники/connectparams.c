gchar* GetConnectParam (ConnectParams* params, const gchar* paramName)
{
	static char tmp[FILENAME_MAX];

	/* use old servername */
	tmp[0] = '\0';
	if (SQLGetPrivateProfileString(params->dsnName->str, paramName, "", tmp, FILENAME_MAX, "odbc.ini") > 0) {
		return tmp;
	}
	return NULL;

}