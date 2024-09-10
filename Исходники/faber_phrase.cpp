//-----------------------------------------------
// CFaberPhrase stop
//-----------------------------------------------
void CFaberPhrase::stop()
{
	H_AUTO(CFaberPhrase_stop);

	CCharacter* player = PlayerManager.getChar(_ActorRowId);
	if (!player)
		return;

	player->unlockFaberRms();
	player->clearCurrentAction();
	player->staticActionInProgress(false);
	player->sendCloseTempInventoryImpulsion();

	// set behaviour
	PHRASE_UTILITIES::sendUpdateBehaviour( _ActorRowId, MBEHAV::FABER_END );

	// send message
	PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "FABER_CANCEL");
} // stop //