bool OTServerContract::SaveContractWallet(OTString & strContents) const
{
	const OTString strID(m_ID);
	OTASCIIArmor   ascName;
	
	if (m_strName.Exists()) // name is in the clear in memory, and base64 in storage.
	{
		ascName.SetString(m_strName, false); // linebreaks == false
	}
	strContents.Concatenate("<notaryProvider name=\"%s\"\n"
							" serverID=\"%s\" />\n\n",
							m_strName.Exists() ? ascName.Get() : "",
							strID.Get());
	
	return true;
}