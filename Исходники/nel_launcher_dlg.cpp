void CNelLauncherDlg::clickedConnect()
{
	pbConnect->setEnabled(FALSE);
	TShardList shards = m_Connection.getShards();
	nlinfo("a shard was double clicked. row selected: %d", tblShardList->currentRow());
	if(tblShardList->currentRow() < 0)
	{
		QMessageBox::about(this, "Connect to Shard", "Please, select a shard and then press Connect button.");
	}

	pbConnect->setEnabled(FALSE);

	CShard shard = shards[tblShardList->currentRow()];

	if(!shard.Online)
	{
		QMessageBox::about(this, "Connect to Shard", "You can't connect to an offline shard (error code 15)");
	}

	// TODO implement the patching stuff.
	//if(!shard.Version.empty() && shard.Version != getVersion())

	std::string cookie, addr;
	std::string res = m_Connection.selectShard(shard.ShardId, cookie, addr);

	if(res.empty())
	{
		nlinfo("successfully connected to shard, launch client.");
		std::string rapp = ConfigFile.getVar("Application").asString(1);
		std::string dir = ConfigFile.getVar("Application").asString(2);

		std::vector<std::string> vargs;
		//const char *args[50];
		vargs.push_back(rapp);
		vargs.push_back(cookie);
		vargs.push_back(addr);

		// Create the ArgV from a vector.
		uint nArgs = vargs.size();
		char **buf = new char*[nArgs + 1];
		for(uint i=0; i<nArgs; ++i)
		{
			buf[i] = new char(vargs[i].size() + 1);
			strcpy(buf[i], vargs[i].c_str());
			//strcat(buf[i], '\0');
		}
		buf[nArgs]=NULL;

		if(!dir.empty())
			_chdir(dir.c_str());

		if(_execvp(rapp.c_str(), buf) == -1)
		{
			QMessageBox::about(this, "Launch Client", "Can't execute the game (error code 17)");
			pbConnect->setEnabled(TRUE);
		}
		else
		{
			for(uint i=0; i<nArgs; ++i)
				delete [] buf[i];
			delete buf;
			exit(0);
		}
	}
	else
	{
		QMessageBox::about(this, "Connect to Shard", res.c_str());
		pbConnect->setEnabled(TRUE);
	}
}