bool SPostgres::Execute(SString sql)
{
	LOGBASEDEBUG("into SPostgres::Execute(%s)",sql.data());
	sql = sql.replace("\\","\\\\");//postgres数据库SQL中\为转义符
	if(m_pConn == NULL)
	{
		LOGWARN("m_pConn is NULL is SPostgres::Execute, Connect it at first!");
		Connect();
		if(m_pConn == NULL)
		{
			LOGWARN("m_pConn is NULL is SPostgres::Execute, Connect error!");
			return false;
		}
	}
	 
	PGresult *pRes = PQexec(m_pConn,sql.data());
	if(PQresultStatus(pRes) != PGRES_COMMAND_OK )
	{
		SString err;
		err.sprintf("Error in SPostgres::Execute(%s), err=%s",sql.data(),PQresultErrorMessage(pRes));
		LOGERROR("%s",err.data());
		if(pRes != NULL)
			PQclear(pRes);
		if(TestConnect() == true)//连接可用
			return false;

		//失败自动重连一次数据库
		if(!Reconnect())
			return false;//连接失败
		pRes = PQexec(m_pConn,sql.data());
		if(PQresultStatus(pRes)!=PGRES_COMMAND_OK) 
		{
			LOGERROR("Error in SPostgres::Execute(%s), err=%s",sql.data(),PQresultErrorMessage(pRes));
			if(pRes != NULL)
				PQclear(pRes);
			return false;
		}
	}
	PQclear(pRes);
	return true;
}