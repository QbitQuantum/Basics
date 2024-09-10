// Routine to load date qualifier strings from resources. Do not call before AfApp has m_hinst.
void LoadDateQualifiers()
{
	if (g_fDoneDateQual)
		return;

	int i;
	for (i = 0; i < 5; i++)
	{
		StrUni stu(g_rgridDateQual1[i]);
		Assert(stu.Length() < knPrecLen);
		u_strcpy(g_rgchwPrecFull[i], stu.Chars());
		StrAnsi sta(g_rgridDateQual1[i]);
		Assert(sta.Length() < knPrecLen);
		strcpy_s(g_rgchPrecFull[i], sta.Length(), sta.Chars());
	}
	for (i = 0; i < 2; i++)
	{
		StrUni stu(g_rgridDateQual2[i]);
		Assert(stu.Length() < knAdBcLen);
		u_strcpy(g_rgchwBC_ADFull[i], stu.Chars());
		StrAnsi sta(g_rgridDateQual2[i]);
		Assert(stu.Length() < knAdBcLen);
		strcpy_s(g_rgchBC_ADFull[i], sta.Length(), sta.Chars());
	}
	for (i = 0; i < 3; i++)
	{
		StrUni stu(g_rgridDateBlank[i]);
		Assert(stu.Length() < knBlankLen);
		u_strcpy(g_rgchwBlankFull[i], stu.Chars());
		StrAnsi sta(g_rgridDateBlank[i]);
		Assert(stu.Length() < knBlankLen);
		strcpy_s(g_rgchBlankFull[i], sta.Length(), sta.Chars());
	}
	g_fDoneDateQual = true;
}