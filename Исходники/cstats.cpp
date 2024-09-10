void cStats::CleanUp()
{
	mQuery.Clear();
	mQuery.OStream() << "delete from " << mMySQLTable.mName << " where("
		"realtime < " << cTime().Sec() - 7 * 3600* 24 <<
		")";
	mQuery.Query();
	mQuery.Clear();
}