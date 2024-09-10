bool MailingList::ProcessEmailFile(std::string emailfilepathstr)
{
	/*
		Check if sender of email is authorised to post to this list, if not return true and caller will delete file
		else copy it to an outgoing email with relevent header changes, queue og mail for delivery
		and return true so caller will delete file.
		Any errors return false
	*/
	
	
	BFile* bfile = new BFile(emailfilepathstr.c_str(),B_READ_WRITE);
	
	if (bfile->InitCheck() != B_NO_ERROR)
	{
		LogError("ERROR: Could not process an incoming email. BFile::InitCheck was false");
		return false;
	}

	IncomingMail* ICMail= new IncomingMail(bfile,this);
	if (ICMail->InitCheck()==false)
	{
		LogError("ERROR: Could not process an incoming email. File read failed. IncomingMail::InitCheck was false");
		return false;
	}
	
	if (fLogSuccesses)
	{
		LogError("INFO: Processing an email file from "+ICMail->GetSendersAddr());
	}
	
	
	int32 authstatus=1;
	
	/*
		Return vals from external auth prog are 
		0=Authorised
		1=Error
		2=Not Authorsed - bounce msg
		3=Not Authorised - silently discard
		
		This func should return false if val is 1, thus ensuring the incoming file is not deleted and will be re-processed later
		for all other values it should return true, indicating that the incoming file can be deleted
	*/
	int32 arg_c = 4; //no of args passed in arg_v
	extern char **environ; //env variables
	char **arg_v;
	arg_v = (char **) malloc(sizeof(char*) * (arg_c+1)); //array must hold arg_c elements + a terminating null
	
	std::stringstream epochsecs;
	epochsecs << real_time_clock(); //secs now since unix epoch
	int filenamecounterInt=0; //will be incremented until we get a unique filename string
	bool nonuniquefilename=true;
	BEntry tempFileBEntry;
	std::string tempFilePath;
	do
	{
		filenamecounterInt++;
		std::stringstream filenamecounter;
		filenamecounter << filenamecounterInt;
		MailMistressApplication* app=(MailMistressApplication*) be_app;
		tempFilePath=app->GetTempDirPath()+fListICAddress+"--"+ICMail->GetSendersAddr()+"--"+epochsecs.str()+filenamecounter.str();
		//test if tempFilePath already exists
		tempFileBEntry.SetTo(tempFilePath.c_str());
		BFile tempFileBFile;
		status_t tempFileResult=tempFileBFile.SetTo(&tempFileBEntry,B_READ_WRITE|B_FAIL_IF_EXISTS|B_CREATE_FILE); //fails if already exists
		if (tempFileResult==B_FILE_EXISTS)
		{
			nonuniquefilename=true;	
		}
		else if (tempFileResult==B_NO_ERROR)
		{
			nonuniquefilename=false;
			tempFileBFile.Unset(); //close file
		}
		else
		{
			//error
			bfile->Unset();
			//delete ICMail obj
			delete ICMail;
			delete bfile;

			return false;
		}
		
	}while(nonuniquefilename);
	
	
	arg_v[0]=strdup(fAuthProgPath.c_str()); //path to exe
	arg_v[1]=strdup((ICMail->GetSendersAddr()).c_str()); //senders email addr
	arg_v[2]=strdup(tempFilePath.c_str()); //path to temp file
	arg_v[3]=strdup(fListICAddress.c_str()); //list IC address
	arg_v[4]=NULL;
	
	thread_id authprog_team;
	authprog_team=load_image(arg_c,(const char**)arg_v,(const char**)environ);
	free(arg_v);
	wait_for_thread(authprog_team,&authstatus);
	//if authstatus==0 then temp file will now contain all recipient email addresses one per line
	
	if (authstatus==0)
	{
		//send to recipients in temp file
		if (DistributeEmail(ICMail,tempFilePath))
		{
				//delete temp file
				tempFileBEntry.Remove();
				
				//delete ICMail obj
				delete ICMail;
				
				//close orig email file
				bfile->Unset();
				delete bfile;
				return true;
		}
		else
		{
				//delete temp file
				tempFileBEntry.Remove();
				
				//delete ICMail obj
				delete ICMail;
				
				//close orig email file
				bfile->Unset();
				delete bfile;
			
				return false;
		}
	}
	else if (authstatus==2)
	{
			LogError("INFO: Auth status 2 -- Bouncing to "+ICMail->GetSendersAddr());
			BMailMessage* ogmail;
			ogmail= new BMailMessage();
			ogmail->AddHeaderField(B_MAIL_TO,(ICMail->GetSendersAddr()).c_str());
			ogmail->AddHeaderField(B_MAIL_FROM,fListOGEnvelopeAddressFromAddress.c_str());
			std::string bouncesubject=std::string("Undelivered mail: Your message to ");
			bouncesubject=bouncesubject+fListName+" was rejected";
			ogmail->AddHeaderField(B_MAIL_SUBJECT,bouncesubject.c_str());
			ogmail->AddHeaderField("X-Mailer: ",(fApp->GetAppName()).c_str());
    	  	ogmail->AddContent(fUnauthorisedBounceMsgContents.c_str(),strlen(fUnauthorisedBounceMsgContents.c_str()));
			ogmail->Send();
			delete ogmail;
	}
	else if (authstatus==3)
	{
			LogError("INFO: Auth status 3 -- Silently discarding email from "+ICMail->GetSendersAddr());	
			
	}
	
	//delete temp file
	tempFileBEntry.Remove();
	
	if ( (authstatus==2) || (authstatus==3)  )
	{
		//ok so return true to delete incoming file
		delete ICMail;
		bfile->Unset();
		delete bfile;
		
		return true;	
	}
	else
	{
		//error occured so return false and incoming file will be kept for reprocessing later
		LogError("ERROR: Auth status 1 (or other error value). Either the autentication program failed to run or it encountered an error itself");
		delete ICMail;
		bfile->Unset();
		delete bfile;
	
		return false;	
	}
	
}