void CHelperManager::ProcessMessage_Invite_REQ_fromHELPER(playerCharacter_t* pHelper)
{
	
	if(TRUE == IsBadWritePtr(pHelper,sizeof(playerCharacter_t)) 
		|| TRUE == IsBadReadPtr(pHelper,sizeof(playerCharacter_t)))
	{
	
	
		
		return;
	}


	
	if( tagHelper::tagMemberList::HELPER != pHelper->tHelper.List.mode)
	{
		SendMessage_Invite_Respond_toHelper(
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidMode );
			g_logSystem->Write("Fail_RegistrationRequest_invalidMode" );
		return ;
	}



	char cz_tempTakerName[NAMESTRING+1];
	strncpy(cz_tempTakerName,MSG_ReadString(),NAMESTRING);
	cz_tempTakerName[NAMESTRING]=NULL;

	int idx = GTH_FindPCByName(cz_tempTakerName);
	
	playerCharacter_t * pTaker=gcpTools->GetPlayerRecordPointer(idx);

	if(NULL == pTaker){
		SendMessage_Invite_Respond_toHelper(
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidUser);
			g_logSystem->Write("Fail_RegistrationRequest_invalidUser" );
		return;
	}
	
	
	if( tagHelper::tagMemberList::TAKER != pTaker->tHelper.List.mode)
	{
		SendMessage_Invite_Respond_toHelper(
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidTakerMode );
			g_logSystem->Write("Fail_RegistrationRequest_invalidMode" );
		return ;
	}

	
	if(pTaker->idx == pHelper->idx)
	{
		SendMessage_Invite_Respond_toHelper( 
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidUser);
		g_logSystem->Write("Fail_RegistrationRequest_invalidUser" );
		return;
	}


	
	if ( pHelper->tHelper.List.count > tagHelper::MAX_MEMBER)
	{
		SendMessage_Invite_Respond_toHelper( 
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidTakersCount);
			g_logSystem->Write("Fail_RegistrationRequest_invalidTakersCount" );
		return;
	}

	
	if(pTaker->tHelper.List.count >= tagHelper::MAX_Accept_HELPERS)
	{
		SendMessage_Invite_Respond_toHelper( 
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidHelperCount);
		g_logSystem->Write("Fail_RegistrationRequest_invalidHelperCount" );
		return;
	}

	if ( pHelper->worldIdx != pTaker->worldIdx )
	{
		SendMessage_Invite_Respond_toHelper( 
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invalidWorldIndex);
			g_logSystem->Write("Fail_RegistrationRequest_invalidWorldIndex" );
		return ;
	}

	if(TRUE == isMyChild(pHelper,pTaker->name))
	{
		SendMessage_Invite_Respond_toHelper(
			pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Fail_RegistrationRequest_invaliChild);
			g_logSystem->Write("Fail_RegistrationRequest_invaliChild" );
		return ;
	}



	strncpy(pTaker->HelperAdd.RequestPlayer.Name,pHelper->name,NAMESTRING);
	pTaker->HelperAdd.RequestPlayer.Name[NAMESTRING]=NULL;
	pTaker->HelperAdd.RequestPlayer.pcIdx=pHelper->idx;


	SendMessage_Invite_Respond_toHelper( 
		pHelper,tagHelperPacket_SC_INVITE_RES_toHELPER::Ready_Registration);
	
	ShowLogInfo("Helper_Invite_Suggest: name:%s,level:%d ",pHelper->name,pHelper->level);
	
	SendMessage_Invite_Request_toTaker( pTaker,pHelper->name);
	ShowLogInfo("Helper_Invite_Suggest: name:%s,level:%d ",pTaker->name,pTaker->level);
}