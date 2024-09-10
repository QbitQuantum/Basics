void ConnectionsConfigWidget::testConnection(void)
{
	Connection conn;
	Messagebox msg_box;
	attribs_map srv_info;

	try
	{
		this->configureConnection(&conn);
		conn.connect();
		srv_info=conn.getServerInfo();
		msg_box.show(trUtf8("Success"),
					 PgModelerUiNS::formatMessage(trUtf8("Connection successfuly stablished!\n\nServer details:\n\nPID: `%1'\nProtocol: `%2'\nVersion: `%3'"))
					 .arg(srv_info[Connection::SERVER_PID])
				.arg(srv_info[Connection::SERVER_PROTOCOL])
				.arg(srv_info[Connection::SERVER_VERSION]), Messagebox::INFO_ICON);
	}
	catch(Exception &e)
	{
		throw Exception(e.getErrorMessage(),e.getErrorType(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
	}
}