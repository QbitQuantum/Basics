// Checked: 2011-05-26 (RLVa-1.3.1c) | Added: RLVa-1.3.1c
void RlvFloaterBehaviours::onBtnCopyToClipboard() const
{
	std::ostringstream strRestrictions;

	strRestrictions << RlvStrings::getVersion() << "\n";

	const RlvHandler::rlv_object_map_t* pObjects = gRlvHandler.getObjectMap();
	for (RlvHandler::rlv_object_map_t::const_iterator itObj = pObjects->begin(), endObj = pObjects->end(); itObj != endObj; ++itObj)
	{
		strRestrictions << "\n" << rlvGetItemNameFromObjID(itObj->first) << ":\n";

		const rlv_command_list_t* pCommands = itObj->second.getCommandList();
		for (rlv_command_list_t::const_iterator itCmd = pCommands->begin(), endCmd = pCommands->end(); itCmd != endCmd; ++itCmd)
		{
			std::string strOption; LLUUID idOption;
			if ( (itCmd->hasOption()) && (idOption.set(itCmd->getOption(), FALSE)) && (idOption.notNull()) )
			{
				LLAvatarName avName;
				if (gObjectList.findObject(idOption))
					strOption = rlvGetItemNameFromObjID(idOption, true);
				else if (LLAvatarNameCache::get(idOption, &avName))
					strOption = (!avName.getAccountName().empty()) ? avName.getAccountName() : avName.getDisplayName();
				else if (!gCacheName->getGroupName(idOption, strOption))
					strOption = itCmd->getOption();
			}

			strRestrictions << "  -> " << itCmd->asString();
			if ( (!strOption.empty()) && (strOption != itCmd->getOption()) )
				strRestrictions << "  [" << strOption << "]";
			if (RLV_RET_SUCCESS != itCmd->getReturnType())
				strRestrictions << "  (" << RlvStrings::getStringFromReturnCode(itCmd->getReturnType()) << ")";
			strRestrictions << "\n";
		}
	}

	LLWString wstrRestrictions = utf8str_to_wstring(strRestrictions.str());
	gClipboard.copyFromSubstring(wstrRestrictions, 0, wstrRestrictions.length());
}