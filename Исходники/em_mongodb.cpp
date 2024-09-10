int em_mongodb::setvalue(std::string dbcoll,mongo::Query cond,BSONObj valObj,bool flag)	
{
	int ret = MDB_FAIL_SET;
	DBClientConnection* pconn = getConn();
	if(!pconn)
		return ret;

	pconn->update(dbcoll,cond,valObj,flag);
	std::string errmsg = pconn->getLastError();
	std::cout << "em_mongodb::setvalue: " << errmsg << std::endl;
	if(errmsg.empty())
		ret = MDB_RET_SUCCESS;
	boost::mutex::scoped_lock lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
	return ret;
}			