/** log that user logged in */
bool cRegList::Logout(const string &nick)
{
	if(!FindRegInfo(mModel, nick)) return false;
	mModel.mLogoutLast = cTime().Sec()-1; // this is a patch for users that connect twice
	return UpdatePKVar("logout_last");
}