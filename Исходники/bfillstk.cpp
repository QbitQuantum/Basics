void boundryfill(int seedx,int seedy,int boundry,int color)
{Point p(seedx,seedy);
 s.push(p);
 do
 {p=s.pop();
  if(getpixel(p.x,p.y)==boundry) continue;
  while(getpixel(p.x,p.y)!=boundry)p.x--;
  p.x++;
  int flagup=false,flagdown=false;
  int cup,cdwn;
  while(getpixel(p.x,p.y)!=boundry)
  {cup=getpixel(p.x,p.y-1);
   cdwn=getpixel(p.x,p.y+1);
   if(cup==boundry||cup==color) flagup=false;
   else if(!flagup)
   {flagup=true;
    s.push(Point(p.x,p.y-1));
    }
  if(cdwn==boundry||cdwn==color) flagdown=false;
   else if(!flagdown)
   {flagdown=true;
    s.push(Point(p.x,p.y+1));
    }
  putpixel(p.x,p.y,color);
  p.x++;
  }
 }while(!s.isempty());
 s.reset();
}