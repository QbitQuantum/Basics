char *GOA2GetAuthorizationURL(const char *pszScope)

{
    CPLString osScope;
    CPLString osURL;

    osScope.Seize(CPLEscapeString(pszScope, -1, CPLES_URL));
    osURL.Printf( "%s/auth?scope=%s&redirect_uri=urn:ietf:wg:oauth:2.0:oob&response_type=code&client_id=%s",
                  GOOGLE_AUTH_URL,
                  osScope.c_str(), 
                  CPLGetConfigOption("GOA2_CLIENT_ID", GDAL_CLIENT_ID));
    return CPLStrdup(osURL);
}