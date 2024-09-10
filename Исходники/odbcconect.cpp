int DBConnection::checkConnectionState(){
	int closed;
	int res =  SQLGetConnectAttr(dbc,SQL_ATTR_CONNECTION_DEAD,(SQLPOINTER)&closed, SQL_IS_INTEGER,0);
	return res;
}