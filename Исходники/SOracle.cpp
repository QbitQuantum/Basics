bool SOracle::UpdateLobFromFile(SString sTable,SString sLobField,SString sWhere,SString sFile) 
{

	//6.执行一个带有CLOB/BLOB的Update语句,将文件内容保存到CLOB/BLOB字段中
	SString sql;
	sql.sprintf("update %s set %s=:1 where %s", sTable.data(),sLobField.data(),sWhere.data());
	LOGDEBUG("文件内容保存到CLOB/BLOB字段中:%s",sql.data());
	string sSql(sql.data());
	string filename(sFile.data());
	long gg;
	OdbParamArray oa;
	OdbParam* pParam=new OdbParam;
	pParam->wType=SQLT_CLOB;  
	pParam->BindPos=1; 
	oa.paParams.push_back(pParam);
	m_pConn->SqlPrepare(sSql,gg);   
	m_pConn->BindParam(gg,oa);
	m_pConn->WriteLobFromFile(pParam,filename);
	m_pConn->SqlExecuteWithParam(gg); 
	m_pConn->Commit(); 
	m_pConn->FreeParams(gg,oa);
	return true;
}