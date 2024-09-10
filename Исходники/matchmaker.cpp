void Matchmaker::CreateWONAccount(const char* theUserName, const char* thePassword)
{
#ifdef DLLSAMPLE
	WONError aError;
	if (mAuthH) { WONAuthCloseHandle(mAuthH); mAuthH = NULL; }
	mAuthH = WONAuthLoginNewAccountA(&aError, mAuthServers, mNumAuthServers, theUserName, COMMUNITY_SAMPLE, thePassword, "", gRequestTimeout);
#else
	mIdentity = Identity(theUserName, COMMUNITY_SAMPLE, thePassword, "", mAuthServers, mNumAuthServers);
	Error aError = mIdentity.AuthenticateNewAccount(gRequestTimeout);
#endif // DLLSAMPLE

	switch (aError)
	{
		case StatusCommon_Success:
			OutputError("Successfully created new account and logged in");

#ifdef DLLSAMPLE
			WONProfileCreate(mAuthH, mProfileServers, mNumProfileServers, "*****@*****.**", gRequestTimeout);
#else
			CreateProfile(&mIdentity, mProfileServers, mNumProfileServers, "*****@*****.**", gRequestTimeout);
#endif

			ListRooms();
			break;
		case StatusAuth_CDKeyInUse:
			OutputError("CD key is already in use");
			break;
		case StatusAuth_CRCFailed:
			OutputError("Invalid version of game");
			break;
		case StatusAuth_UserExists:
			OutputError("User already exists");
			break;
		default:
			OutputError("Account creation failed!", aError);
			break;
	}
}