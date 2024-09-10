void shakil::show()
{
 hidemouseptr();
 setcolor(123);

 for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 {
   if(vm[i][j]==10)
   {setcolor(123);
   rectangle(xp1[i][j],yp1[i][j],xp2[i][j],yp2[i][j]);
   setfillstyle(SOLID_FILL,123);
   floodfill(xp1[i][j]+2,yp1[i][j]+2,123);
     }
    if(vm[i][j]==5)
    {setcolor(7);
     rectangle(xp1[i][j],yp1[i][j],xp2[i][j],yp2[i][j]);
      setfillstyle(SOLID_FILL,7);
     floodfill(xp1[i][j]+2,yp1[i][j]+2,7);

    }
   if(vm[i][j]==0)
   { setcolor(BLACK);
     rectangle(xp1[i][j],yp1[i][j],xp2[i][j]+(c12/2),yp2[i][j]+(c12/2));
     setfillstyle(SOLID_FILL,BLACK);
     floodfill(xp1[i][j]+2,yp1[i][j]+2,BLACK);
     line(xp1[i][j],yp2[i][j],xp1[i][j]+(c12/2),yp2[i][j]+(c12/2));
    line(xp2[i][j],yp1[i][j],xp2[i][j]+(c12/2),yp1[i][j]+(c12/2));
   }
   if(vm[i][j]==5||vm[i][j]==10)
   {
    setcolor(RED);
    p=res1[i][j]/100;
    if(p>0)
    {switch(p)
    {case 0:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"0");
	  break;
      case 1:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"1");
	  break;

    case 2:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"2");
	  break;
    case 3:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"3");
	  break;
   case 4:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"4");
	  break;
    case 5:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"5");
	  break;
    case 6:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"6");
	  break;
    case 7:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"7");
	  break;
    case 8:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"8");
	  break;
    case 9:
	  outtextxy(xp1[i][j]+1,(yp1[i][j]+yp2[i][j])/2-10,"9");
	  break;
    }

    }
    m=res1[i][j]/10;
    if(m>9)
    m=m-p*10;
    if(m>0||p>0)
    {switch(m)
    {case 0:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"0");
	  break;
    case 1:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"1");
	  break;

    case 2:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"2");
	  break;
    case 3:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"3");
	  break;
    case 4:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"4");
	  break;
    case 5:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"5");
	  break;
    case 6:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"6");
	  break;
    case 7:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"7");
	  break;
    case 8:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"8");
	  break;
    case 9:
	  outtextxy(xp1[i][j]+10,(yp1[i][j]+yp2[i][j])/2-10,"9");
	  break;



    }

    }
    m=res1[i][j]%10;
    switch(m)
    {case 0:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"0");
	  break;
      case 1:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"1");
	  break;

    case 2:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"2");
	  break;
    case 3:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"3");
	  break;
    case 4:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"4");
	  break;
    case 5:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"5");
	  break;
    case 6:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"6");
	  break;
    case 7:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"7");
	  break;
    case 8:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"8");
	  break;
    case 9:
	  outtextxy(xp1[i][j]+20,(yp1[i][j]+yp2[i][j])/2-10,"9");
	  break;



    }
    setcolor(8);
    line(xp1[i][j]+(c12/2),yp2[i][j]+(c12/2),xp2[i][j]+(c12/2),yp2[i][j]+(c12/2));
    line(xp2[i][j]+(c12/2),yp1[i][j]+(c12/2),xp2[i][j]+(c12/2),yp2[i][j]+(c12/2));
    line(xp1[i][j],yp2[i][j],xp1[i][j]+(c12/2),yp2[i][j]+(c12/2));
    line(xp2[i][j],yp1[i][j],xp2[i][j]+(c12/2),yp1[i][j]+(c12/2));
    // setfillstyle(SOLID_FILL,8);
   //  floodfill(xp2[i][j],yp2[i][j]+2,8);
    }
	}
    setcolor(123);
    rectangle(xp1[0][0]-c12,yp1[0][0]-c12,xp2[n-1][n-1]+c12,yp2[n-1][n-1]+c12);
    setcolor(2);
    rectangle(470,370,520,390);
    setfillstyle(SOLID_FILL,2);
    floodfill(477,376,2);
    setcolor(RED);
    outtextxy(476,369,"EXIT");
    setcolor(2);
    rectangle(470,270,520,290);
    setfillstyle(SOLID_FILL,2);
    floodfill(477,276,2);
    setcolor(RED);
    outtextxy(473,270,"SAVE");
    showmouseptr();

}