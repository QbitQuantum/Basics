void DryonBot::onPrivMsg(const string &sender, const string &dest, const string &msg)
{
	vector<string> msg_parts;
	Tokenize(msg, msg_parts, " ");
	user_Info *usr;
	GET_USR(usr, sender);

	const string &command= msg_parts[0].substr(1);

	// load user flags from userfile.txt
	checkUserFlags(usr, dest);

	if( command=="reload" )
	{
		/* if user has owner flag then reload all config files */
		if( usr->hasFlag(USRLVL_OWNER) )
		{
			// force update of user flags
			for(userDataTypeIter it= userData.begin(); it!= userData.end(); it++)
				(*it).second.flags_set= false;

			servers.loadFromFile("servers.txt");
			userfile.saveFile();
			userfile.readUserFile();
			cfg.readFile();
			PMgr.loadScriptsFromCfg(cfg);
		}
		return;
	}
	// user list
	else if( command=="userlist" )
	{
		if( usr->hasAccount() && usr->hasFlag(USRLVL_OWNER) )
		{
			map<string, UsersData> &ulist= userfile.getAccessList();
			notice(sender, "User list: %d entries", ulist.size());
			notice(sender, "-------- Start (Show accounts and global flags) --------");

			for(map<string, UsersData>::iterator it= ulist.begin(); it!=ulist.end(); it++)
			{
				string what= it->first;
				if( (what[0]=='a') && (what[1]=='/') )
				{
					what= '#' + what.substr(2);
				}

				notice(sender, "%15s %35s %5s", it->second.name.c_str(), what.c_str(), it->second.flags.c_str());
			}

			notice(sender, "--------  End  --------");
		}
		return;
	}
	else if( command == "showflags" )
	{
		if( usr->hasAccount() && usr->hasFlag(USRLVL_MASTER) )
		{
			map<string, UsersData> &ulist= userfile.getAccessList();
			string &chan= msg_parts[1];
			notice(sender, "User list for %s", chan.c_str());

			for(map<string, UsersData>::iterator it= ulist.begin(); it!=ulist.end(); it++)
			{
				string what= it->first;
				UsersData &tmp= it->second;

				for(map<string,string>::iterator it2= tmp.channel_flags.begin(); it2 != tmp.channel_flags.end(); it2++)
				{
					if( it2->first == chan )
						notice(sender, "%15s %5s", it->second.name.c_str(), it2->second.c_str());
				}
			}
			notice(sender, "--------  End  --------");
		}
	}
	// return a list of loaded plugins
	else if( command=="scripts" )
	{
		uint count= PMgr.getPluginCount();
		for(int i= count-1; i>= 0; i--)
		{
			notice(sender, "%2d ) %s\n", i, PMgr.getPlugin(i)->getPath());
		}
	}
	else if( command=="quit" )
	{
		if( usr->hasFlag(USRLVL_OWNER) )
		{
			quit("exit requested");
		}
		return;
	}
	else if( command=="help" )
	{
		if( usr->hasAccount() )
		{
			notice(sender, "Core commands:");
			if( usr->hasFlag(USRLVL_OWNER) )
			{
				notice(sender, ":reload - reload all plugins and config file");
				notice(sender, ":userlist - display user list");
			}

			notice(sender, ":help - display this :<");
			notice(sender, ":scripts - display list of currently loaded scripts");
			notice(sender, "---");
			PMgr.sendCommandsList(sender, dest, usr);
			//return;
		}
	}
	else if( command=="nfo" )
	{
		if( msg_parts.size() == 1 )
		{
			Output("Nick: '%s'\n", bot_data.nick.c_str());
			Output("Host: '%s'\n", bot_data.full_host.c_str());
			Output("Auth: '%s'\n", bot_data.auth.c_str());
		}
		else if( msg_parts.size() >= 2 )
		{
			user_Info *u= getUserData(msg_parts[1]);
			if( u!=NULL )
			{
				Output("Nick: '%s'\n", u->nick.c_str());
				Output("Host: '%s'\n", u->full_host.c_str());
				Output("Auth: '%s'\n", u->auth.c_str());
			}
			else
			{
				notice(sender, "Nick unknown: %s", msg_parts[1].c_str());
			}
		}
	}
	else
	{
		chan_Info *chan;
		if( isChannelName(dest) )
		{
			GET_CHAN(chan, dest);
			PMgr.callEvent("event_onPrivMsg", "ucv", usr, chan, &msg_parts);
			PMgr.callCommand(usr, (dummy_Info*)chan, msg_parts);
		}
		else
		{
			PMgr.callEvent("event_onPrivMsg", "uuv", usr, &bot_data, &msg_parts);
			PMgr.callCommand(usr, (dummy_Info*)&bot_data, msg_parts);
		}
	}
}