void main()
{
  int ch;
  clrscr();
  while(1)
  {
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
    {
      printf("%d",errorcode);
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
    }
   cleardevice();
   setbkcolor(6);
   setcolor(15);
   settextstyle(1,0,1);
   sprintf(msg,"SRI JAYACHAMARAJENDRA COLLEGE OF ENGINEERING");
   outtextxy(75,10,msg);
   sprintf(msg,"MYSORE-570006");
   outtextxy(230,40,msg);
   sprintf(msg,"STUDENT DATABASE");
   outtextxy(220,100,msg);
   sprintf(msg,"1. INSERT A RECORD");
   outtextxy(200,200,msg);
   sprintf(msg,"2. ACCESS A RECORD");
   outtextxy(200,240,msg);
   sprintf(msg,"3. DELETE A RECORD");
   outtextxy(200,280,msg);
   sprintf(msg,"4. DISPLAY THE DATABASE");
   outtextxy(200,320,msg);
   sprintf(msg,"5. EXIT");
   outtextxy(200,360,msg);
   sprintf(msg," Please enter your choice:");
   outtextxy(220,400,msg);
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("\n\t\t\t\t\t");
   scanf("%d",&ch);
   clrscr();
   switch(ch)
      {
	      case 1:write();
		     break;
	      case 2:read();
		     break;
	      case 3:del();
		     break;
	      case 4:display();
		     break;
	      case 5:exit(0);
	      default:printf("Wrong Choice:Please enter a valid choice");
      }
      getch();
      closegraph();
    }
}