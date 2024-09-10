bool cFloodprotect::CheckFlood(cConnDC * conn, tFloodType ft)
{
	if (conn && conn->mpUser && conn->mpUser->mClass >= eUC_OPERATOR) return true;

	unsigned long Hash = cBanList::Ip2Num(conn->AddrIP());

	if(mUserInfo.ContainsHash(Hash))
	{
		cTime now;
		sUserInfo * usr = 0;
		usr = mUserInfo.GetByHash(Hash);

		if(!usr || (usr && usr->mDisabled)) return false;

		usr->mElapsedTime += now.Get() - usr->mLastAction;
		usr->mLastAction = now;
		usr->mActionCounter++;

		usr->addFloodType(ft); // registers the current action type for later analysis

		if(usr->mActionCounter == 10)
		{
			//10/10 = freq > 1 Hz
			//10/10 - freq = 1 Hz - 0.33 Hz
			//10/30 = freq < 0.33 Hz
			if(usr->mElapsedTime.Sec() < 10) // 10 actions, 1 Hz or higher is high frequency
			{
				ostringstream os;
				string text, floodtype;

				int cnt = KickAll(conn);

				switch(ft)
				{
					case eFT_CHAT: floodtype = "MAIN CHAT"; break;
					case eFT_PRIVATE: floodtype = "PRIVATE CHAT"; break;
					case eFT_SEARCH: floodtype = "SEARCH"; break;
					case eFT_MYINFO: floodtype = "MYINFO"; break;
					default: floodtype = "UNKNOWN"; break;
				}

				os << "\r\n";
				os << "FLOODPROTECT: User is trying to " << floodtype << " flood the server. Number of affected connections: " << cnt << ". Banned for " << mCfg.mBanTimeOnFlood << " secs!\r\n";
				os << "FLOODPROTECT: Frequecy is: " << usr->mActionCounter / (usr->mElapsedTime.Sec() + (usr->mElapsedTime.tv_usec / 1000000.)) << " Hz\r\n";
				os << "FLOODPROTECT: Detected flood types are: " << usr->getFloodTypes();
				text = os.str();
				mS->ReportUserToOpchat(conn, text, false);

				cBan Ban(mS);
				cKick Kick;

				Kick.mOp = mS->mC.hub_security;
				Kick.mIP = usr->mIP;
				Kick.mTime = cTime().Sec();
				Kick.mReason = "HIGH FLOOD FREQUENCY DETECTED!";
				mS->mBanList->NewBan(Ban, Kick, mCfg.mBanTimeOnFlood, eBF_IP);
				mS->mBanList->AddBan(Ban);
				usr->mDisabled = true;
				usr->mActionCounter = 0;
				usr->mElapsedTime = cTime(0,0);
				return false;
			}
			if((usr->mElapsedTime.Sec() >= 10) && (usr->mElapsedTime.Sec() < 30)) // between 0.33 Hz and 1 Hz is medium frequency
			{
				//string text;
				//ostringstream os;
				//os << "\r\n";
				//os << "FLOODPROTECT: Frequecy is: " << usr->mActionCounter / (usr->mElapsedTime.Sec() + (usr->mElapsedTime.tv_usec / 1000000.)) << " Hz\r\n";
				//os << "FLOODPROTECT: Detected flood types are: " << usr->getFloodTypes();
				//text = os.str();
				//mS->ReportUserToOpchat(conn, text, false);
				conn->CloseNow();
				usr->mActionCounter = 0;
				usr->mElapsedTime = cTime(0,0);
				return false;
			}
			if(usr->mElapsedTime.Sec() >= 30) // less than 0.33 Hz is low frequency
			{
				//string text;
				//ostringstream os;
				//os << "\r\n";
				//os << "FLOODPROTECT: Frequecy is: " << usr->mActionCounter / (usr->mElapsedTime.Sec() + (usr->mElapsedTime.tv_usec / 1000000.)) << " Hz\r\n";
				//os << "FLOODPROTECT: Detected action types are: " << usr->getFloodTypes();
				//text = os.str();
				//mS->ReportUserToOpchat(conn, text, false);
			        usr->mActionCounter = 0;
			        usr->mElapsedTime = cTime(0,0);
			        return true;
			}
		}
	}
	else
	{
		cTime now;
		sUserInfo * usr;
		usr = new sUserInfo(conn->AddrIP());
		if(!usr) return false;
		usr->mLastAction = now;
		usr->mElapsedTime = cTime(0,0);
		mUserInfo.AddWithHash(usr, Hash);
	}
	return true;
}