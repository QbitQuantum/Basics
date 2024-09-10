void OTVariable::Serialize(OTString & strAppend,
						   bool bCalculatingID/*=false*/)
{
	// ---------------------------------------
	std::string str_access("");

	switch (m_Access) {
		case OTVariable::Var_Constant:		// This cannot be changed from inside the script.
			str_access = "constant";
			break;
		case OTVariable::Var_Persistent:	// This can be changed without notifying the parties.
			str_access = "persistent";
			break;
		case OTVariable::Var_Important:		// This cannot be changed without notifying the parties.
			str_access = "important";
			break;
		default:
			OTLog::Error("OTVariable::Serialize:  ERROR:  Bad variable type.\n");
			break;
	}
	// ---------------------------------------
	std::string str_type;

	switch (m_Type) {
		case OTVariable::Var_String:
		{
			str_type = "string";

			if ((false == bCalculatingID) && // we don't serialize the variable's value when calculating the
				(m_str_Value.size() > 0)) // owner OTScriptable's ID, since the value can change over time.
			{
				OTString strVal(m_str_Value.c_str());
				OTASCIIArmor ascVal(strVal);
				strAppend.Concatenate("<variable\n name=\"%s\"\n"
									  " value=\"%s\"\n"
									  " type=\"%s\"\n"
									  " access=\"%s\" >\n%s</variable>\n\n",
									  m_strName.Get(),
									  "exists",
									  str_type.c_str(),
									  str_access.c_str(),
									  ascVal.Get());
			}
			else
			{
				strAppend.Concatenate("<variable\n name=\"%s\"\n"
									  " value=\"%s\"\n"
									  " type=\"%s\"\n"
									  " access=\"%s\" />\n\n",
									  m_strName.Get(),
									  "none", // value
									  str_type.c_str(),
									  str_access.c_str());
			}
		}
			break;
		case OTVariable::Var_Integer:
			str_type = "integer";
			strAppend.Concatenate("<variable\n name=\"%s\"\n"
								  " value=\"%d\"\n"
								  " type=\"%s\"\n"
								  " access=\"%s\" />\n\n",
								  m_strName.Get(),
								  bCalculatingID ? 0 : m_nValue, // we don't serialize the variable's value when calculating the smart contract's ID.
								  str_type.c_str(), str_access.c_str());
			break;
		case OTVariable::Var_Bool:
			str_type = "bool";
			strAppend.Concatenate("<variable\n name=\"%s\"\n"
								  " value=\"%s\"\n"
								  " type=\"%s\"\n"
								  " access=\"%s\" />\n\n",
								  m_strName.Get(),
								  bCalculatingID ? "false" : (m_bValue ? "true" : "false"), // we don't serialize the variable's value when calculating the smart contract's ID.
								  str_type.c_str(), str_access.c_str());
			break;
		default:
			str_type = "ERROR_VARIABLE_TYPE";
			OTLog::Error("OTVariable::Serialize: Error, Wrong Type -- not serializing.\n");
			break;
	}
	// ---------------------------------------
}