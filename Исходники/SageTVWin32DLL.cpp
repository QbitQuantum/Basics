/*
 * Class:     sage_Sage
 * Method:    connectToInternet0
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_sage_Sage_connectToInternet0(JNIEnv *env, jclass jc)
{
	DWORD dwConnectionTypes = INTERNET_CONNECTION_LAN |
		INTERNET_CONNECTION_MODEM |
		INTERNET_CONNECTION_PROXY;
	if (!InternetGetConnectedState(&dwConnectionTypes, 0))
	{
		slog((env, "Internet connection not present, autodialing...\r\n"));
		if (InternetAutodial(INTERNET_AUTODIAL_FORCE_UNATTENDED, 0))
			return sage_Sage_DID_CONNECT;
		else
			return sage_Sage_CONNECT_ERR;
	}
	return 0;
}