/*!
This ends the casting of a specified character.
If the second parameter is not false, it 
displays the fizzle animation and the fizzle sound.
*/
void cNewMagic::disturb( P_CHAR pMage, bool fizzle, INT16 chance )
{
	if( !pMage->isCasting() )
		return;

	pMage->setCasting( false );
	pMage->setFrozen( false );

	// Stop the repeating animation and the endspell thing
	//pMage->stopRepeatedAction();

	cBaseChar::EffectContainer effects = pMage->effects();
	for( INT32 i = 0; i < effects.size(); ++i )
	{
		if( effects[i]->objectID() == "endcasting" )
		{
			// We found our effect
			TempEffects::instance()->erase( effects[i] );
			pMage->removeEffect( effects[i] );
			break;
		}
	}
	
	if( fizzle )
	{
		pMage->effect( 0x3735, 1, 30 );
		pMage->soundEffect( 0x005C );

		if( pMage->objectType() == enPlayer )
		{
			P_PLAYER pp = dynamic_cast<P_PLAYER>(pMage);
			if( pp->socket() )
				pp->socket()->sysMessage( tr( "Your spell fizzles." ) );
		}
	}
}