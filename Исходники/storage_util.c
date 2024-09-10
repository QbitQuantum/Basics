/**************************************************************************
 * Function: getHashFromAccountIndex
 * Description: returns the unique has for the account located at a given
 * index. Remember that the first few bytes of an account record are the
 * system ID of the account.  Just skip these an pop off the AID.
 * ************************************************************************/ 
md_hash * getHashFromAccountIndex (DmOpenRef AccountDB, UInt16 index) {
	static md_hash ret;
	MemHandle rec = DmQueryRecord (AccountDB, index);
	if (rec) {
		MemPtr buff = MemHandleLock (rec);
		MemMove (ret, buff+sizeof(UInt16)+sizeof(UInt16), sizeof (ret));
		MemHandleUnlock (rec);
	}
	return &ret;
}