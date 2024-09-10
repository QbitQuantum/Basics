bool OTAccount::DisplayStatistics(OTString & strContents) const
{
	const OTString	strAccountID(GetPurportedAccountID()), strServerID(GetPurportedServerID()), 
					strUserID(GetUserID()), strAssetTypeID(m_AcctAssetTypeID);
	
	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);
		
	strContents.Concatenate(
							" Asset Account (%s) Name: %s\n"
							" Last retrieved Balance: %s  on date: %s\n"
							" accountID: %s\n"
							" userID: %s\n"
							" serverID: %s\n"
							" assetTypeID: %s\n"
							"\n",
							strAcctType.Get(),
							m_strName.Get(),
							m_BalanceAmount.Get(), 
							m_BalanceDate.Get(), 
							strAccountID.Get(),
							strUserID.Get(),
							strServerID.Get(),
							strAssetTypeID.Get());
	
	return true;
}