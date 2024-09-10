void IDAController::LoadIDARawData(PBYTE (*RetrieveCallback)(PVOID Context, BYTE *Type, DWORD *Length), PVOID Context)
{
	BYTE type;
	DWORD length;

	multimap <DWORD,  PBasicBlock>::iterator address_hash_map_pIter;
	multimap <string,  DWORD>::iterator fingerprint_hash_map_pIter;
	multimap <string,  DWORD>::iterator name_hash_map_pIter;
	multimap <DWORD,  PMapInfo>::iterator map_info_hash_map_pIter;

	DWORD current_addr = 0L;

	if( m_StorageDB )
		m_StorageDB->BeginTransaction();
	while(1)
	{	
		PBYTE data = RetrieveCallback(Context, &type, &length);
#if DEBUG_LEVEL > 0
		Logger.Log( 10, "%s: ID = %d type = %u Data(0x%X) is Read %u Bytes Long\n", __FUNCTION__, m_FileID, type, data, length);
#endif

		if(type  ==  END_OF_DATA)
		{
#if DEBUG_LEVEL > -1
			Logger.Log(10, LOG_IDA_CONTROLLER, "%s: ID = %d End of Analysis\n", __FUNCTION__);
			Logger.Log(10, LOG_IDA_CONTROLLER, "%s: ID = %d address_hash_map:%u/address_fingerprint_hash_map:%u/fingerprint_hash_map:%u/name_hash_map:%u/map_info_hash_map:%u\n",
				__FUNCTION__, m_FileID, 
				ClientAnalysisInfo->address_hash_map.size(), 
				ClientAnalysisInfo->address_fingerprint_hash_map.size(), 
				ClientAnalysisInfo->fingerprint_hash_map.size(), 
				ClientAnalysisInfo->name_hash_map.size(), 
				ClientAnalysisInfo->map_info_hash_map.size()
			);
#endif
			if(data)
				free(data);
			break;
		}
		if(!data)
			continue;

		if( m_StorageDB )
			m_FileID = DatabaseWriterWrapper(m_StorageDB, type, data, length);
		if(type  ==  BASIC_BLOCK && sizeof(BasicBlock)<= length)
		{
			PBasicBlock pBasicBlock = (PBasicBlock)data;
			current_addr = pBasicBlock->StartAddress;
			Logger.Log(11, LOG_IDA_CONTROLLER, "%s: ID = %d BASIC_BLOCK[StartAddress = %X Flag = %u function addr = %X BlockType = %u]\n", __FUNCTION__, m_FileID,
				pBasicBlock->StartAddress, //ea_t
				pBasicBlock->Flag,  //Flag_t
				pBasicBlock->FunctionAddress, 
				pBasicBlock->BlockType);
#ifdef USE_LEGACY_MAP
			ClientAnalysisInfo->address_hash_map.insert(AddrPBasicBlock_Pair(pBasicBlock->StartAddress, pBasicBlock) );			
#endif
			ClientAnalysisInfo->name_hash_map.insert(NameAddress_Pair(pBasicBlock->Data, pBasicBlock->StartAddress));
			if(pBasicBlock->FingerprintLen>0)
			{
				unsigned char *FingerprintBuffer = (unsigned char *)malloc(pBasicBlock->FingerprintLen+sizeof(short));
				*(unsigned short *)FingerprintBuffer = pBasicBlock->FingerprintLen;
				memcpy(FingerprintBuffer+sizeof(short), pBasicBlock->Data+pBasicBlock->NameLen+pBasicBlock->DisasmLinesLen, *(unsigned short *)FingerprintBuffer);
				ClientAnalysisInfo->address_fingerprint_hash_map.insert(AddressFingerPrintAddress_Pair(pBasicBlock->StartAddress, FingerprintBuffer));
			}
			free(data);
		}else if(type  ==  MAP_INFO && length  ==  sizeof(MapInfo))
		{
			PMapInfo p_map_info = (PMapInfo)data;
#if DEBUG_LEVEL > 2
			Logger.Log( 10, "%s: ID = %d %s %X(%X)->%X\n", __FUNCTION__, m_FileID, 
				MapInfoTypesStr[p_map_info->Type], 
				p_map_info->SrcBlock, 
				p_map_info->SrcBlockEnd, 
				p_map_info->Dst);
#endif
			ClientAnalysisInfo->map_info_hash_map.insert(AddrPMapInfo_Pair(p_map_info->SrcBlock, p_map_info));
			/*
			We don't use backward CFG anymore.
			if(p_map_info->Type  ==  CREF_FROM || p_map_info->Type  ==  CALL)
			{
				PMapInfo p_new_map_info = (PMapInfo)malloc(sizeof(MapInfo));
				p_new_map_info->SrcBlock = p_map_info->Dst;
				p_new_map_info->Src = p_map_info->Dst;
				p_new_map_info->Dst = p_map_info->SrcBlock;
				if(p_map_info->Type  ==  CREF_FROM)
					p_new_map_info->Type = CREF_TO;
				else
					p_new_map_info->Type = CALLED;
				ClientAnalysisInfo->map_info_hash_map.insert(AddrPMapInfo_Pair(p_new_map_info->SrcBlock, p_new_map_info));
			}*/
		}else
		{
			free(data);
		}
	}

	if( m_StorageDB )
		m_StorageDB->EndTransaction();
	FixFunctionAddresses();
	GenerateFingerprintHashMap();
}