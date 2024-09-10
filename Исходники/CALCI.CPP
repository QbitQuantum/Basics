//start of main
void main()
{
//getch();
  initialize();      //initialises graphics mode
  setcolor(RED);     //sets text color red
  mainscreen();      //draws format for calculator
  mouse m;           //creates mouse object
  char string[100];
  int button,xx,yy,flag=0,index,i;
  int counter;
  int matrix[5][3]={{0,1,2},{3,4,5},{6,7,8},{9,10,11},{12,13,14}};
  int count=0;
  //setviewport(70,70,getmaxx()-80,100,1);
  //clearviewport();
  long double num[100],ii=0,rcount=0;
  drawscreen();         //creates output screen
  while(1)
  {


  counter=150;
  button=0;
  m.getmousepos(button,xx,yy);        //gets x&y position of mouse ptr

  if(((button & 1)==1)&&(flag==0))
    {
	for(int k=0;k<5;k++)
		{
		for(int x=400,i=0;x<=5*100;x+=50,i++)
			{
			if(xx>=x && xx<=x+30 && yy>=counter&&yy<=counter+20)
				{
				index=matrix[k][i];
				flag=1;
				//cout<<index;
				//delay(200);
				goto end;
				}
			}
		   counter+=40;
		}

    }

    end:
    //(430,350,500,375);
    if(((button & 1)==1)&&(flag==0))
    {
    if(xx>=430&&xx<=500&&yy>=350&&yy<=375)
    index=50;
    flag=1;
    }
    switch(index)
    {



    case 50:
	m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	 exit(0);
	}

    case 0:

	m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	//setcolor(WHITE);
       drawscreen();
	setcolor(WHITE);


	string[count]='9';
	num[ii]=9;
	ii++;
	//outtextxy(getmaxx()-(5*count+200),70,string);

	count++;
	string[count]='\0';
	outtextxy(getmaxx()-(200+5*count),70,string );
	//delay(0);
	flag=0;
	}
	break;

    case 1:

	m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	//setcolor(WHITE);
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"8" );


	string[count]='8';
	count++;
	string[count]='\0';
		num[ii]=8;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 2:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"7" );
	string[count]='7';
	count++;
	string[count]='\0';
		num[ii]=7;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 3:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"6" );
	string[count]='6';
	count++;
	string[count]='\0';
		num[ii]=6;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 4:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
       //	outtextxy(getmaxx()-100,70,"5" );
       string[count]='5';
	count++;
	string[count]='\0';
		num[ii]=5;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 5:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"4" );
	string[count]='4';
	count++;
	string[count]='\0';
		num[ii]=4;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 6:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"3" );
	string[count]='3';
	count++;
	string[count]='\0';
		num[ii]=3;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 7:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//+outtextxy(getmaxx()-100,70,"2" );
	string[count]='2';
	count++;
	string[count]='\0';
		num[ii]=2;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 8:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"1" );
	string[count]='1';
	count++;
	string[count]='\0';
		num[ii]=1;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 9:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"0" );
	string[count]='0';
	count++;
	string[count]='\0';
		num[ii]=0;
	ii++;
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 10:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"+" );
	string[count]='+';
	count++;
	string[count]='\0';
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 11:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);
	//outtextxy(getmaxx()-100,70,"-" );
	string[count]='-';
	count++;
	string[count]='\0';
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 12:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	clearscreen();

	setcolor(WHITE);
	//string[count]='/';
	//count++;
	//outtextxy(getmaxx()-100,70,"%" );
       //	string[count]='\0';
   //	outtextxy(getmaxx()-(200+5*count),70,string );
	count=0;
	flag=0;
	}
	break;
    case 13:
	  m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{
	drawscreen();
	setcolor(WHITE);

	string[count]='*';
	count++;
	string[count]='\0';
	outtextxy(getmaxx()-(200+5*count),70,string );
	flag=0;
	}
	break;
    case 14:
	char s1[100],s2[100];
	char * s11,s22;
	long double value=0;

	long double n1=0,n2=0;
	m.getmousepos(button,xx,yy);
	if(((button & 1)==0) && (flag==1))
	{

	drawscreen();
	setcolor(WHITE);


	for(int k=0;k<count;k++)
	{
	if(string[k]=='+'||string[k]=='-'||string[k]=='*'||string[k]=='-')
	{
	for(int p=0,q=k-1;p<k;p++,q--)
	{
	n1+=(num[p]*(pow(10,q)));

	}

	for(p=k,q=(ii-k-1);p<count-1;p++,q--)
	{

	 n2+=(num[p]*(pow(10,q)));

	}
	if(string[k]=='+')
	{
	value=(double)(n1+n2);

	break;
	}
	if(string[k]=='-')
	{
	value=(double)(n1-n2);
	break;
	}
	if(string[k]=='*')
	{
	value=(double)(n1*n2);
	break;
	}
       /*	if(string[k]=='cls')
	{
	value=(double)(n1/n2);
	break;
	}*/
	}
	}

	int ndig=0,dec,sign;
	s11 = fcvt(value,ndig, &dec, &sign);//converts a num into string
       drawscreen();
       setcolor(WHITE);
	outtextxy(getmaxx()-(5*strlen(s11)+200),70,s11);
	rcount++;
	flag=0;
	count=0;

	ii=0;
	}
	break;

    }

  }
  //getch();
  restorecrtmode();       //restores textmode
}