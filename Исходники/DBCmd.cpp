bool CDBCmd::GetRec(int fieldno, LONGLONG& ll)
{
	char* ret = GetRec(fieldno);
	if (ret == NULL)
		return false;

	ll = ATOLL(ret);
	return true;
}