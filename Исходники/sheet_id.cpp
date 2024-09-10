//-----------------------------------------------
//	Build
//
//-----------------------------------------------
bool CSheetId::buildSheetId(const std::string& sheetName)
{
	nlassert(_Initialised);
	
	// When no sheet_id.bin is loaded, use dynamically assigned IDs.
	if (_DontHaveSheetKnowledge)
	{
		std::string sheetNameLc = toLower(sheetName);
		std::map<std::string, uint32>::iterator it = _DevSheetNameToId.find(sheetNameLc);
		if (it == _DevSheetNameToId.end())
		{
			// Create a new dynamic sheet ID.
			// nldebug("SHEETID: Creating a dynamic sheet id for '%s'", sheetName.c_str());
			std::string sheetType = CFile::getExtension(sheetNameLc);
			std::string sheetName = CFile::getFilenameWithoutExtension(sheetNameLc);
			std::map<std::string, uint32>::iterator tit = _DevTypeNameToId.find(sheetType);
			uint32 typeId;
			if (tit == _DevTypeNameToId.end())
			{
				_FileExtensions.push_back(sheetType);
				_DevSheetIdToName.push_back(std::vector<std::string>());
				typeId = (uint32)_FileExtensions.size() - 1;
				_DevTypeNameToId[sheetType] = typeId;
				std::string unknownNewType = std::string("unknown." + sheetType);
				_DevSheetIdToName[typeId].push_back(unknownNewType);
				_Id.IdInfos.Type = typeId;
				_Id.IdInfos.Id = _DevSheetIdToName[typeId].size() - 1;
				_DevSheetNameToId[unknownNewType] = _Id.Id;
				if (sheetName == "unknown")
					return true; // Return with the unknown sheet id of this type
			}
			else
			{
				typeId = tit->second;
				_Id.IdInfos.Type = typeId;
			}
			// Add a new sheet name to the type
			_DevSheetIdToName[typeId].push_back(sheetNameLc);
			_Id.IdInfos.Id = _DevSheetIdToName[typeId].size() - 1;
			// nldebug("SHEETID: Type %i, id %i, sheetid %i", _Id.IdInfos.Type, _Id.IdInfos.Id, _Id.Id);
			_DevSheetNameToId[sheetNameLc] = _Id.Id;
			return true;
		}
		_Id.Id = it->second;
		return true;
	}

	// try looking up the sheet name in _SheetNameToId
	CStaticMap<CChar,uint32,CCharComp>::const_iterator itId;
	CChar c;
	c.Ptr = new char [sheetName.size()+1];
	strcpy(c.Ptr, sheetName.c_str());
	toLower(c.Ptr);

	itId = _SheetNameToId.find (c);
	delete [] c.Ptr;
	if( itId != _SheetNameToId.end() )
	{
		_Id.Id = itId->second;
#ifdef NL_DEBUG_SHEET_ID
		// store debug info
		_DebugSheetName = itId->first.Ptr;
#endif
		return true;
	}

	// we failed to find the sheet name in the sheetname map so see if the string is numeric
	if (sheetName.size()>1 && sheetName[0]=='#')
	{
		uint32 numericId;
		NLMISC::fromString((const char*)(sheetName.c_str()+1), numericId);
		if (NLMISC::toString("#%u",numericId)==sheetName)
		{
			_Id.Id= numericId;
			return true;
		}
	}

#ifdef NL_TEMP_YUBO_NO_SOUND_SHEET_ID
	if (a_NoSoundSheetId && sheetName.find(".sound") != std::string::npos)
	{
		std::string sheetNameLc = toLower(sheetName);
		std::map<std::string, uint32>::iterator it = _DevSheetNameToId.find(sheetNameLc);
		if (it == _DevSheetNameToId.end())
		{
			// nldebug("SHEETID: Creating a temporary sheet id for '%s'", sheetName.c_str());
			_DevSheetIdToName[0].push_back(sheetName);
			_Id.IdInfos.Type = a_NoSoundSheetType;
			_Id.IdInfos.Id = _DevSheetIdToName[0].size() - 1;
			_DevSheetNameToId[sheetNameLc] = _Id.Id;
			return true;
		}
		_Id.Id = it->second;
		return true;
	}
#endif

	return false;
}