void CRconn::ConstructL()
{
	TInt err;

	User::LeaveIfError(iServ.Connect());

	err = iConn.Open(iServ);
	if (KErrNone != err) {
		DEBUG_WARNING("iConn.Open err=%d\n", err);
		User::Leave(err);
	}
}