void NPC::Killed(Damage &fatal_blow)
{
	m_destiny->Stop();

	DynamicSystemEntity::Killed(fatal_blow);
	
	SystemEntity *killer = fatal_blow.source;
	Client* client = m_services.entity_list.FindByShip( killer->Item()->ownerID() );
	if( !killer->IsClient() )
	{
		if( client != NULL )
		{
			killer = static_cast<SystemEntity*>(client);
		}
	}
	else
	{
		client = killer->CastToClient();
	}
	//TODO: drop loot.
	//_DropLoot(fatal_blow.source);
	_DropLoot(killer);
	
	//award kill bounty.
	//_AwardBounty(fatal_blow.source);
	_AwardBounty(killer);
	
	//TODO: award status changes. (entitySecurityStatusKillBonus)
	client->GetChar()->addSecurityRating( m_self->GetAttribute(AttrEntitySecurityStatusKillBonus).get_float() );

	//notify our spawner that we are gone.
	if(m_spawner != NULL) {
	  m_spawner->SpawnDepoped(m_self->itemID());
	}
	
	m_system->RemoveNPC(this);
}