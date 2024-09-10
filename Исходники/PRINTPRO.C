void InitSubPage(HWND Window,int pt_w,int pt_h,int pg_w,int pg_h)
{
   HWND Mid;
   int xw,yw,i,j;
   char p[40];
   int SaveColor;
   struct viewporttype SaveViewPort;


   WaitMessageEmpty();

   MouseHidden();
   getviewsettings(&SaveViewPort);
   SaveColor=getcolor();

   Mid=WindowGetFather(Window);
   ScreenDispWidth=WindowGetWidth(Window)-10;
   ScreenDispHeight=WindowGetHeight(Window)-10;
   WinX=ScreenX=WindowGetLeft(Window)+WindowGetLeft(Mid);
   WinY=ScreenY=WindowGetTop(Window)+WindowGetTop(Mid);

   setviewport(WinX,WinY,WinX+ScreenDispWidth+9,WinY+ScreenDispHeight+9,1);
   setwritemode(COPY_PUT);
   setcolor(EGA_WHITE);
   bar(0,0,ScreenDispWidth+9,ScreenDispHeight+9);

   SCRscaleX=SubP->TotalX/ScreenDispWidth*1.05;
   SCRscaleY=SubP->TotalY/ScreenDispHeight*1.05;

   if (SCRscaleX>SCRscaleY)
        SCRscaleY=SCRscaleX;
   else
        SCRscaleX=SCRscaleY;

   xw=mXw=pg_w/SCRscaleX;
   yw=mYw=pg_h/SCRscaleY;

   ScreenX=ScreenX+5+(ScreenDispWidth-mXw)/2;
   ScreenY=ScreenY+5+(ScreenDispHeight-mYw)/2;

   //setcolor(EGA_DARKGRAY);       //gray
   setcolor(12);
   setviewport(0,0,getmaxx(),getmaxy(),1);
   rectangle(ScreenX,ScreenY,ScreenX+xw,ScreenY+yw);

   setviewport(WinX,WinY,WinX+ScreenDispWidth+9,WinY+ScreenDispHeight+9,1);

   for (i=0;i<PG.Blocks;i++)
   {
      int x0,x1,y0,y1;
      mXw=ScreenX-WinX;
      mYw=ScreenY-WinY;
      x0=-PG.PageBlock[i].Xoffset*1000/25.4/SCRscaleX+mXw;
      y0=-PG.PageBlock[i].Yoffset*1000/25.4/SCRscaleY+mYw;
      x1=x0+pt_w/SCRscaleX;
      y1=y0+pt_h/SCRscaleY;
      if (PG.PageBlock[i].Reveser&1)
        setcolor(14);
      else
        setcolor(11);
      rectangle(x0,y0,x1,y1);
   }

   setwritemode(COPY_PUT);
   setcolor(SaveColor);
   setviewport(SaveViewPort.left,SaveViewPort.top,SaveViewPort.right,
              SaveViewPort.bottom,SaveViewPort.clip);
   MouseShow();

}