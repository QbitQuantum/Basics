	void handle_file(const boost::system::error_code& e, connection_ptr conn,string nameFile)	{
		if (!e)	{	// lecture des informations
			db::DataBaseType<MySQL> dbMySQL("root", "", "mycloud") ;
			string idMySQL;
			for(model::info i : infos)	{
				idMySQL = dbMySQL.getUser(i.getAddressMail(), i.getPwd());
			}
			File file("/home/steven/server/",idMySQL);
			std::string path="/home/steven/client/" + idMySQL + nameFile;
			std::stringstream data_in;
			data_in << readMap(path.c_str());
			conn->socket().send(boost::asio::buffer(data_in.str()));
		}
	}