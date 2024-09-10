	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Return true if in_MaterialName material exists in in_Part
	// in_MaterialName length must be < 32 chars
	bool  MaterialExists( ProSolid in_Part, const std::string &in_MaterialName ) 
													throw (isis::application_exception)
	{
		std::string MaterialName = isis::ConvertToUpperCase(in_MaterialName);

		ProName * p_name;
		isis::isis_ProArrayAlloc(0, sizeof(ProName), 1, (ProArray*) &p_name);
		isis::isis_ProPartMaterialsGet(in_Part, &p_name);

		int numLines;

		isis::isis_ProArraySizeGet((ProArray)p_name, &numLines);

		char stringBuffer[PRO_NAME_SIZE];  // PRO_NAME_SIZE = 32
		for (int i=0; i < numLines; ++i)
		{
			ProWstringToString(stringBuffer, p_name[i]);
			//std::cout << std::endl << stringBuffer;
			if ( strcmp(MaterialName.c_str(), _strupr(stringBuffer ))  == 0  ) 
			{
				isis::isis_ProArrayFree((ProArray*)&p_name);
				return true; 
			}
		}

		return false;
	}