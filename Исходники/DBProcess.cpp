void TDBProcess::OnExecSQL(const ServiceIdentifier&sender,UserTransferMessage& utm)
{
	string sql = utm[_TagSql];
	string sourceName=utm[_TagSourceName];
	strarray result ;
	strarray fieldname;

	BaseFieldDescription *pField;
	int rowcount = 0;
	u32 fieldcount = 0;
	bool	tryconnect	= false;

	utm.setRes(utm.getReq());
	utm.setMessageId(_ResExecSQL);
	PrintLog("RECV ReqExecSQL  sql = %s \n",sql.c_str() );

	if(!PreExecSQL(sender,utm, sql ) )
	{
		PrintLog("Check SQL Statement Error\n");
		return;	
	}
	try 
	{
		m_pDbQuery->command(sql);
		for(u32 i= 1 ; i <= m_pDbQuery->outputCount() ; i++)
		{
			m_pDbQuery->registerOutParam(i,FT_STRING);
		}
		PrintLog("Debug DO ExecSQL\n");
		m_pDbQuery->execute();
		PrintLog("Debug Finish ExecSQL\n");
		fieldcount = (u32) m_pDbQuery->fieldCount();
		utm[_TagFieldCount] = fieldcount;
		while ( !m_pDbQuery->eof())
		{
			rowcount++;
			m_pDbQuery->fetchNext();
			for(u32 i= 0 ; i < fieldcount ; i++)
				result.push_back( m_pDbQuery->getFieldByColumn(i)->asString());
		}
		if( 0 == rowcount )
		{
			for(u32 i=1; i <= m_pDbQuery->outputCount() ; i++ )
				result.push_back(m_pDbQuery->getOutParamByIndex(i)->asString());
			utm[_TagFieldCount] = (u32) m_pDbQuery->outputCount();
		}
		utm[_TagResult] = result;
		if( fieldcount )
		{
			for(u32 i = 0; i< fieldcount ; i++)
			{
				pField = m_pDbQuery->getFieldInfoByColumn(i);
				if( pField)
					fieldname.push_back(pField->name());
			}
		}
		utm[_TagFieldName] = fieldname;
	}
#ifdef _DB_ORACLE_ 
		catch( BaseException &err )
	{		
		Service::printConsole(cacti::LogLevel::FATAL, "%s %s\n",err.name.c_str(),err.description.c_str());
		utm.setReturn(ERR_DBS_ERROR);
		PrintLog("SEND ResExecSQL  failed, Exec SQL %s %s\n",
			err.name.c_str(),err.description.c_str());
		errProcess(err,sourceName);
		m_rowCount = 0;
		m_owner->postMessage(sender, utm);
		return ;
	}
#endif
#ifdef _DB_SYBASE_ 
	catch( BaseException &err )
	{
		if ( utm.getReturn() == 0 ){
			//	check the error information.
			//	if the communication is lost, reconnect it.
			if ( err.state == "08S01" || err.state == "HY000"){
				tryconnect	= true;
			};
		};		
		if ( ! tryconnect ){
			Service::printConsole(cacti::LogLevel::FATAL, "%s %s\n",err.name.c_str(),err.description.c_str());
			utm.setReturn(ERR_DBS_ERROR);
			PrintLog("SEND ResExecSQL  failed, Exec SQL %s %s\n",
				err.name.c_str(),err.description.c_str());
			errProcess(err,sourceName);
			m_owner->postMessage(sender, utm);
			return ;
		}
	}
#endif
#ifdef FOR_ODBC 
		catch( BaseException &err )
		{
			if ( utm.getReturn() == 0 ){
				//	check the error information.
				//	if the communication is lost, reconnect it.
				if ( err.state == "08S01" || err.state == "HY000"){
					tryconnect	= true;
				};
			};		
			if ( ! tryconnect ){
				Service::printConsole(cacti::LogLevel::FATAL, "%s %s\n",err.name.c_str(),err.description.c_str());
				utm.setReturn(ERR_DBS_ERROR);
				PrintLog("SEND ResExecSQL  failed, Exec SQL %s %s\n",
					err.name.c_str(),err.description.c_str());
				errProcess(err,sourceName);
				m_owner->postMessage(sender, utm);
				return ;
			}
		}
	if ( tryconnect ){
		ODBCQuery*	oq	= (ODBCQuery*)m_pDbQuery;
		try{
			oq->getParentConnection()->_odbcReconnect( oq->getIndex() );
		}
		catch( BaseException& err ){
			Service::printConsole(cacti::LogLevel::FATAL, "%s %s\n",err.name.c_str(),err.description.c_str());
			utm.setReturn(ERR_DBS_ERROR);
			PrintLog("SEND ResExecSQL  failed, Exec SQL %s %s\n",
				err.name.c_str(),err.description.c_str());
			errProcess(err,sourceName);
			m_owner->postMessage(sender, utm);
			return ;
		};
		utm.setMessageId( _ReqExecSQL );
		utm.setReturn( utm.getReturn() + 1 );
		Process( utm );
		return;
	};
	utm.setReturn( 0 );
#endif

	PrintLog("SEND ResExecSQL  fieldcount =%d, rowcount=%d\n",fieldcount,rowcount);
	m_owner->postMessage(sender, utm);

	return;
}