/** log that user logged in */
bool cIPLog::Log(cConnDC *conn, int action, int info)
{
	sUserStruct entry;
	entry.mIP = cBanList::Ip2Num(conn->AddrIP());
	if(conn->mpUser != NULL)
		entry.mNick = conn->mpUser->mNick;
	else
		entry.mNick = "";

	entry.mDate = cTime().Sec();
	entry.mType = action;
	entry.mInfo = info;
	SetBaseTo(&entry);
	return SavePK();
}