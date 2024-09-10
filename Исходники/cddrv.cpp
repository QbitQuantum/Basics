static CDROM_DeviceCapabilities getCapsUsingProductId(const char* prodID)
{
	std::string productID;
	auto strID = as_string(prodID);

	std::for_each(CONST_RANGE(strID, i)
	{
		if (IsAlpha(i))
			productID.push_back(ToUpper(i));
	});