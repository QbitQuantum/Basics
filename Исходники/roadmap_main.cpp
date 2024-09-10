 void roadmap_internet_open_browser (char *url) {
 	  RApaLsSession apaLsSession;
 	  const TUid KOSSBrowserUidValue = {0x10008D39}; // 0x1020724D for S60 3rd Ed
 	  TUid id(KOSSBrowserUidValue);
 	  TApaTaskList taskList(CEikonEnv::Static()->WsSession());
 	  TApaTask task = taskList.FindApp(id);
 	  if(task.Exists())
 		  {
 		  task.BringToForeground();
 		  task.SendMessage(TUid::Uid(0), TPtrC8((TUint8 *)url,strlen(url))); // UID not used
 		  }
 	  else
 		  {
 		  if(!apaLsSession.Handle())
 			  {
 			  User::LeaveIfError(apaLsSession.Connect());
 			  }
 		  TThreadId thread;
 		  
 		  TBuf16<128> buf;
 		  buf.Copy(TPtrC8((TUint8 *)url,strlen(url)));
 		   		  
 		  User::LeaveIfError(apaLsSession.StartDocument(buf, KOSSBrowserUidValue, thread));
 		  apaLsSession.Close();   
 		  }
 }