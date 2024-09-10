// Save party to mysql
int inter_party_tosql(struct party *p, int flag, int index)
{
	// 'party' ('party_id','name','exp','item','leader_id','leader_char')
	char esc_name[NAME_LENGTH*2+1];// escaped party name
	int party_id;

	if( p == NULL || p->party_id == 0 )
		return 0;
	party_id = p->party_id;

#ifdef NOISY
	ShowInfo("Save party request ("CL_BOLD"%d"CL_RESET" - %s).\n", party_id, p->name);
#endif
	Sql_EscapeStringLen(sql_handle, esc_name, p->name, strnlen(p->name, NAME_LENGTH));

#ifndef TXT_SQL_CONVERT
	if( flag & PS_BREAK )
	{// Break the party
		// we'll skip name-checking and just reset everyone with the same party id [celest]
		if( SQL_ERROR == Sql_Query(sql_handle, "UPDATE `%s` SET `party_id`='0' WHERE `party_id`='%d'", char_db, party_id) )
			Sql_ShowDebug(sql_handle);
		if( SQL_ERROR == Sql_Query(sql_handle, "DELETE FROM `%s` WHERE `party_id`='%d'", party_db, party_id) )
			Sql_ShowDebug(sql_handle);
		//Remove from memory
		idb_remove(party_db_, party_id);
		return 1;
	}
#endif //TXT_SQL_CONVERT
	if( flag & PS_CREATE )
	{// Create party
#ifndef TXT_SQL_CONVERT
		if( SQL_ERROR == Sql_Query(sql_handle, "INSERT INTO `%s` "
			"(`name`, `exp`, `item`, `leader_id`, `leader_char`) "
			"VALUES ('%s', '%d', '%d', '%d', '%d')",
			party_db, esc_name, p->exp, p->item, p->member[index].account_id, p->member[index].char_id) )
		{
			Sql_ShowDebug(sql_handle);
			return 0;
		}
		party_id = p->party_id = (int)Sql_LastInsertId(sql_handle);
#else
		//During conversion, you want to specify the id, and allow overwriting
		//(in case someone is re-running the process.

		if( SQL_ERROR == Sql_Query(sql_handle, "REPLACE INTO `%s` "
			"(`party_id`, `name`, `exp`, `item`, `leader_id`, `leader_char`) "
			"VALUES ('%d', '%s', '%d', '%d', '%d', '%d')",
			party_db, p->party_id, esc_name, p->exp, p->item, p->member[index].account_id, p->member[index].char_id) )
		{
			Sql_ShowDebug(sql_handle);
			return 0;
		}
#endif
	}

#ifndef TXT_SQL_CONVERT
	if( flag & PS_BASIC )
	{// Update party info.
		if( SQL_ERROR == Sql_Query(sql_handle, "UPDATE `%s` SET `name`='%s', `exp`='%d', `item`='%d' WHERE `party_id`='%d'",
			party_db, esc_name, p->exp, p->item, party_id) )
			Sql_ShowDebug(sql_handle);
	}

	if( flag & PS_LEADER )
	{// Update leader
		if( SQL_ERROR == Sql_Query(sql_handle, "UPDATE `%s`  SET `leader_id`='%d', `leader_char`='%d' WHERE `party_id`='%d'",
			party_db, p->member[index].account_id, p->member[index].char_id, party_id) )
			Sql_ShowDebug(sql_handle);
	}
	
	if( flag & PS_ADDMEMBER )
	{// Add one party member.
		if( SQL_ERROR == Sql_Query(sql_handle, "UPDATE `%s` SET `party_id`='%d' WHERE `account_id`='%d' AND `char_id`='%d'",
			char_db, party_id, p->member[index].account_id, p->member[index].char_id) )
			Sql_ShowDebug(sql_handle);
	}

	if( flag & PS_DELMEMBER )
	{// Remove one party member.
		if( SQL_ERROR == Sql_Query(sql_handle, "UPDATE `%s` SET `party_id`='0' WHERE `party_id`='%d' AND `account_id`='%d' AND `char_id`='%d'",
			char_db, party_id, p->member[index].account_id, p->member[index].char_id) )
			Sql_ShowDebug(sql_handle);
	}
#endif //TXT_SQL_CONVERT
	if( save_log )
		ShowInfo("Party Saved (%d - %s)\n", party_id, p->name);
	return 1;
}