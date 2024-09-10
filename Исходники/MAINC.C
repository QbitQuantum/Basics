static int SystemConstruct(void)
{
  int Result;
  int x,y;

  _harderr(handler);

  ReadDefaultScreenMode();

  if ((Result=LockMouseMemory())<0)
     return(Result);

  TimerInit();
  HandleInitial();
  if ((Result=ChineseLibInitial())<0)
     return(Result);
  if ((Result=ItemInitial())<0)
     return(Result);

  x=getmaxx();  y=getmaxy();
    if ((Result=WindowInitial(x,y-30))<0)
     return(Result);

  if ((Result=GraphInitial())<0)
     return(Result);

  if ((Result=MouseConstruct(x,y))<0 && !fEditor) {
   #ifdef OLD_VERSION
     //printf("I can't find mouse or mouse driver. Press a key ...\n");
     static char MouseErrMsg[]="ÇëÏÈ°²×°Êó±êÇý¶¯³ÌÐò¡£°´<Esc>ÍË³ö¡­¡­";
     DisplayString(MouseErrMsg,(x-strlen(MouseErrMsg)*ASC16WIDTH)/2,y/2,
               EGA_LIGHTRED,getbkcolor());
     fflush(stdout);
     getch();
     return(Result);
   #else
     static char MouseErrMsg1[]="Î´°²×°Êó±êÇý¶¯³ÌÐò(ÓÐÐ©¹¦ÄÜ±ØÐëÓÉ";
     static char MouseErrMsg2[]="Êó±ê²ÅÄÜÍê³É)! Äú¿ÉÍË³öÏµÍ³, ÏÈÔËÐÐÊó";
     static char MouseErrMsg3[]="±êÇý¶¯³ÌÐò, Èç:   AMOUSE     [»Ø³µ]";
     static char MouseErrMsg4[]="ÈôÊó±ê×°ÔÚ´®¿Ú¶þÉÏ, Ôò¼üÈë:  AMOUSE/2";
     static char MouseErrMsg5[]="ÏÖÔÚÄú¿É°´<Esc>ÍË³ö, ±ðµÄ¼ü½«¼ÌÐø";
     int disp_x=x/2-(strlen(MouseErrMsg2)+4)*ASC16WIDTH/2;
     int disp_y=y/2-10;

     DisplayString(MouseErrMsg1,disp_x+4*ASC16WIDTH,disp_y-3*ASC16HIGHT-4,
               EGA_WHITE,EGA_BLACK);
     DisplayString(MouseErrMsg2,disp_x,disp_y-2*ASC16HIGHT,
               EGA_WHITE,EGA_BLACK);
     DisplayString(MouseErrMsg3,disp_x,disp_y-1*ASC16HIGHT+4,
               EGA_WHITE,EGA_BLACK);
     DisplayString(MouseErrMsg4,disp_x,disp_y-0*ASC16HIGHT+8,
               EGA_WHITE,EGA_BLACK);
     DisplayString(MouseErrMsg5,disp_x,disp_y+1*ASC16HIGHT+20,
               EGA_WHITE,EGA_BLACK);
     fflush(stdout);
     Result=getch();
     if(Result==0) getch();
     else if(Result==ESC) return(-1);

     while (kbhit()) getch();
   #endif
  }

 #ifdef NOT_USED
  if (EMMTest())
    {
        if (EMMMessage()<0) return -1;
    }
 #endif

/*--------
  if ((Result=KeySpeed())<0)
     return(Result);
----*/
  PageInitial();

  if ((Result=FontInitial())<0)
     return(Result);

  InitCache();
  init_paper();             //By zjh

  GetFaxConfig();
  ReturnOK();
}