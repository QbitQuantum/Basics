 ////////////////////////////*BARS*///////////////////////////////////////////////
 number()
 {  cleardevice();

  rectangle(500,130,580,150);outtextxy(503,133,"EXIT");

  rectangle(200,100,400,300);

    for(a=100;a<300;a=a+50)
    {
      line(200,a,400,a);
    }
    for(a=200;a<400;a=a+50)
    {
      line(a,100,a,300);
    }
    while(b<=15)
    {
     r=random1();r++;
     h=random2();h++;
     switch(h)
     {
       case 1:x=225;y=125;break;
       case 2:x=225;y=175;break;
       case 3:x=225;y=225;break;
       case 4:x=225;y=275;break;
       case 5:x=275;y=125;break;
       case 6:x=275;y=175;break;
       case 7:x=275;y=225;break;
       case 8:x=275;y=275;break;
       case 9:x=325;y=125;break;
       case 10:x=325;y=175;break;
       case 11:x=325;y=225;break;
       case 12:x=325;y=275;break;
       case 13:x=375;y=125;break;
       case 14:x=375;y=175;break;
       case 15:x=375;y=225;break;
       case 16:x=375;y=275;break;
     }
     if(r==16)
     {
       ex=x;ey=y;
     }
     switch(r)
     {
       case 1: outtextxy(x,y,c1); break;
       case 2: outtextxy(x,y,c2);break;
       case 3: outtextxy(x,y,c3);break;
       case 4: outtextxy(x,y,c4);break;
       case 5: outtextxy(x,y,c5);break;
       case 6: outtextxy(x,y,c6);break;
       case 7: outtextxy(x,y,c7);break;
       case 8: outtextxy(x,y,c8);break;
       case 9: outtextxy(x,y,c9);break;
       case 10: outtextxy(x,y,c10);break;
       case 11: outtextxy(x,y,c11);break;
       case 12: outtextxy(x,y,c12);break;
       case 13: outtextxy(x,y,c13);break;
       case 14: outtextxy(x,y,c14);break;
       case 15: outtextxy(x,y,c15);break;
       case 16: outtextxy(x,y,c16);break;
     }
    b++;
     }
      showmouseptr();
   while(flag==0)
   {
       getmousepos(&button,&x,&y);

	if(button==1&&x>500&&x<580&&y>130&&y<150)exit(0);


 /////////////////main logic//////////////
	if(button==1&&((x>ex-75&&x<ex-25&&y<ey+25&&y>ey-25)||(x>ex-25&&x<ex+25&&y<ey-25&&y>ey-75)||(x>ex+25&&x<ex+75&&y>ey-25&&y<ey+25)||(x>ex-25&&x<ex+25&&y>ey+25&&y<ey+75))&&(x>200&&x<400&&y<300&&y>100))
       {  cx=x-(x%50);cy=y-(y%50);
	  size=imagesize(cx+2,cy+2,cx+48,cy+48);
	  buf=malloc(size);
	  hidemouseptr();
	  getimage(cx+2,cy+2,cx+48,cy+48,buf);
	  putimage(ex-23,ey-23,buf,0);
	  free(buf);
	  setfillstyle(SOLID_FILL,GREEN);
	  bar(cx+2,cy+2,cx+48,cy+48);
	  ex=cx+25;ey=cy+25;
	  showmouseptr();
       }
/////////////////

    }


  return(0);
  }