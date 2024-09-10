/*	InitName - initialize name translation
 *
 *	pszServer   machine name for symref daemon
 */
void InitName (IN PSZ pszServer)
{
    PSERVICE_INFO_0 psi;
    PWKSTA_INFO_100 pwi;

    //
    //	Set up daemon server name
    //

    strcpy (szServer, pszServer);

    //
    //	See if our own server is started
    //

    if (NetServiceGetInfo (NULL, "SERVER", 0, (LPBYTE *) &psi) == 0) {
	fServerStarted = TRUE;
	NetApiBufferFree (psi);
	}


    //
    //	Set up workstation name
    //

    NetWkstaGetInfo (NULL, 100, (LPBYTE *) &pwi);

    strcpy (szWksta, pwi->wki100_computername);

    NetApiBufferFree (pwi);
}