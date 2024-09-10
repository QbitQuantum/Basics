void OTAcctList::Serialize(OTString & strAppend)
{
	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);

	strAppend.Concatenate("<accountList type=\"%s\" count=\"%d\" >\n\n",
						  strAcctType.Get(), m_mapAcctIDs.size());
	// -----------------

	FOR_EACH(mapOfStrings, m_mapAcctIDs)
	{
		const std::string str_asset_type_id	= (*it).first;
		const std::string str_account_id	= (*it).second;
		OT_ASSERT((str_asset_type_id.size()>0) && (str_account_id.size()>0));

		strAppend.Concatenate("<accountEntry assetTypeID=\"%s\" accountID=\"%s\" />\n\n",
							  str_asset_type_id.c_str(), str_account_id.c_str());
	}
	// -----------------
	strAppend.Concatenate("</accountList>\n\n");
}