LRESULT CALLBACK wndproc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
  static HWND hwndbutton,hwndbutton1,hwndbutton2,hwndbutton3,hwndedit,hwndedit1,hwndedit2,hwndedit3;
  HDC hdc;
  PAINTSTRUCT ps;
  static HINSTANCE hInstance;
  static int speed=600;
  static int pause=1;
  int line;
  switch(message)
  {
  case WM_CREATE:
	  {
	   //PlaySound(TEXT("1/神话主题曲.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	   color[0]=CreateSolidBrush(RGB(0,0,0));  //白刷
	   color[1]=CreateSolidBrush(RGB(0,255,0)); //绿刷
	   color[2]=CreateSolidBrush(RGB(255,0,0));  //红刷
	   hwndbutton=CreateWindow(TEXT("BUTTON"),TEXT("暂停"),WS_CHILD|WS_VISIBLE,320,140,80,40,hwnd,(HMENU)1,hInstance,NULL);
	   hwndbutton1=CreateWindow(TEXT("BUTTON"),TEXT("退出"),WS_CHILD|WS_VISIBLE,320,200,80,40,hwnd,(HMENU)2,hInstance,NULL);
	   hwndbutton2=CreateWindow(TEXT("BUTTON"),TEXT("新游戏"),WS_CHILD|WS_VISIBLE,320,260,80,40,hwnd,(HMENU)3,hInstance,NULL);
	   hwndbutton3=CreateWindow(TEXT("BUTTON"),TEXT("确定"),WS_CHILD|WS_VISIBLE,320,450,80,30,hwnd,(HMENU)4,hInstance,NULL);
	   hwndedit=CreateWindow(TEXT("EDIT"),TEXT("分数:0"),WS_CHILD|WS_VISIBLE|ES_READONLY,320,320,80,20,hwnd,(HMENU)5,hInstance,NULL);
	   hwndedit1=CreateWindow(TEXT("EDIT"),TEXT("等级:1"),WS_CHILD|WS_VISIBLE|ES_READONLY,320,350,80,20,hwnd,(HMENU)6,hInstance,NULL);
	   hwndedit2=CreateWindow(TEXT("EDIT"),TEXT(""),WS_CHILD|WS_VISIBLE,320,380,80,20,hwnd,(HMENU)7,hInstance,NULL);
       hwndedit3=CreateWindow(TEXT("EDIT"),TEXT(""),WS_CHILD|WS_VISIBLE|ES_READONLY,320,410,80,20,hwnd,(HMENU)8,hInstance,NULL);
	   SetTimer(hwnd,1,speed,NULL);
	   SetTimer(hwnd,2,400,timerProc);
       return 0;
	  }
  case WM_PAINT:
	  {
		hdc=BeginPaint(hwnd,&ps); 
	    hua(hdc);
		load(hdc);
		huabk(hdc,300,0,0,460);
		huabk(hdc,0,0,0,460);
		Init();
		tuxing(hdc,Pos.dir,Pos.sharp,220,20,1);
		tuxing(hdc,Pos.dir,Pos.sharp,0,0,1);
		EndPaint(hwnd,&ps);
	    return 0;
	  }
  case WM_TIMER:
	  { 
		hdc=GetDC(hwnd);
		if(check(Pos.dir,Pos.sharp,Pos.x,Pos.y+20))
		{
		tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,0);
		Pos.y=Pos.y+20;
        tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,1);
		}
	    else
		{
		  if(gameover())
		  {
		  PlaySound(TEXT("1/luodi.wav"),NULL,SND_FILENAME|SND_ASYNC);
		  line=save(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y);
		  if(line==1)
		  {
		  TCHAR fs[256];
		  f+=10;
		  wsprintf(fs,"分数:%d",f);
		  SetDlgItemText(hwnd,5,fs);
		  if(f==100)
		  {
		   TCHAR dj1[256];
           dj++;
		   wsprintf(dj1,"等级:%d",dj);
		   SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==200)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==400)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==800)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		   if(f==1000)
		   {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		   }
		   if(f==2000)
		   {
			KillTimer(hwnd,1);
			MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
			ZeroMemory(cfk,sizeof(cfk));
			InvalidateRect(hwnd,NULL,FALSE);
		   }
		  }
		  else if(line>=2&&line<4)
		  {
          TCHAR fs[256];
		  f+=20;
		  wsprintf(fs,"分数:%d",f);
		  SetDlgItemText(hwnd,5,fs);
		  if(f==100)
		  {
		   TCHAR dj1[256];
           dj++;
		   wsprintf(dj1,"等级:%d",dj);
		   SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==200)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==400)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==800)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		   if(f==1000)
		   {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		   }
		   if(f==2000)
		   {
			KillTimer(hwnd,1);
			MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
			ZeroMemory(cfk,sizeof(cfk));
			InvalidateRect(hwnd,NULL,FALSE);
		   }
		  }
		  else if(line>=4&&line<8)
		  {
		  TCHAR fs[256];
		  f+=40;
		  wsprintf(fs,"分数:%d",f);
		  SetDlgItemText(hwnd,5,fs);
		  if(f==100)
		  {
		   TCHAR dj1[256];
           dj++;
		   wsprintf(dj1,"等级:%d",dj);
		   SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==200)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==400)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==800)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		   if(f==1000)
		   {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		   }
		   if(f==2000)
		   {
			KillTimer(hwnd,1);
			MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
			ZeroMemory(cfk,sizeof(cfk));
			InvalidateRect(hwnd,NULL,FALSE);
		   }
		  }
		  else if(line>=8)
		  {
		  TCHAR fs[256];
		  f+=160;
		  wsprintf(fs,"分数:%d",f);
		  SetDlgItemText(hwnd,5,fs);
		  if(f==100)
		  {
		   TCHAR dj1[256];
           dj++;
		   wsprintf(dj1,"等级:%d",dj);
		   SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==200)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==400)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		  if(f==800)
		  {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		  }
		   if(f==1000)
		   {
		  TCHAR dj1[256];
          dj++;
		  wsprintf(dj1,"等级:%d",dj);
		  SetDlgItemText(hwnd,6,dj1);
		   }
		   if(f==2000)
		   {
			KillTimer(hwnd,1);
			MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
			ZeroMemory(cfk,sizeof(cfk));
			InvalidateRect(hwnd,NULL,FALSE);
		   }
		  }
          Init();
		  speed=600;
		  SetTimer(hwnd,1,speed,NULL);
		  InvalidateRect(hwnd,0,FALSE);
		  }
		  else
		{
		 KillTimer(hwnd,1);
		 PlaySound(TEXT("1/结束.wav"),NULL,SND_FILENAME|SND_ASYNC);
		 int i=MessageBox(NULL,TEXT(".......@_@是否重来@_@......"),TEXT("提示"),MB_OKCANCEL);
		 if(i==IDOK)
		 {
		  ZeroMemory(cfk,sizeof(cfk));
		  InvalidateRect(hwnd,0,FALSE);
		  SetTimer(hwnd,1,speed,NULL); 
		 }
		}
		}
		ReleaseDC(hwnd,hdc);
	    return 0;
	  }
  case WM_KEYDOWN:
	  {
		hdc=GetDC(hwnd);
		switch(wParam)
	   {
	   case VK_UP:
	   case VK_SPACE:
		   { 
			 if(check(Pos.dir,(Pos.sharp+1)%4,Pos.x,Pos.y))   //同个函数传替的参数值不同，其每个函数返回的值也不同。
			 {
			 PlaySound(TEXT("1/xuanzhuan.wav"),NULL,SND_FILENAME|SND_ASYNC);
			 tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,0);
			 ++Pos.sharp%=4;  //使用两个tuxing函数，第一个的颜色与背景颜色一样，另一个就是本身颜色
			 tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,1);
			 }
		     return 0;
		   }
	   case VK_LEFT:
		   {
			if(check(Pos.dir,Pos.sharp,Pos.x-20,Pos.y))
			{
			PlaySound(TEXT("1/xuanzhuan.wav"),NULL,SND_FILENAME|SND_ASYNC);
			tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,0);
			Pos.x-=20;
			tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,1);
			}
			return 0;
		   }
	   case VK_RIGHT:
		   {
			if(check(Pos.dir,Pos.sharp,Pos.x+20,Pos.y))
			{
			PlaySound(TEXT("1/xuanzhuan.wav"),NULL,SND_FILENAME|SND_ASYNC);
		    tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,0);
			Pos.x+=20;
			tuxing(hdc,Pos.dir,Pos.sharp,Pos.x,Pos.y,1);
			}
			return 0;
		   }
	   case VK_DOWN:
		   {
			PlaySound(TEXT("1/xuanzhuan.wav"),NULL,SND_FILENAME|SND_ASYNC);
		    speed=100;
			SetTimer(hwnd,1,speed,NULL);
		   }
	   }
	   ReleaseDC(hwnd,hdc);
	   return 0;
	  }
  case WM_COMMAND:
	  {
	   switch(LOWORD(wParam))
	   {
	   case 1:
		   {
			 if(gameover())
			 {
			 if(pause)
			 {
			  PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			  KillTimer(hwnd,1);
			  SetWindowText(hwndbutton,TEXT("继续"));
			 }
             else
			 {
			  PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			  SetTimer(hwnd,1,speed,NULL);
			  SetWindowText(hwndbutton,TEXT("暂停"));
			  SetFocus(hwnd); //把输入焦点换回到主窗口
			 }
			 ++pause%=2;
			 }
			 return 0;
		   }
	   case 2:
		   {
			PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			KillTimer(hwnd,1);
			int i=MessageBox(hwnd,TEXT("确定要退出吗?"),TEXT("提示"),MB_OKCANCEL);
			if(i==IDOK)
			{
            KillTimer(hwnd,1);
	        PostQuitMessage(0);
			}
			else
			{
			 PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			 SetTimer(hwnd,1,speed,NULL);
			}
		    return 0;
		   }
	   case 3:
		   {
			PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			KillTimer(hwnd,1);
			int i=MessageBox(hwnd,TEXT("确定要重新开始吗?"),TEXT("提示"),MB_OKCANCEL);
			if(i==IDOK)
			{
			ZeroMemory(cfk,sizeof(cfk));
			InvalidateRect(hwnd,NULL,FALSE);
			SetTimer(hwnd,1,speed,NULL); 
			}
			else
			{
			 PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
			 SetTimer(hwnd,1,speed,NULL);
			}
			return 0;
		   }
	   case 4:
		   {
           ZeroMemory(str,sizeof(str));
           GetDlgItemText(hwnd,7,str,sizeof(str)/sizeof(TCHAR));
           SetFocus(hwnd);
		   return 0;
		   }
	   case ID_MENUITEM40001:
		   {
			PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
            KillTimer(hwnd,1);
			MessageBox(hwnd,TEXT("1.游戏简单,不过功能也齐全.\n"
				                 "2.此游戏可能和其他的有点不\n"
								 "  同之处,其他的都是以分数来玩\n"
								 "3.的!而我的不同之处是以时间\n"
								 "  来玩的!根据时间来换取不同的\n"
								 "  音乐!时间越久速度也越快!@_@\n"),TEXT("说明"),MB_OK);
			SetTimer(hwnd,1,speed,NULL);
		    return 0;
		   }
	   case ID_MENUITEM40002:
		   {
			PlaySound(TEXT("1/Pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
		    KillTimer(hwnd,1);
			MessageBox(hwnd,TEXT("通过此游戏的编程,让我知道许多知识.\n"
				                  "特别是POINT结构体,以及数组的使用...\n"  
								  "也要感谢帮助过我的人,特别是我的网友\n"
								  "和她.非常感谢了!!!我会继续努力的!!!"),TEXT("感言"),MB_OK);
			SetTimer(hwnd,1,speed,NULL);
			return 0;
		   }
	   }
	   return 0;
	  }
  case WM_DESTROY:
	  {
	   KillTimer(hwnd,1);
	   KillTimer(hwnd,2);
	   PostQuitMessage(0);
	   return 0;
	  }
  }
  return DefWindowProc(hwnd,message,wParam,lParam);
}