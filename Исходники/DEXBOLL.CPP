void show()
{
  cleardevice();
  setcolor(RED);
  rectangle(40,40,600,450);

  setcolor(RED);
  line(sa[0],sa[1],sa[2],sa[3]);
  rectangle(sa[0],sa[1],sa[2],sa[3]+5);
  setfillstyle(SOLID_FILL,RED);
  floodfill((sa[0]+sa[2])/2,(sa[1]+sa[3]+5)/2,RED);
  circle(sa1[0],sa1[1],r1);
  setfillstyle(SOLID_FILL,RED);
  floodfill(sa1[0]+1,sa1[1]+1,RED);
  setcolor(RED);
  for(i=0;i<30;i++)
  if(bool3[i]==1)
  { setcolor(rand()%5+1);
   circle(bool1[i],bool2[i],28);
    }

  for(i=0;i<kk;i++)
  {if(sin3[i]!=0)
   if(sin2[i]<=445)
   { sin2[i]=sin2[i]+5;
     circle(sin1[i],sin2[i],sin3[i]);
     switch(sin3[i])
     {case 12:outtextxy(sin1[i]-5,sin2[i],"+1");
	      break;
     case 14:outtextxy(sin1[i]-5,sin2[i],"-1");
	     break;
     case 16:outtextxy(sin1[i]-5,sin2[i],"+");
	      break;
     case 18: outtextxy(sin1[i]-5,sin2[i],"-");
	      break;
     case 8:outtextxy(sin1[i]-5,sin2[i],"@");
	     break;
     case 10:outtextxy(sin1[i]-5,sin2[i],"*");
	     break;
     case 6:outtextxy(sin1[i]-2,sin2[i],"O");
	     break;
     case 4:outtextxy(sin1[i]-1,sin2[i],"o");
	     break;
     }
    if(sin1[i]>=sa[0]&&sin1[i]<=sa[2])
    {
     if(sin2[i]+sin3[i]>=sa[1])
    {
     switch(sin3[i])
    {case 12:li=li+1;break;
     case 14:outtextxy(140,350,"LIFE LOSE");
	     li=li-1;score=score-50;
	     delay(2000);
	     if(li==0)
	    {cleardevice();
	     outtextxy(140,380,"GAME OVER AND YOUR SCORE");
	     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n            %ld",score);
	     delay(4000);

	     fil();
	       }
	     get();
	     break;
     case 16:r=r*2;score=score+100;break;
     case 18:r=r/2;break;
     case 8:mn=20;score=score+100;break;
     case 10:powe=powe*powe;score=score+100;break;
     case 6:r1=r1*2;score=score+100;
	   break;
     case 4:r1=r1/2;
	    break;
     }

     sin3[i]=0;
     }}
   }
  }

}