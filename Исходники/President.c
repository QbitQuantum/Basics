void President()
{
  int presidentNumberOfCalls=0; /* keep count of total number of calls made by the president */
  int checkCorrectOperatorP;
  int waitingTime;
  int condnToWait;
  int phoneToUse, gotPhone,i,j;
  int operatorToUse;
  int talkingTime;
  int phoneStatus_i;
  int num;
  char lockName[30];
  char condName1[30];
  char condName2[30];
  int presidentStatus;
  int phoneStatus;
  char printing[50];
  int lockID1, lockID2, lockID3, lockID4, lockID5, lockID6, condID1, condID2, condID3, condID4;
  int indOpLock[20], waitForOperVerCV[20], waitForCallerCV[20];
  int activate, authMechanism, freeOperators, operatorStatus;



  /* Create or get access to some shared variables, locks, conditions */
  presidentStatus = CreateSharedInt("presidentStatus",15,1);
  phoneStatus = CreateSharedInt("phoneStatus",11,NOOFPHONES);
  lockID1 = CreateLock("phoneLock",10);                  /* obtain a master lock for all phones */
  freeOperators = CreateSharedInt("freeOperators",13,1);
  operatorStatus = CreateSharedInt("operatorStatus",14,Nop);
  activate = CreateSharedInt("activate",sizeof("activate"),Nop);
  authMechanism = CreateSharedInt("authMechanism",sizeof("authMechanism"),Nop);


  lockID2 = CreateLock("GlobalOpLock",sizeof("globaloplock"));     /* obtain a master lock for all the operators */
  lockID3 = CreateLock("visitorCountLock",17);     /* obtain a lock to keep track of the number of visitors permitted to make a call */
  lockID4 = CreateLock("NumSenators",12);
  lockID5 = CreateLock("NumVisitors",12);
  lockID6 = CreateLock("NumOperators",13);
 /*  displayLock = CreateLock("DispLock",7); */
  /* Lock **individualOperatorLock; */                            /* obtain an individual lock for every operator */
  condID1 = CreateCondition("presiNeedsPhone",16); /* condition variable for the condition that president needs phone */
  condID2 = CreateCondition("senatorNeedsPhone",18);     /* condition variable for the condition that senator needs phone */
  condID3 = CreateCondition("visitorNeedsPhone",18);     /* condition variable for the condition that visitor  needs phone */
  condID4 = CreateCondition("processCustomer",16);         /* condition variable to allow president/senator/visitor to make a call */
  for (i=0;i<Nop;i++)
    {
     Concatenate("OperatorLock",sizeof("OperatorLock"),i,lockName);
     Concatenate("waitForOpVer",sizeof("waitForOpVer"),i,condName1);
     Concatenate("waitForCaller",sizeof("waitForCaller"),i,condName2); 
     indOpLock[i] = CreateLock(lockName,sizeof(lockName));
     waitForOperVerCV[i] = CreateCondition(condName1,sizeof(condName1));
     waitForCallerCV[i] = CreateCondition(condName2,sizeof(condName2));
    } 

	 while(presidentNumberOfCalls<3)
    {
		 WriteMe("President Going to speak for the ");WriteNum(presidentNumberOfCalls);WriteMe("th time\n");
      condnToWait = FALSE;
      phoneToUse = 0;

      AcquireLock(lockID1);

      SetSharedInt(presidentStatus, 0, 1); /* presidentStatus = 1; */

      /* loop for the president to keep waiting even if a single phone is busy */
      do
	  {	 
		  /*
		  for(i=0;i<NOOFPHONES;i++)
		    {
			 phoneStatus_i = GetSharedInt(phoneStatus,i);
		     if(phoneStatus_i == BUSY)
				{
				 condnToWait = TRUE;
				 break;
				}
		    } */
			i = GetZeroIndex(phoneStatus);

		if(i==NOOFPHONES)
		   condnToWait=FALSE;
		else
			condnToWait = TRUE;
	
		if(condnToWait==TRUE)
		  WaitCV(condID1,lockID1);
	
	  }while(condnToWait==TRUE);
	  	
      /* all phones are free now */
      SetSharedInt(phoneStatus, phoneToUse, BUSY); /* phoneStatus[phoneToUse] = BUSY;*/
      /* president has obtained a phone now */
      ReleaseLock(lockID1);      
      /* Need to get an operator */
      AcquireLock(lockID2);
      /* loop to wait till an operator is available */
	  	
      while(GetSharedInt(freeOperators,0)==0)
	    WaitCV(condID4,lockID2);
	  	
	  /* president has to wait if there are no free operators available */
      /* Some operator is available. Though I don't know who it is yet, let us find out    */    
      /*
	  for(j=0;j<Nop;j++)
	  {
	  if(GetSharedInt(operatorStatus,j)==FREE)
	    {
	      operatorToUse = j;
	      break;
	    }
	 }
	 */
	 operatorToUse = GetOneIndex(operatorStatus);
      /* operator obtained */
      /* check if the operator to whom president goes for authentication is same as the one who permits him/her to make a call. */
      checkCorrectOperatorP = operatorToUse;
      AcquireLock(indOpLock[operatorToUse]);
      SetSharedInt(activate, operatorToUse, 2);
      SetSharedInt(operatorStatus, operatorToUse, BUSY);
      SetSharedInt(freeOperators, 0, GetSharedInt(freeOperators, 0) - 1);
	  ReleaseLock(lockID2);
      SetSharedInt(authMechanism, operatorToUse, 1); /* 1 for President | 2 for Senators | 3 for Visitors */
	 
      /* If operator is sleeping, wake up */
	  SignalCV(waitForCallerCV[operatorToUse],indOpLock[operatorToUse]);
	  while(GetSharedInt(activate,operatorToUse)==2)
	      WaitCV(waitForOperVerCV[operatorToUse],indOpLock[operatorToUse]); 
      ReleaseLock(indOpLock[operatorToUse]);  
      if(GetSharedInt(activate,operatorToUse)==0) /* President is denied access to phone.But this will never happen as there is only one president and we assume that his/her ID is never faked */
	  {
	  /*  printf("President is denied access to Phone failing authentication!\n"); */
		Write("President is denied access to Phone failing authentication!\n",sizeof("President is denied access to Phone failing authentication!\n"),1);
	  }
      else if(GetSharedInt(activate, operatorToUse)==1) /* operator succesfully authenticates the identity of the president */
	 {
	  /* Now Talk */
	  talkingTime = RandomFunction(20); /* randomly generate the amount of time the president is talking */
          /* loop for the president to talk on the phone for the randomly generated time period */
	  for (j=1;j<=talkingTime;j++){
	    /*printf("President \t  %d \t\t %d/%d units \t %d \t\t %d \t    ACCEPTED       NOTAPPLICABLE - verified by operator %d \n",phoneToUse+1,j,talkingTime,operatorToUse+1,presidentNumberOfCalls+1,checkCorrectOperatorP+1);*/
		/*AcquireLock(displayLock); */
		Write("President \t ",13,1);
	    num = phoneToUse+1;
	    itoa(printing,10,num);
	    Write(printing,sizeof(printing),1);
	    Write("\t\t ",5,1);	    
	    itoa(printing,10,j);
	    Write(printing,sizeof(printing),1);
	    Write("/",1,1);
	    num=talkingTime;
	    itoa(printing,10,num);
	    Write(printing,sizeof(printing),1);
	    Write(" units \t ",10,1);
	    num=operatorToUse+1;
	    itoa(printing,10,num);
	    Write(printing,sizeof(printing),1);
	    Write(" \t\t ",6,1);
	    num=presidentNumberOfCalls+1;
	    itoa(printing,10,num);
	    Write(printing,sizeof(printing),1);
	    Write(" \t   ACCEPTED      NOTAPPLICABLE - verified by operator ",56,1);
	    num=checkCorrectOperatorP+1;
	    itoa(printing,10,num);
	    Write(printing,sizeof(printing),1);
	    Write(" \n",3,1);
		/*ReleaseLock(displayLock);*/
	   /* Yield();*/
	  }
	  /* president is done talking */	  
	  /* Set the status to be free */
	  AcquireLock(lockID1);
	  SetSharedInt(phoneStatus, phoneToUse, FREE);
	  SetSharedInt(presidentStatus,0,0);
	  BroadcastCV(condID2,lockID1); /* wake up all the senators waiting to talk */
	  BroadcastCV(condID3,lockID1); /* wake up all the visitors waiting to talk */
	  ReleaseLock(lockID1);
	}
      /* president goes away  */
      /* president waits for a random amount of time before coming back to make the next call. Remember maximum number of calls allowed is 5 */
      waitingTime = RandomFunction(4);
      for(j=0;j<waitingTime;j++)
	{
	  Yield();
	}
      presidentNumberOfCalls++; /* increment the number of calls made by the president */
    }
  Exit(0);
}