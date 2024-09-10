__int64 TVar::i() const
{
	return isInteger() ? inum : (isDouble() ? (__int64)dnum : (str ? _wtoi64(str) : 0));
}