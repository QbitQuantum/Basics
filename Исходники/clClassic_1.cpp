clClassic_1::clClassic_1(char * szPrimaryWork, const clCd_1 & d) : clCd_1(d)
{
	if (szPrimaryWork)
	{
		strncpy(szPrimaryWork_, szPrimaryWork, (strlen(szPrimaryWork) < sizeof(szPrimaryWork_)) ? strlen(szPrimaryWork) : sizeof(szPrimaryWork_) - 1);
		szPrimaryWork_[(strlen(szPrimaryWork) < sizeof(szPrimaryWork_)) ? strlen(szPrimaryWork) : sizeof(szPrimaryWork_) - 1] = '\0';
	}
	else
		szPrimaryWork_[0] = '\0';
}