//-----------------------------------------------------------------------------
// 轉型運算子
C_NTime::operator __int64 () const
{
	struct tm sTime = *this;

	return _mktime64(&sTime);
}