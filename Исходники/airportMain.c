/*
int checkExpiry(passenger p)
{
	return 0;		
}
int checkVisa(passenger p)
{
	return 1;
}
*/
int main()
{
	printf("Airport Simulation System.\nThe system may wait for few seconds in between. \n");
	pipe(restpipe);
	pipe(cafepipe);
	int secpip[2];
	char secbuf[10];
	pid_t baggage,immig,sec,lounge,board,lug,wt,pass;
	
	//taking number of passengers here so as to malloc now before passing as function
	FILE *fp = fopen("input.txt","r");	
	fscanf(fp," %d",&num);
	plist = (passenger *)malloc(num*sizeof(passenger));
	inputAll(plist);
	//input from file over
	
	int extraCost=0;
	
	boarding = fork();
	if(!boarding)
	{
		signal(SIGUSR1,addLoungers);
		signal(SIGUSR2,removeLoungers);
		
		raise(SIGSTOP);
		printf("\nAll passengers are requested to move to the Gate.\n");
		
		if(loungers !=0)
			printf("this is the last boarding call for passengers. please report immediately to the gate\n");
		
		sleep(2);
		kill(getppid(),SIGUSR2);
		exit(0);	
	}
	lounge = fork();
	if(!lounge)
	{
		cafe = fork();
		if(cafe) 
		{
		rest = fork();
			if(!rest)  //in restroom process
			{
				
				signal(SIGUSR1,gotorest);	
				while(1);
			}
			
		}
		else  //in cafe process
		{
			signal(SIGUSR1,gotocafe);
			while(1);
		}
		while( i < num ) {
			raise(SIGSTOP);
			srand(time(NULL));
			int choice = rand()%3;  //3 because it is not necessary he has to go to cafe or airport
			if(choice ==0) //go to cafe
			{
				sprintf(cafebuf,"%s",plist[i].flt.ticket_no);
				write(cafepipe[1],cafebuf,15);
				kill(cafe,SIGUSR1);
			}
			else if(choice ==1)
			{	 //go to restroom
				sprintf(restbuf,"%s",plist[i].flt.ticket_no);	
				write(restpipe[1],restbuf,15);
				kill(rest,SIGUSR1);
			}
			i++;
		}
		kill(boarding,SIGCONT);
		raise(SIGSTOP);
	
		kill(cafe,SIGKILL);
		kill(rest,SIGKILL);
		exit(0);
		
	}
	
	checksec = fork();		
	if(!checksec)
	{
		//why pipe? we do not know the value of i inside the child processes.
		//so every time a passenger comes in, we can update the value on a pipe and children can see it.
		pipe(secpip);	
		
		while( i < num ) 
		{
			raise(SIGSTOP);
			sleep(1);
			if(i==0)
			{
			     secm= fork();
		             if(secm)
			     	secf=fork();
			}
			if(secm && secf)
			{
				sleep(1);
				sprintf(secbuf,"%d",i);
				write(secpip[1],secbuf,10);
				if(plist[i].gender=='M')
				kill(secm,SIGCONT);
				else
				kill(secf,SIGCONT);
			
			}
			if(secm==0 )
			{
				while(1)
				{
					raise(SIGSTOP);
					sleep(1);
					read(secpip[0],secbuf,10);
					printf("Invalid items in hand bag of male %d: ",atoi(secbuf));
					checkMFbag(plist[atoi(secbuf)]);
					kill(getppid(),SIGCONT);
				}
			}
			if(secm && secf==0 )
			{
				while(1)
				{
					raise(SIGSTOP);
					sleep(1);
					read(secpip[0],secbuf,10);	
					printf("Invalid items in hand bag of female %d: ",atoi(secbuf));
					checkMFbag(plist[atoi(secbuf)]);
					kill(getppid(),SIGCONT);
				}
			}
			raise(SIGSTOP); //so that when sec_M or sec_F calls it, it has ample time to raise itself
			sleep(1);
			kill(lounge,SIGCONT);	
			i++;	
		}
		kill(secm,SIGKILL);
		kill(secf,SIGKILL);
		exit(0);
	}

	if(checksec ==0)   //go into male and female security check
	{
		while( i < num ) {
			raise(SIGSTOP);
			sleep(1);			
			kill(lounge,SIGCONT);	
			i++;	
		}
		exit(0);
	}

	
	immigration = fork();
	if(immigration == 0)
	{
		//pipe(impipe);
		while( i < num ) {
			raise(SIGSTOP);
			printf("checking immigration of %d\n",i);
			/*	
			if(i==0)
			{
				visa = fork();
				if(visa) 
					passport = fork();
			}
			if(visa && passport)
			{
				sleep(1);
				kill(passport,SIGCONT);
			}
			if(!passport)
			{
				while(1)
				{
					raise(SIGSTOP);
					sleep(.5);
					if(checkPass(plist[i]))
					{
						sprintf(imbuf,"%d",i,10);
						write(impipe[1],imbuf,10);
						kill(visa,SIGCONT);
					}
					else
					{
						plist[i].valid = 0;
						FILE *fp = fopen(plist[i].flt.ticket_no,"a");
						fprintf(fp,"Immigration not successful\n");
						fclose(fp);
						kill(getppid(),SIGCONT);		
					}
					i++;
				}
			}
			if(!visa)
			{
				while(1)
				{
					raise(SIGSTOP);
					sleep(0.5);
					read(impipe[0],imbuf,10);
					if(checkVisa(plist[atoi(imbuf)]))
					{
						FILE *fp = fopen(plist[atoi(imbuf)].flt.ticket_no,"a");
						fprintf(fp,"Immigration successful\n");
						fclose(fp);
			
					}
					else
					{
						plist[atoi(imbuf)].valid = 0;
						FILE *fp = fopen(plist[atoi(imbuf)].flt.ticket_no,"a");
						fprintf(fp,"Immigration not successful\n");
						fclose(fp);	
					}
					kill(getppid(),SIGCONT);
				}
			}
			
			raise(SIGSTOP);
			*/
			sleep(2);
			kill(checksec,SIGCONT);
		        
		   	i++;
			
		}
		//kill(visa,SIGKILL);
		//kill(passport,SIGKILL);
		exit(0);
	}

	bcounter = fork();
	if(bcounter && immigration && checksec && lounge && boarding)
		signal(SIGUSR2,sigtoStop);  //this is for mother process(airport). this is for when final stop
	
	
	if(bcounter == 0)
	{
		int p1[2],p2[2];
		char buf1[10],buf2[10]; //buf1 for
		pipe(p1);
		pipe(p2);
		while( i < num ) 
		{
			if(i==0)
			{
				boardpass = fork();
				if(boardpass) weight = fork();
				if(boardpass && weight) lugsec = fork();
			}
			if(boardpass == 0)   //going into boarding pass process.called after baggage price calc
			{	
				raise(SIGSTOP);
				if(i == 0) 
				{
				 	sleep(2);
					close(p1[1]);
					read(p1[0],buf1,10);
					weight = atoi(buf1);  //getting weight's pid so that he can be called
				}
				sleep(1);
				makePass(plist[i]);
				kill(weight,SIGCONT);
				i++;
				if(i == num)
					exit(0);
				continue;
			}
			if(weight == 0)
			{
				sleep(1);
				raise(SIGSTOP);    //will be called by boarding pass to print extra cost.
			    	extraCost = checkExtraCost(plist[i]);  //todo
			    	printf("Extra cost = Rs.%d\n",extraCost);
			    	sleep(2);
			   	kill(boardpass,SIGCONT);
			    	//returning
			    	raise(SIGSTOP);
			    
			    	addCostoFile(plist[i],extraCost);   //appended extra cost
			    
			    	if(i == 0)
			    	{    
					sleep(1);
					close(p2[1]);
					read(p2[0],buf2,10);
					lugsec = atoi(buf2);
				 }
			    kill(lugsec,SIGCONT);
			    i++;
			    if(i == num)  //exiting if all passengers have finished passing baggage counter
				exit(0);
			    continue;
			}
			if(i == 0)
			{
				sprintf(buf1,"%d",weight);
			    	close(p1[0]);
			  	write(p1[1],buf1,10);
			}
			if(lugsec == 0)
			{
			    sleep(1);
			    checkLuggage(plist,i);
			    sleep(2);
			    kill(weight,SIGCONT);                    //sending to weight
			    raise(SIGSTOP);                          //waiting 
			    int nt = plist[i].num_bags,it,jt;
			    for(it=0;it<nt;it++)
			    {
			    	for(jt=0;jt<10;jt++)
			    	{
			    		if(plist[i].explosives[it][jt] ==1)
			    		printf("%d ",plist[i].content[it][jt]);
			    	}
			    	printf("\n");
			    }
			    appendBaggageID(plist[i]);
			    kill(immigration,SIGCONT);              //baggage counter sending to immigration
			    i++;
			    
			    if( i == num )
			    {
			     	exit(0);
			    }
			    continue;
			}

			    if(i == 0) 
			    {
			    	sprintf(buf2,"%d",lugsec);
			    	close(p2[0]);
			    	write(p2[1],buf2,10);
			    }
		    i++;
		    }	
	}
	while(wait(NULL)!=-1);
	return 0;
}