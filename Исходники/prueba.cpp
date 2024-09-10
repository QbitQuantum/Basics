main()
{
   int gd = DETECT,gm;
 
   int maxx,maxy,x,y,button,prevx,prevy,temp1,temp2,key,color;
   char ch = 'f' ;            // default free-hand drawing
 
   initgraph(&gd,&gm,"C:\\TC\\BGI");
 
   maxx = getmaxx();
   maxy = getmaxy();
 
   setcolor(BLUE);
   rectangle(0,0,maxx,maxy);
 
   setcolor(WHITE);
   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
   outtextxy(maxx/2-180,maxy-28,"<a href="http://www.programmingsimplified.com"">www.programmingsimplified.com"</a>);
 
   draw_color_panel();
   draw_shape_panel();
 
   setviewport(1,1,maxx-1,maxy-1,1);
 
   restrictmouseptr(1,1,maxx-1,maxy-1);
   showmouseptr();
   rectangle(2,2,518,427);
   setviewport(1,1,519,428,1);
 
   while(1)
   {
      if(kbhit())
      {
         key = get_key();
 
         if( key == 1 )
         {
            closegraph();
            exit(0);
         }
      }
 
      getmousepos(&button,&x,&y);
 
      if( button == 1 )
      {
         if( x > 4 && x < 635 && y > 431 && y < 457 )
            change_color( x, y );
         else if ( x > 529 && x < 625 && y > 40 && y < 250 )
             ch = change_shape( x, y );
 
         temp1 = x ;
         temp2 = y ;
 
         if ( ch == 'f' )
         {
            hidemouseptr();
            while( button == 1 )
            {
               line(temp1,temp2,x,y);
               temp1 = x;
               temp2 = y;
               getmousepos(&button,&x,&y);
            }
            showmouseptr();
         }
 
         while( button == 1)
            getmousepos(&button,&x,&y);
 
         /* to avoid interference of mouse while drawing */
         hidemouseptr();
 
         if( ch == 'p')
            putpixel(x,y,getcolor());
 
         else if ( ch == 'b' )
         {
            setfillstyle(SOLID_FILL,getcolor());
            bar(temp1,temp2,x,y);
         }
         else if ( ch == 'l')
            line(temp1,temp2,x,y);
         else if ( ch == 'e')
            ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));
         else if ( ch == 'r' )
            rectangle(temp1,temp2,x,y);
         else if ( ch == 'c' )
         {
            ch = 'f';          // setting to freehand drawing
            clearviewport();
            color = getcolor();
            setcolor(WHITE);
            rectangle(2,2,518,427);
            setcolor(color);
         }
 
         showmouseptr();
      }
   }
}