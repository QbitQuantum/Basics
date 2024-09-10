INT SystemUser::getUserID(LPCSTR userName)
{
	String sql;
	sql.printf("SELECT user_id FROM tb_user WHERE user_name='%s';",userName);
	SQRes res = m_db->exec(sql);
	if(res->getRows() == 0)
		return 0;
	return atoi(res->getColumn(0));
}