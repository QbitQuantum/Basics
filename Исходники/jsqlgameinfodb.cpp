JCode JSQLGameInfoDB::insertGameInfo(const JGameInfo& gameInfo)
{
	QSqlQuery query;
	PREPARE( query ,
			" INSERT INTO gameinfo "
			" (game_id,game_name,version,author_id,runner_id,intro,server_id,download_url) "
			" values(:gameID,:gameName,:version,:authorID,:runnerID,:introduction,:serverID,:downUrl) ",
			EPrepareFailed );
	
	query.bindValue(":gameName", gameInfo.getName());
	query.bindValue(":version", gameInfo.getVersion().getData());
	query.bindValue(":authorID", gameInfo.getAuthor());
	query.bindValue(":runnerID", gameInfo.getRunner());
	query.bindValue(":introduction", gameInfo.getIntroduction());
	query.bindValue(":serverID", gameInfo.getServerId());
	query.bindValue(":downUrl", gameInfo.getDownloadUrl());
	query.bindValue(":gameID", gameInfo.getGameId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}