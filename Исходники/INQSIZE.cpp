/*
AR-921013
CH UT_InqPathSize_i64                              Finn filstørrelse
CD ==================================================================
CD Formål:
CD Henter filstørrelsen for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD UT_INT64 *n64Size   u   Filstørrelse
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_InqPathSize_i64(szPath,&n64Size);
   ==================================================================
*/
SK_EntPnt_UT short UT_InqPathSize_i64(char *pszPath,UT_INT64 *n64Size)
{
#ifdef LINUX
	struct stat buf;
#else
    struct _stat32i64 buf;
#endif
	 int result;


	 // Hent filopplysninger
    //result = _stat(pszPath,&buf);
#ifdef LINUX
    result = stat(pszPath,&buf);
#else
    result = _stat32i64(pszPath,&buf);
#endif
	 if (result == 0) {
		  *n64Size = buf.st_size;
	 }

	 return (short)result;
}