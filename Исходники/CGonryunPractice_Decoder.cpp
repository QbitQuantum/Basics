void CGonryunPractice_Decoder::
recPaketProcces_BATTLE_PRACTICE_BATTINGTRADE_OK(playerCharacter_t* pPlayer)
{
	if((TRUE == IsBadWritePtr(pPlayer,sizeof(playerCharacter_t))) || 
	   (TRUE == IsBadReadPtr(pPlayer,sizeof(playerCharacter_t)))) {
		
		return;
	}
	
	int TargetIdx = MSG_ReadShort();
	playerCharacter_t* pTargetPlayer= gcpTools->GetPlayerRecordPointer(TargetIdx);
	
	if(NULL == pTargetPlayer) {
	
		GTH_DisconnectPlayer(pPlayer,FALSE);
		return;	
	}

	pPlayer->GonryunBattlePractice.bBattingOkSignal = TRUE;
	m_cpVirtualEncoder->SendMessage_BattingTrade_OkBatting( pPlayer, TRUE );
	m_cpVirtualEncoder->SendMessage_BattingTrade_OkBatting( pTargetPlayer, FALSE );
	
}