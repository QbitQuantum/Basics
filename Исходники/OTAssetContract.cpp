bool OTAssetContract::DisplayStatistics(OTString & strContents) const
{
	const OTString strID(m_ID);
	
	strContents.Concatenate(
							" Asset Type:  %s\n"
							" AssetTypeID: %s\n"
							"\n",
							m_strName.Get(),
							strID.Get());
	return true;
}