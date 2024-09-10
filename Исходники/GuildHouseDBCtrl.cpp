void CGuildHouseDBCtrl::SendGuildHouse( DPID dpId )
{
	if( !GuildHouseMng->IsEmpty() )
	{
		BEFORESENDDUAL( ar, PACKETTYPE_GUILDHOUSE_LOAD, DPID_UNKNOWN, DPID_UNKNOWN );
		GuildHouseMng->Serialize( ar );
		SEND( ar, CDPTrans::GetInstance(), dpId );
	}
}