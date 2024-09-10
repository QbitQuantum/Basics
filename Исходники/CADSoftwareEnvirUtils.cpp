	// Return empty string if registry value was not found.
	// WARNING - Do not use this function for values larger that 2048.
	//////////////////////////////////////////////////////////////////////////////////////////////// 
	std::string RetrieveRegistryStringValue( const HKEY in_hkey, const std::string &in_Key )
	{
		std::string tempString = "";

		DWORD	pdwType;
		char	pvData[MAX_VALUE_NAME];
		DWORD	pcbData = MAX_VALUE_NAME;

		LSTATUS errorStatus = 
			RegGetValueA(	in_hkey,		// A handle to an open registry key
							NULL,			// subkey of the key specified by the hkey parameter.
							in_Key.c_str(), // The name of the registry value. 
							RRF_RT_REG_SZ,  // Flags that restrict the data type of value to be queried.  RRF_RT_REG_SZ only strings.
							&pdwType,		// A pointer to a variable that receives a code indicating the type of data stored
							pvData,			// A pointer to a buffer that receives the value's data. 
							&pcbData  );		// A pointer to a variable that specifies the size of the buffer pointed to by the pvData 
		
		if ( errorStatus == ERROR_SUCCESS ) tempString = (char *) pvData;

		return tempString;
	}