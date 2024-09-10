DWORD WINAPI netGameLoop(void *param)
{
	int len, c, x, y;
	Psquare p;
	TnetGameSettings *b;
	char *m, *u, *a;
	hostent *h;
	char buf[256];

	if(!param){
		buf[0]=(BYTE)C_INIT1;
		buf[1]=NETGAME_VERSION;
		wr(buf, 2);
		c=rd1();
		if(c!=C_INIT2) goto le;
		c=rd1();
		if(c<1) goto le;
		netGameVersion=c;
		SetForegroundWindow(hWin);
		h= gethostbyaddr((char*)&netGameIP.sin_addr, 4, netGameIP.sin_family);
		a= inet_ntoa(netGameIP.sin_addr);
		if(msg1(MB_YESNO|MB_ICONQUESTION,
			lng(868, "Do you want to play with %s [%s] ?"),
			(h && h->h_name) ? h->h_name : "???", a ? a : "???")!=IDYES){
			wr1(C_INIT_DENY);
			goto le;
		}
		buf[0]=(BYTE)C_INFO;
		buf[1]=sizeof(TnetGameSettings);
		b= (TnetGameSettings*)(buf+2);
		b->width=(char)width;
		b->height=(char)height;
		b->begin= (player==1);
		b->rule5=(char)ruleFive;
		b->cont=(char)continuous;
		if(netGameVersion<2) b->rule5=b->cont=0;
		wr(buf, 2+sizeof(TnetGameSettings));
		if(rd1()!=C_INFO_OK) goto le;
		b->begin= !b->begin;
	}
	else{
		buf[0]=(BYTE)C_INIT2;
		buf[1]=NETGAME_VERSION;
		wr(buf, 2);
		c=rd1();
		if(c==C_BUSY) wrLog(lng(874, "The other player is already playing with someone else"));
		if(c!=C_INIT1) goto le;
		c=rd1();
		if(c<1) goto le;
		netGameVersion=c;
		wrLog(lng(871, "Connection established. Waiting for response..."));
		c=rd1();
		if(c==C_INIT_DENY) wrLog(lng(870, "The other player doesn't want to play with you !"));
		if(c!=C_INFO) goto le;
		len=rd1();
		b= (TnetGameSettings*)buf;
		memset(buf, 0, sizeof(TnetGameSettings));
		if(len<2 || rd(buf, len)<0) goto le;
		wr1(C_INFO_OK);
	}
	SendMessage(hWin, WM_COMMAND, 992, (LPARAM)b);
	undoRequest=0;

	for(;;){
		x=rd1();
		switch(x){
			case C_MSG: //message
				len=rd2();
				if(len<=0) goto le;
				u=new char[2*len];
				if(rd(u, 2*len)>=0){
					m=new char[len+1];
					WideCharToMultiByte(CP_ACP, 0, (WCHAR*)u, len, m, len, 0, 0);
					m[len]='\0';
					wrLog("--->  %s", m);
					delete[] m;
					SetWindowPos(logDlg, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_ASYNCWINDOWPOS|SWP_NOACTIVATE|SWP_SHOWWINDOW);
				}
				delete[] u;
				break;
			case C_UNDO_REQUEST:
				y=rd2();
				if(y<=0 || y>moves) goto le;
				if(undoRequest){
					//both players pressed undo simultaneously
					if(undoRequest<0) undoRequest=y;
					amax(undoRequest, y);
					postUndo();
				}
				else{
					c=msg1(MB_YESNO|MB_ICONQUESTION,
						lng(876, "The other player wants to UNDO the last move.\r\nDo you agree ?"));
					if(c==IDYES){
						undoRequest=y;
						wr1(C_UNDO_YES);
						postUndo();
					}
					else{
						wr1(C_UNDO_NO);
					}
				}
				break;
			case C_NEW_REQUEST:
				if(undoRequest){
					if(undoRequest<0){
						//both players pressed NewGame simultaneously
						postNewGame();
					}
					else{
						postUndo();
					}
				}
				else{
					c=msg1(MB_YESNO|MB_ICONQUESTION,
						lng(877, "The other player wants to start a NEW game.\r\nDo you agree ?"));
					if(c==IDYES){
						undoRequest=-1;
						wr1(C_NEW_YES);
						postNewGame();
					}
					else{
						wr1(C_NEW_NO);
					}
				}
				break;
			case C_UNDO_YES:
				if(undoRequest<=0) goto le;
				postUndo();
				break;
			case C_UNDO_NO:
				if(undoRequest>0){
					msglng(878, "Sorry, the other player does not allow to UNDO your move.");
					undoRequest=0;
				}
				break;
			case C_NEW_YES:
				if(undoRequest>=0) goto le;
				postNewGame();
				break;
			case C_NEW_NO:
				if(undoRequest<0){
					msglng(879, "Sorry, the other player does not allow to start a NEW game.");
					undoRequest=0;
				}
				break;
			default: //move or error
				if(x<0 || x>=width){
					show(logDlg);
					goto le;
				}
				while(finished && (getTickCount()-lastTick<5000 || saveLock)){
					Sleep(200);
				}
				if(finished) SendMessage(hWin, WM_COMMAND, 101, 0);
				y=rd1();
				if(y<0 || y>=height) goto le;
				p=Square(x, y);
				p->time=rd4();
				PostMessage(hWin, WM_COMMAND, 991, (LPARAM)p);
		}
	}
le:
	EnterCriticalSection(&netLock);
	netGameDone();
	LeaveCriticalSection(&netLock);
	return 0;
}