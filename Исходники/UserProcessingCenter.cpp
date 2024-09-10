void UserProcessingCenter::handleLogin(CMazeMsg* context)
{
	string input(context->getMsg());
	MBlockSocket *pclient = context->getSocket();
	UserDatabase *userdb = UserDatabase::getInstance();
       CUserCard onecard;
	cout<<" : Login : "******"Version").c_str())>atof("510"))
		onecard.isold=false;
			
	unsigned long uid;
	bool UIDLogin=false;
	uid = CConvert::StringToInt (MXMLHandler::GetNode(input,"UID"));

	string email=MXMLHandler::GetNode(input,"EmailAddr");
	if (uid>0)
		UIDLogin=true;
	else
	{
		USERDB* tmpUser = new USERDB;
		memset(tmpUser, 0, sizeof(USERDB));
		string email = MXMLHandler::GetNode(input,"EmailAddr");
		userdb->get_record(email, tmpUser);
		uid = tmpUser->UID;
		cout<<"Login mail:"<<email<<";"<<uid<<endl;
		delete tmpUser;
	}

	string output;
	if (!onecard.isold)//new version of client.exe
	{
		USERDB* one = new USERDB;
		memset(one, 0, sizeof(USERDB));
		string output = "";
		string m;
				
		if(userdb->get_record(uid, one) == 0)
			cout<<" : Login : "******" : LoginErr : "<<one->UID<<endl;
				
		m = string(one->MailAddr);
				
		if (m=="")
			output=MXMLHandler::CreateNode("Alarm","EmailNotSigned");
				
		string desc,pwd,nickname,mail;
		unsigned int account, ip;
		time_t taccount;
		ip = pclient->GetPeerName().GetIP();
		string ip_str=pclient->GetPeerName().ip();
		mail = string(one->MailAddr==NULL?"@":one->MailAddr);
		nickname = string(one->NickName);
		pwd = string(one->Pwd);
		account = one->Account;
		taccount = one->LastAddAccount;
		one->LastLoginIP = ip;
		one->LastLogin = time(NULL);
		int level = one->Level;
				
		if(userdb->put_record( uid, one) == 0)
			cout <<" : Login update success : "<<one->UID<<endl;
		else
			cout <<" : Login update faild : "<<one->UID<<endl;
				
		if (!onecard.isold)
		{   
			onecard.m_card.UID = uid;
			if(uid < 3000000)
			{
				mail = "";
			}
			strcpy(onecard.m_card.MailAddr,mail.c_str());
			//cout<<"email以后的onecard.m_card.UID"<<onecard.m_card.UID<<endl;
			onecard.m_card.Account = account;
			//cout<<"account以后的onecard.m_card.UID"<<onecard.m_card.UID<<endl;
			onecard.m_card.Level = level;
			//cout<<"level以后的onecard.m_card.UID"<<onecard.m_card.UID<<endl;

			if(nickname.length()>=24)
			{
				memcpy(onecard.m_card.NickName,nickname.c_str(),23);
				onecard.m_card.NickName[23] = '\0';
			}
			else
				strcpy(onecard.m_card.NickName,nickname.c_str());
					
			//cout<<"Nick以后的onecard.m_card.UID"<<onecard.m_card.UID<<endl;
			onecard.m_card.IP  = pclient->GetPeerName().GetIP();
		}
		else
		{
			onecard.m_oldcard.UID = uid;
			onecard.m_oldcard.Account = account;
			onecard.m_oldcard.Level = level;
			strcpy(onecard.m_oldcard.NickName,nickname.c_str());
			onecard.m_oldcard.IP  = pclient->GetPeerName().GetIP();
		}
				
		//cout<<"CMD Login:"******"MyIP");
		//lqf_7.5 判断本地socketip地址是否和用户服务器看到的socketip地址相同，不同则判断为内网
		if (CConvert::StringToInt (myip)==ip)
		{
			if (!onecard.isold)
				onecard.m_card.ServerPort =CConvert::StringToInt(MXMLHandler::GetNode(input,"SvrPort"));
			else
				onecard.m_oldcard.ServerPort = CConvert::StringToInt(MXMLHandler::GetNode(input,"SvrPort"));
		}
		else
		{
			if (!onecard.isold)
				onecard.m_card.ServerPort =0;//如果服务端口为0，说明这个客户是在防火墙内else      
			else
				onecard.m_oldcard.ServerPort = 0;
		}
		//add system crc
		onecard.AddSysCRC ();
		string crccard=onecard.ToBase64 ();
		//encrypt with client key
		//客户端的密码，从数据库获取
		//cout <<"用户服务器密的密码是"<<pwd<<endl;
		onecard.AddUserEncrypt(pwd);
		//cout << "Logi<pwd<<endl;
		//cout <<"用户服务器本地解密card以后"<<endl;
		//lqf_7.6	用户服务器加密card以后本地解密就出错，对300w以前的用户
		//问题确定出在这里..
		output+=MXMLHandler::CreateNode("Card",onecard.ToBase64 ());
		output+=MXMLHandler::CreateNode("CardTimeOutSecond","36000");
					
		string sLastTime = CConvert::IntToString(taccount);
		output+=MXMLHandler::CreateNode("LastAccountTime",sLastTime);
		/*nick name fix debug by lqf
		CUserCard usercard;
		usercard.isold = false;
		usercard.FromBase64(MXMLHandler::GetNode(output,"Card"));
		//用本地存储的密码来解密从用户服务器返回的信用卡
		cout <<"用户服务器解密的密码是"<<pwd<<endl;
		usercard.RemoveUserEncrypt(pwd);
		cout << "UID:" << usercard.m_card.UID<<endl;
		 */
		//cout<<"Login Reply "<<output<<endl;
				
		pclient->SendPacket (output.c_str (),output.length ()+1);
		delete one;

		
		char buf[256];
		time_t timep;
		struct tm *p;
		time(&timep);
		p=localtime(&timep);
		sprintf(buf,"%d_%0.2d_%0.2d_login.txt",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);

		Configuration config = Configuration::getInstance();
		string logDir = config.get("log");
		string logName = logDir + buf;
		ofstream loginLogOutput(logName.c_str(),ofstream::app);
		sprintf(buf,"%.2d:%.2d:%.2d  %10d    %15s login ",p->tm_hour,p->tm_min,p->tm_sec,uid,ip_str.c_str());
		loginLogOutput<<buf<<endl;
		
	}
}