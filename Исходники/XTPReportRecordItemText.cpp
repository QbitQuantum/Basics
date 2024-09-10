int CXTPReportRecordItemVariant::Compare(CXTPReportColumn*, CXTPReportRecordItem* pItem)
{
	if (GetSortPriority() != -1 || pItem->GetSortPriority() != -1)
		return GetSortPriority() - pItem->GetSortPriority();

	CXTPReportRecordItemVariant* pItemVariant = DYNAMIC_DOWNCAST(CXTPReportRecordItemVariant, pItem);
	if (!pItemVariant)
		return 0;

	ULONG dwFlags = m_pRecord->GetRecords()->IsCaseSensitive() ? 0 : NORM_IGNORECASE;

	LCID lcidnSortLocale = m_nSortLocale;
	if (lcidnSortLocale == LOCALE_USER_DEFAULT)
	{
		lcidnSortLocale = CXTPReportControlLocale::GetActiveLCID();
	}
	return VarCmp(m_oleValue, pItemVariant->m_oleValue, lcidnSortLocale, dwFlags) - VARCMP_EQ;
}