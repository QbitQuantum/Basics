   void start()
   {
	  i=0;
	  init();
	  setcolor(WHITE);
	  settextstyle(1,0,4);
	  outtextxy(100,400,"Press any key to Continue");

	 if((f1=fopen("firstrun","r"))==NULL)
	  {
	   f1=fopen("firstrun","w+");
	   border();
	   while(!kbhit())
	   {
		if(i%2==0)
		 setcolor(GREEN);
		else
		 setcolor(BLACK);
		settextstyle(1,0,3);
		outtextxy(75,300,"Program is running for the first time");
		delay(500);
		i++;
	   }
	   f2=fopen("Admin","wb+");
	   f3=fopen("data.dat","wb+");
	   f5=fopen("rem_acc.dat","wb+");
	   f6=fopen("password.dat","wb+");
	   df=fopen("cust.dat","wb+");
	   ft=fopen("transactions","wb+");
	   strcpy(admin.loginid,"admin");
	   strcpy(admin.password,"password");
	   fwrite(&admin,sizeof(admin),1,f2);
	   data.acc_no=10001;
	   data.tran_no=1000000;
	   fwrite(&data,sizeof(data),1,f3);
	   flushall();
	   fcloseall();
	  }
	  getch();
   }