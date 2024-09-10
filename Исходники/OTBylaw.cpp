void OTBylaw::Serialize(OTString & strAppend,
						bool bCalculatingID/*=false*/)
{
	strAppend.Concatenate("<bylaw\n name=\"%s\"\n"
						  " numVariables=\"%d\"\n"
						  " numClauses=\"%d\"\n"
						  " numHooks=\"%d\"\n"
						  " numCallbacks=\"%d\"\n"
						  " language=\"%s\" >\n\n",
						  m_strName.Get(),
						  m_mapVariables.size(), // HOW MANY VARIABLES?
						  m_mapClauses.size(), // HOW MANY CLAUSES?
						  m_mapHooks.size(), // How many HOOKS?
						  m_mapCallbacks.size(), // How many CALLBACK?
						  m_strLanguage.Get());
	// ------------------------------

	FOR_EACH(mapOfVariables, m_mapVariables)
	{
		OTVariable * pVar = (*it).second;
		OT_ASSERT(NULL != pVar);

		pVar->Serialize(strAppend, bCalculatingID); // Variables save in a specific state during ID calculation (no matter their current actual value.)
	}