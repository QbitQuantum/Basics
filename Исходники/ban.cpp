bool IOBanSQL::saveBans(const std::string& identifier, const Ban& banclass)
{
	Database db;
	if(!db.connect(m_db.c_str(), m_host.c_str(), m_user.c_str(), m_pass.c_str())){
		return false;
	}
	
	DBQuery query;

	query << "BEGIN;";
	if(!db.executeQuery(query))
		return false;

	query << "DELETE FROM bans;";
	if(!db.executeQuery(query))
		return false;
	
	uint32_t currentTime = std::time(NULL);
	//save ip bans
	bool executeQuery = false;
	query.reset();
	query << "INSERT INTO `bans` (`type` , `ip` , `mask`, `time`) VALUES ";
	for(IpBanList::const_iterator it = banclass.ipBanList.begin(); it !=  banclass.ipBanList.end(); ++it){
		if(it->time > currentTime){
			executeQuery = true;
			query << query.getSeparator() << "(1," << it->ip << "," << it->mask << 
				"," << it->time << ")";
		}
	}

	if(executeQuery){
		if(!db.executeQuery(query))
			return false;
	}

	//save player bans
	executeQuery = false;
	query.reset();
	query << "INSERT INTO `bans` (`type` , `player` , `time`) VALUES ";
	for(PlayerBanList::const_iterator it = banclass.playerBanList.begin(); it !=  banclass.playerBanList.end(); ++it){
		if(it->time > currentTime){
			executeQuery = true;
			query << query.getSeparator() << "(2," << it->id << "," << it->time << ")";
		}
	}

	if(executeQuery){
		if(!db.executeQuery(query))
			return false;
	}

	//save account bans
	executeQuery = false;
	query.reset();
	query << "INSERT INTO `bans` (`type` , `account` , `time`) VALUES ";
	for(AccountBanList::const_iterator it = banclass.accountBanList.begin(); it != banclass.accountBanList.end(); ++it){
		if(it->time > currentTime){
			executeQuery = true;
			query << query.getSeparator() << "(3," << it->id << "," << it->time << ")";
		}
	}

	if(executeQuery){
		if(!db.executeQuery(query))
			return false;
	}
	
	query.reset();
	query << "COMMIT;";	
	if(!db.executeQuery(query))
		return false;
	
	return true;
}