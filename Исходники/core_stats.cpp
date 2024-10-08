void CommandStats::DoStats(char statschar, User* user, string_list &results)
{
	bool isPublic = ServerInstance->Config->UserStats.find(statschar) != std::string::npos;
	bool isRemoteOper = IS_REMOTE(user) && (user->IsOper());
	bool isLocalOperWithPrivs = IS_LOCAL(user) && user->HasPrivPermission("servers/auspex");

	if (!isPublic && !isRemoteOper && !isLocalOperWithPrivs)
	{
		ServerInstance->SNO->WriteToSnoMask('t',
				"%s '%c' denied for %s (%s@%s)",
				(IS_LOCAL(user) ? "Stats" : "Remote stats"),
				statschar, user->nick.c_str(), user->ident.c_str(), user->host.c_str());
		results.push_back("481 " + user->nick + " :Permission denied - STATS " + statschar + " requires the servers/auspex priv.");
		return;
	}

	ModResult MOD_RESULT;
	FIRST_MOD_RESULT(OnStats, MOD_RESULT, (statschar, user, results));
	if (MOD_RESULT == MOD_RES_DENY)
	{
		results.push_back("219 "+user->nick+" "+statschar+" :End of /STATS report");
		ServerInstance->SNO->WriteToSnoMask('t',"%s '%c' requested by %s (%s@%s)",
			(IS_LOCAL(user) ? "Stats" : "Remote stats"), statschar, user->nick.c_str(), user->ident.c_str(), user->host.c_str());
		return;
	}

	switch (statschar)
	{
		/* stats p (show listening ports) */
		case 'p':
		{
			for (std::vector<ListenSocket*>::const_iterator i = ServerInstance->ports.begin(); i != ServerInstance->ports.end(); ++i)
			{
				ListenSocket* ls = *i;
				std::string ip = ls->bind_addr;
				if (ip.empty())
					ip.assign("*");
				std::string type = ls->bind_tag->getString("type", "clients");
				std::string hook = ls->bind_tag->getString("ssl", "plaintext");

				results.push_back("249 "+user->nick+" :"+ ip + ":"+ConvToStr(ls->bind_port)+
					" (" + type + ", " + hook + ")");
			}
		}
		break;

		/* These stats symbols must be handled by a linking module */
		case 'n':
		case 'c':
		break;

		case 'i':
		{
			for (ClassVector::iterator i = ServerInstance->Config->Classes.begin(); i != ServerInstance->Config->Classes.end(); i++)
			{
				ConnectClass* c = *i;
				std::stringstream res;
				res << "215 " << user->nick << " I " << c->name << ' ';
				if (c->type == CC_ALLOW)
					res << '+';
				if (c->type == CC_DENY)
					res << '-';

				if (c->type == CC_NAMED)
					res << '*';
				else
					res << c->host;

				res << ' ' << c->config->getString("port", "*") << ' ';

				res << c->GetRecvqMax() << ' ' << c->GetSendqSoftMax() << ' ' << c->GetSendqHardMax()
					<< ' ' << c->GetCommandRate() << ' ' << c->GetPenaltyThreshold();
				if (c->fakelag)
					res << '*';
				results.push_back(res.str());
			}
		}
		break;

		case 'Y':
		{
			int idx = 0;
			for (ClassVector::iterator i = ServerInstance->Config->Classes.begin(); i != ServerInstance->Config->Classes.end(); i++)
			{
				ConnectClass* c = *i;
				results.push_back("215 "+user->nick+" i NOMATCH * "+c->GetHost()+" "+ConvToStr(c->limit ? c->limit : SocketEngine::GetMaxFds())+" "+ConvToStr(idx)+" "+ServerInstance->Config->ServerName+" *");
				results.push_back("218 "+user->nick+" Y "+ConvToStr(idx)+" "+ConvToStr(c->GetPingTime())+" 0 "+ConvToStr(c->GetSendqHardMax())+" :"+
						ConvToStr(c->GetRecvqMax())+" "+ConvToStr(c->GetRegTimeout()));
				idx++;
			}
		}
		break;

		case 'P':
		{
			unsigned int idx = 0;
			const UserManager::OperList& opers = ServerInstance->Users->all_opers;
			for (UserManager::OperList::const_iterator i = opers.begin(); i != opers.end(); ++i)
			{
				User* oper = *i;
				if (!oper->server->IsULine())
				{
					LocalUser* lu = IS_LOCAL(oper);
					results.push_back("249 " + user->nick + " :" + oper->nick + " (" + oper->ident + "@" + oper->dhost + ") Idle: " +
							(lu ? ConvToStr(ServerInstance->Time() - lu->idle_lastmsg) + " secs" : "unavailable"));
					idx++;
				}
			}
			results.push_back("249 "+user->nick+" :"+ConvToStr(idx)+" OPER(s)");
		}
		break;

		case 'k':
			ServerInstance->XLines->InvokeStats("K",216,user,results);
		break;
		case 'g':
			ServerInstance->XLines->InvokeStats("G",223,user,results);
		break;
		case 'q':
			ServerInstance->XLines->InvokeStats("Q",217,user,results);
		break;
		case 'Z':
			ServerInstance->XLines->InvokeStats("Z",223,user,results);
		break;
		case 'e':
			ServerInstance->XLines->InvokeStats("E",223,user,results);
		break;
		case 'E':
		{
			const SocketEngine::Statistics& stats = SocketEngine::GetStats();
			results.push_back("249 "+user->nick+" :Total events: "+ConvToStr(stats.TotalEvents));
			results.push_back("249 "+user->nick+" :Read events:  "+ConvToStr(stats.ReadEvents));
			results.push_back("249 "+user->nick+" :Write events: "+ConvToStr(stats.WriteEvents));
			results.push_back("249 "+user->nick+" :Error events: "+ConvToStr(stats.ErrorEvents));
			break;
		}

		/* stats m (list number of times each command has been used, plus bytecount) */
		case 'm':
			for (Commandtable::iterator i = ServerInstance->Parser->cmdlist.begin(); i != ServerInstance->Parser->cmdlist.end(); i++)
			{
				if (i->second->use_count)
				{
					/* RPL_STATSCOMMANDS */
					results.push_back("212 "+user->nick+" "+i->second->name+" "+ConvToStr(i->second->use_count));
				}
			}
		break;

		/* stats z (debug and memory info) */
		case 'z':
		{
			results.push_back("249 "+user->nick+" :Users: "+ConvToStr(ServerInstance->Users->GetUsers().size()));
			results.push_back("249 "+user->nick+" :Channels: "+ConvToStr(ServerInstance->GetChans().size()));
			results.push_back("249 "+user->nick+" :Commands: "+ConvToStr(ServerInstance->Parser->cmdlist.size()));

			float kbitpersec_in, kbitpersec_out, kbitpersec_total;
			char kbitpersec_in_s[30], kbitpersec_out_s[30], kbitpersec_total_s[30];

			SocketEngine::GetStats().GetBandwidth(kbitpersec_in, kbitpersec_out, kbitpersec_total);

			snprintf(kbitpersec_total_s, 30, "%03.5f", kbitpersec_total);
			snprintf(kbitpersec_out_s, 30, "%03.5f", kbitpersec_out);
			snprintf(kbitpersec_in_s, 30, "%03.5f", kbitpersec_in);

			results.push_back("249 "+user->nick+" :Bandwidth total:  "+ConvToStr(kbitpersec_total_s)+" kilobits/sec");
			results.push_back("249 "+user->nick+" :Bandwidth out:    "+ConvToStr(kbitpersec_out_s)+" kilobits/sec");
			results.push_back("249 "+user->nick+" :Bandwidth in:     "+ConvToStr(kbitpersec_in_s)+" kilobits/sec");

#ifndef _WIN32
			/* Moved this down here so all the not-windows stuff (look w00tie, I didn't say win32!) is in one ifndef.
			 * Also cuts out some identical code in both branches of the ifndef. -- Om
			 */
			rusage R;

			/* Not sure why we were doing '0' with a RUSAGE_SELF comment rather than just using RUSAGE_SELF -- Om */
			if (!getrusage(RUSAGE_SELF,&R))	/* RUSAGE_SELF */
			{
				results.push_back("249 "+user->nick+" :Total allocation: "+ConvToStr(R.ru_maxrss)+"K");
				results.push_back("249 "+user->nick+" :Signals:          "+ConvToStr(R.ru_nsignals));
				results.push_back("249 "+user->nick+" :Page faults:      "+ConvToStr(R.ru_majflt));
				results.push_back("249 "+user->nick+" :Swaps:            "+ConvToStr(R.ru_nswap));
				results.push_back("249 "+user->nick+" :Context Switches: Voluntary; "+ConvToStr(R.ru_nvcsw)+" Involuntary; "+ConvToStr(R.ru_nivcsw));

				char percent[30];

				float n_elapsed = (ServerInstance->Time() - ServerInstance->stats->LastSampled.tv_sec) * 1000000
					+ (ServerInstance->Time_ns() - ServerInstance->stats->LastSampled.tv_nsec) / 1000;
				float n_eaten = ((R.ru_utime.tv_sec - ServerInstance->stats->LastCPU.tv_sec) * 1000000 + R.ru_utime.tv_usec - ServerInstance->stats->LastCPU.tv_usec);
				float per = (n_eaten / n_elapsed) * 100;

				snprintf(percent, 30, "%03.5f%%", per);
				results.push_back("249 "+user->nick+" :CPU Use (now):    "+percent);

				n_elapsed = ServerInstance->Time() - ServerInstance->startup_time;
				n_eaten = (float)R.ru_utime.tv_sec + R.ru_utime.tv_usec / 100000.0;
				per = (n_eaten / n_elapsed) * 100;
				snprintf(percent, 30, "%03.5f%%", per);
				results.push_back("249 "+user->nick+" :CPU Use (total):  "+percent);
			}
#else
			PROCESS_MEMORY_COUNTERS MemCounters;
			if (GetProcessMemoryInfo(GetCurrentProcess(), &MemCounters, sizeof(MemCounters)))
			{
				results.push_back("249 "+user->nick+" :Total allocation: "+ConvToStr((MemCounters.WorkingSetSize + MemCounters.PagefileUsage) / 1024)+"K");
				results.push_back("249 "+user->nick+" :Pagefile usage:   "+ConvToStr(MemCounters.PagefileUsage / 1024)+"K");
				results.push_back("249 "+user->nick+" :Page faults:      "+ConvToStr(MemCounters.PageFaultCount));
			}

			FILETIME CreationTime;
			FILETIME ExitTime;
			FILETIME KernelTime;
			FILETIME UserTime;
			LARGE_INTEGER ThisSample;
			if(GetProcessTimes(GetCurrentProcess(), &CreationTime, &ExitTime, &KernelTime, &UserTime) &&
				QueryPerformanceCounter(&ThisSample))
			{
				KernelTime.dwHighDateTime += UserTime.dwHighDateTime;
				KernelTime.dwLowDateTime += UserTime.dwLowDateTime;
				double n_eaten = (double)( ( (uint64_t)(KernelTime.dwHighDateTime - ServerInstance->stats->LastCPU.dwHighDateTime) << 32 ) + (uint64_t)(KernelTime.dwLowDateTime - ServerInstance->stats->LastCPU.dwLowDateTime) )/100000;
				double n_elapsed = (double)(ThisSample.QuadPart - ServerInstance->stats->LastSampled.QuadPart) / ServerInstance->stats->QPFrequency.QuadPart;
				double per = (n_eaten/n_elapsed);

				char percent[30];

				snprintf(percent, 30, "%03.5f%%", per);
				results.push_back("249 "+user->nick+" :CPU Use (now):    "+percent);

				n_elapsed = ServerInstance->Time() - ServerInstance->startup_time;
				n_eaten = (double)(( (uint64_t)(KernelTime.dwHighDateTime) << 32 ) + (uint64_t)(KernelTime.dwLowDateTime))/100000;
				per = (n_eaten / n_elapsed);
				snprintf(percent, 30, "%03.5f%%", per);
				results.push_back("249 "+user->nick+" :CPU Use (total):  "+percent);
			}
#endif
		}
		break;

		case 'T':
		{
			results.push_back("249 "+user->nick+" :accepts "+ConvToStr(ServerInstance->stats->statsAccept)+" refused "+ConvToStr(ServerInstance->stats->statsRefused));
			results.push_back("249 "+user->nick+" :unknown commands "+ConvToStr(ServerInstance->stats->statsUnknown));
			results.push_back("249 "+user->nick+" :nick collisions "+ConvToStr(ServerInstance->stats->statsCollisions));
			results.push_back("249 "+user->nick+" :dns requests "+ConvToStr(ServerInstance->stats->statsDnsGood+ServerInstance->stats->statsDnsBad)+" succeeded "+ConvToStr(ServerInstance->stats->statsDnsGood)+" failed "+ConvToStr(ServerInstance->stats->statsDnsBad));
			results.push_back("249 "+user->nick+" :connection count "+ConvToStr(ServerInstance->stats->statsConnects));
			results.push_back(InspIRCd::Format("249 %s :bytes sent %5.2fK recv %5.2fK", user->nick.c_str(),
				ServerInstance->stats->statsSent / 1024.0, ServerInstance->stats->statsRecv / 1024.0));
		}
		break;

		/* stats o */
		case 'o':
		{
			ConfigTagList tags = ServerInstance->Config->ConfTags("oper");
			for(ConfigIter i = tags.first; i != tags.second; ++i)
			{
				ConfigTag* tag = i->second;
				results.push_back("243 "+user->nick+" O "+tag->getString("host")+" * "+
					tag->getString("name") + " " + tag->getString("type")+" 0");
			}
		}
		break;
		case 'O':
		{
			for (OperIndex::const_iterator i = ServerInstance->Config->OperTypes.begin(); i != ServerInstance->Config->OperTypes.end(); ++i)
			{
				OperInfo* tag = i->second;
				tag->init();
				std::string umodes;
				std::string cmodes;
				for(char c='A'; c < 'z'; c++)
				{
					ModeHandler* mh = ServerInstance->Modes->FindMode(c, MODETYPE_USER);
					if (mh && mh->NeedsOper() && tag->AllowedUserModes[c - 'A'])
						umodes.push_back(c);
					mh = ServerInstance->Modes->FindMode(c, MODETYPE_CHANNEL);
					if (mh && mh->NeedsOper() && tag->AllowedChanModes[c - 'A'])
						cmodes.push_back(c);
				}
				results.push_back("243 "+user->nick+" O "+tag->name.c_str() + " " + umodes + " " + cmodes);
			}
		}
		break;

		/* stats l (show user I/O stats) */
		case 'l':
			results.push_back("211 "+user->nick+" :nick[ident@host] sendq cmds_out bytes_out cmds_in bytes_in time_open");
			for (LocalUserList::iterator n = ServerInstance->Users->local_users.begin(); n != ServerInstance->Users->local_users.end(); n++)
			{
				LocalUser* i = *n;
				results.push_back("211 "+user->nick+" "+i->nick+"["+i->ident+"@"+i->dhost+"] "+ConvToStr(i->eh.getSendQSize())+" "+ConvToStr(i->cmds_out)+" "+ConvToStr(i->bytes_out)+" "+ConvToStr(i->cmds_in)+" "+ConvToStr(i->bytes_in)+" "+ConvToStr(ServerInstance->Time() - i->age));
			}
		break;

		/* stats L (show user I/O stats with IP addresses) */
		case 'L':
			results.push_back("211 "+user->nick+" :nick[ident@ip] sendq cmds_out bytes_out cmds_in bytes_in time_open");
			for (LocalUserList::iterator n = ServerInstance->Users->local_users.begin(); n != ServerInstance->Users->local_users.end(); n++)
			{
				LocalUser* i = *n;
				results.push_back("211 "+user->nick+" "+i->nick+"["+i->ident+"@"+i->GetIPString()+"] "+ConvToStr(i->eh.getSendQSize())+" "+ConvToStr(i->cmds_out)+" "+ConvToStr(i->bytes_out)+" "+ConvToStr(i->cmds_in)+" "+ConvToStr(i->bytes_in)+" "+ConvToStr(ServerInstance->Time() - i->age));
			}
		break;

		/* stats u (show server uptime) */
		case 'u':
		{
			time_t current_time = 0;
			current_time = ServerInstance->Time();
			time_t server_uptime = current_time - ServerInstance->startup_time;
			struct tm* stime;
			stime = gmtime(&server_uptime);
			/* i dont know who the hell would have an ircd running for over a year nonstop, but
			 * Craig suggested this, and it seemed a good idea so in it went */
			if (stime->tm_year > 70)
			{
				results.push_back(InspIRCd::Format("242 %s :Server up %d years, %d days, %.2d:%.2d:%.2d",
					user->nick.c_str(), stime->tm_year - 70, stime->tm_yday, stime->tm_hour,
					stime->tm_min, stime->tm_sec));
			}
			else
			{
				results.push_back(InspIRCd::Format("242 %s :Server up %d days, %.2d:%.2d:%.2d",
					user->nick.c_str(), stime->tm_yday, stime->tm_hour, stime->tm_min,
					stime->tm_sec));
			}
		}
		break;

		default:
		break;
	}

	results.push_back("219 "+user->nick+" "+statschar+" :End of /STATS report");
	ServerInstance->SNO->WriteToSnoMask('t',"%s '%c' requested by %s (%s@%s)",
		(IS_LOCAL(user) ? "Stats" : "Remote stats"), statschar, user->nick.c_str(), user->ident.c_str(), user->host.c_str());
	return;
}