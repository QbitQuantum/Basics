DDWORD SpellPickup::EngineMessageFn(DDWORD messageID, void *pData, DFLOAT lData)
{
	CServerDE* pServerDE = GetServerDE();
	if (!pServerDE) return DFALSE;

	switch(messageID)
	{
		case MID_POSTPROPREAD:
		{
			ObjectCreateStruct *pStruct = (ObjectCreateStruct*)pData;
			
			// Set the model filename
			_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)"Models/Powerups/");
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)".abc");

			// Set the skin filename
			_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)"Skins/Powerups/");
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)".dtx");

			break;
		}

		case MID_INITIALUPDATE:
		{
			DVector vDims;
			VEC_SET(vDims, 20.0f, 25.0f, 10.0f);

			pServerDE->SetObjectDims(m_hObject, &vDims);
		}

		default : break;
	}

	return PickupObject::EngineMessageFn(messageID, pData, lData);
}