main()
{
	int mode=VGAHI,driver=VGA;
	char ch;
 	unsigned int l;
 	int i,gi,gj,j,flag=1;/*i,j是循环变量,flag是标记变量,-1:向x负半轴移动,+1:向x正半轴移动*/
 	double qx,qy,k,b=0.0,speech=0.4,x,y;
 	double r=2.0,bx=60.0,byy=270.0;
 	double pianx=100.0,piany=100.0,tx=20.0,ty=10.0,jx=2.0,jy=2.0;
 	int mx=0,my=0,mb,sum;/*sum纪录砖块的数目*/
 	FILE * p;
  	if((p = fopen("record.dat", "r")) == NULL)
    	{
    		p=fopen("record.dat","w");
    		fprintf(p,"0 0 0 0 0\n");
    		rewind(p);
     	}
     	fclose(p);

	initgraph(&driver,&mode,"C:\\tc");
	setbkcolor(BLUE);
 	Msinit();
 	Setmouse((int)(pianx+1+bx/2),(int)((tx+jx)*8+pianx-1-bx/2),(int)byy+piany,(int)byy+piany);

star:	cleardevice();/*程序重载的介入点*/
	setcolor(RED);
	outtextxy(30,20,"^_^ Welcome to Play Hitting Brick Game! ^_^");

	sum=0;
 	qx=100.0+pianx-10;qy=180.0+pianx-10;k=0.33;
 	setcolor(7);
 	rectangle((int)(pianx-2),(int)(piany-2),(int)((tx+jx)*8+2+pianx),302+piany);
 	setcolor(1);
 	rectangle((int)(pianx-1),(int)(piany-1),(int)((tx+jx)*8+1+pianx),301+piany);
 	/*读取盘面情况*/
 	p=fopen("record.dat", "r");
 	for(i=0;i<5;i++)
 		fscanf(p,"%x ",&zhuan[i]);
 	fclose(p);
 	/*画砖块*/
 	for(i=0;i<5;i++)
 	{
 		l=1;
  		for(j=0;j<16;j++)
  		{
  			if((zhuan[i]&l)==0)
   			{
   				Draw((int)((jx+tx)*((16*i+j)%8)+pianx+jx),(int)((jy+ty)*((int)((16*i+j)/8))+piany+jy),(int)tx,(int)ty);
    				sum+=1;
   			}
   			l=l*2;
  		}
 	}
	gotoxy(5,4);
	printf("Press any key to start game...Q key to quit...");
	ch=getch();
	if(ch=='q'||ch=='Q')
		quitgame();
	else
	{
		gotoxy(5,4);
		printf("                                              ");
	}

 	for(;;)
	{
		setfillstyle(1, 0);
  		bar(mx-bx/2,my,mx+bx/2,my+5);
  		Msread(&mx, &my, &mb);

  		Draw(mx-bx/2,my,bx,5);
  		setcolor(0);
		mycircle(qx,qy,r,0);
  		/*判断求是否反弹*/
  		if(qx-r<=pianx+1 || qx+r>=(tx+jx)*8+pianx-1)
  		{
  			flag=-flag;
  			k=-k;
  		}
  		if(qy-r<=piany+1)
  			k=-k;

  		for(gi=0;gi<5;gi++)
  		{
  			l=1;
  			for(gj=0;gj<16;gj++)
  			{
  				if((zhuan[gi]&l)==0)
    				{
    					j=(16*gi+gj)/8;
     					i=(16*gi+gj)%8;
     					x=(jx+tx)*i+jx+tx/2+pianx;
     					y=(jy+ty)*j+jy+ty/2+piany;
     					/*边判断1*/
     					if(qy>=y-ty/2 && qy<=y+ty/2 &&(pow(qx+r-x+tx/2,2)<1 || pow(qx-r-x-tx/2,2)<1))
      					{
      						flag=-flag;
      						k=-k;
       						zhuan[gi]=zhuan[gi]|l;
       						sum-=1;
       						if(sum==0)
       							wingame();
       						setfillstyle(1, 0);
       						bar((jx+tx)*i+pianx+jx,(jy+ty)*j+piany+jy,(jx+tx)*i+pianx+jx+tx,(jy+ty)*j+piany+jy+ty);
      					}
      					else
      					/*边判断2*/
     					if(qx>=x-tx/2 && qx<=x+tx/2 &&(pow(qy+r-y+ty/2,2)<1 || pow(qy-r-y-ty/2,2)<1))
      					{
      						k=-k;
       						zhuan[gi]=zhuan[gi]|l;
       						sum-=1;
       						if(sum==0)
       							wingame();
       						setfillstyle(1, 0);
       						bar((jx+tx)*i+pianx+jx,(jy+ty)*j+piany+jy,(jx+tx)*i+pianx+jx+tx,(jy+ty)*j+piany+jy+ty);
      					}
      					else
      					/*角判断*/
     					if(pow(qx-x+tx/2,2)+pow(qy-y+ty/2,2)<=r*r || pow(qx-x-tx/2,2)+pow(qy-y+ty/2,2)<=r*r || pow(qx-x+tx/2,2)+pow(qy-y-ty/2,2)<=r*r || pow(qx-x-tx/2,2)+pow(qy-y-ty/2,2)<=r*r)
      					{
      						flag=-flag;
       						zhuan[gi]=zhuan[gi]|l;
       						sum-=1;
       						if(sum==0)
       							wingame();
       						setfillstyle(1, 0);
       						bar((jx+tx)*i+pianx+jx,(jy+ty)*j+piany+jy,(jx+tx)*i+pianx+jx+tx,(jy+ty)*j+piany+jy+ty);
      					}
     				}
     				l=l*2;
     			}
     		}
  		/*棍棒的反弹*/
  		if(qx<=mx+bx/2 && qx>=mx-bx/2 && pow(qy+r-my,2)<1)
  		{
  			k=-(k/pow(k*k,0.5))*(0.3*bx/(pow(pow(qx-mx,2),0.5)+0.000001));
  		}
  		if((int)(qy+r)>my+0.5)
  		{
			gotoxy(5,5);
  			printf("You have lost the game!Press any key to restart...");
  			getch();
  			goto star;
  		}
  		b=qy-qx*k;
  		if(flag==1)
  			qx=qx+speech/pow(1.0+k*k,0.5);
  		if(flag==-1)
  			qx=qx-speech/pow(1.0+k*k,0.5);
  		qy=qx*k+b;/*计算球心坐标*/
  		setcolor(14);
		mycircle((int)qx,(int)qy,r,14);
  		delay(1);
  		if(mb==1)
  		{
			gotoxy(5,5);
  			printf("You have lost the game!Press any key to restart...");
  			getch();
  			goto star;
  		}
 	}
}