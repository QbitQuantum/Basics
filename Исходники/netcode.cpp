void PlayerInfo(NodeID nid)
{
	Message msg;
	msg.push_back("PLAYERINFO");
	map<Player::Id,ObjectHandle>::iterator it;
	for (it = game.players.begin(); it != game.players.end(); ++it)
	{
		if (it->first == nodes[nid]) continue; // Don't send player his own info
		if (it->first == game.player->id)
			msg.push_back((long) tokenring->id());
		else
			msg.push_back((long) findNode(it->first));
		
		msg.push_back((string) *it->second);
	}
	SENDTO(nid, msg, true);
}