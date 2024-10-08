int spline_win_message(SCREEN *sc,HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	extern SPLINE_EDIT spline_edit;
	typedef enum CMDMENU{
		CMD_ADDKEY,CMD_DELKEY
	};
	static int clickx=0,clicky=0,debounce=0;
	static PARAM_CONTROL *pcdrag=0;
	static HMENU hmenu=0;
	static SPLINE_KEY_CONTROL *selected_key=0;
	PARAM_CONTROL *p;

	p=spline_edit.plist.list;
	if(FALSE)
	if(msg!=WM_PAINT&&msg!=WM_SETCURSOR&&msg!=WM_NCHITTEST&&msg!=WM_ENTERIDLE)
	{
		static DWORD tick;
		if((GetTickCount()-tick)>500)
			printf("--\n");
		printf("spl");
		print_msg(msg,lparam,wparam,hwnd);
		tick=GetTickCount();
	}
	switch(msg){
	case WM_CREATE:
		{
			hmenu=CreatePopupMenu();
			if(hmenu){
				InsertMenu(hmenu,0xFFFFFFFF,MF_BYPOSITION,CMD_ADDKEY,"add key");
				InsertMenu(hmenu,0xFFFFFFFF,MF_BYPOSITION,CMD_DELKEY,"delete key");
			}
		}
		break;
	case WM_CONTEXTMENU:
		if(hmenu){
			POINT point;
			int x,y;
			point.x=x=LOWORD(lparam);
			point.y=y=HIWORD(lparam);
			MapWindowPoints(NULL,hwnd,&point,1);
			clickx=x;
			clicky=y;
			point.x+=spline_edit.plist.si.hscroll;
			point.y+=spline_edit.plist.si.vscroll;
			if(hittest_param(p,point.x,point.y,0)){
				TrackPopupMenu(hmenu,TPM_LEFTALIGN,x,y,0,hwnd,NULL);
			}
		}
		break;
	case WM_KEYFIRST:
		switch(wparam){
		case VK_DELETE:
			PostMessage(hwnd,WM_COMMAND,CMD_DELKEY,0);
			break;
		}
		break;
	case WM_COMMAND:
		{
			PARAM_CONTROL *pc=0;
			if(p){
				find_param_type(&spline_edit.plist,CSPLINE,&pc);
				if(pc){
					
				}
			}
			switch(LOWORD(wparam)){
			case CMD_ADDKEY:
				{
					SPLINE_KEY *sk=0;
					POINT p;
					p.x=clickx;
					p.y=clicky;
					MapWindowPoints(NULL,hwnd,&p,1);
					p.x+=spline_edit.plist.si.hscroll;
					p.y+=spline_edit.plist.si.vscroll;

					add_splinekey(pc,&sk,p.x,p.y);
				}
				break;
			case CMD_DELKEY:
				del_sel_keys(pc);
				break;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT point;
			PARAM_CONTROL *pc=0;
			point.x=LOWORD(lparam);
			point.y=HIWORD(lparam);
			MapWindowPoints(NULL,hwnd,&point,1);
			point.x+=spline_edit.plist.si.hscroll;
			point.y+=spline_edit.plist.si.vscroll;
			if(hittest_param(p,point.x,point.y,&pc)
				&& pc->control.type==CDROPLIST){
					signed short deltay=(HIWORD(wparam));
					send_mouse_wheel(pc,deltay);
					update_spline_selection(&spline_edit.plist);
			}
			else{
				short w=HIWORD(wparam);
				int key=LOWORD(wparam);
				int amount=DEFBUTTONH;
				int control=0;
				if(key&MK_SHIFT)
					amount<<=2;
				if(key&MK_CONTROL)
					control=1;
				if(w>0)
					amount=-amount;
				scroll_view(hwnd,sc,&spline_edit.plist.si,amount,control);
			}
		}
		break;
	case WM_MOUSEMOVE:
		set_focus(hwnd);
		if(pcdrag){
			int x,y,deltax,deltay;
			int lmb,mmb,rmb,ctrl,shift;
			lmb=wparam&MK_LBUTTON;
			mmb=wparam&MK_MBUTTON;
			rmb=wparam&MK_RBUTTON;
			shift=wparam&MK_SHIFT;
			ctrl=wparam&MK_CONTROL;
			x=LOWORD(lparam);
			y=HIWORD(lparam);
			deltax=x-clickx;
			deltay=y-clicky;
			if(debounce==0){
				int size=4;
				if((deltax<-size) || (deltax>size))
					debounce=1;
				if((deltay<-size) || (deltay>size))
					debounce=1;
				if(debounce==0)
					break;
				else{
					if(deltax<0)
						deltax+=size;
					else
						deltax-=size;
					if(deltay<0)
						deltay+=size;
					else
						deltay-=size;
				}
			}
			send_mouse_move(pcdrag,deltax,deltay,lmb,mmb,rmb,shift,ctrl);
			if(selected_key && pcdrag->control.type==CSPLINE)
				handle_spline_key_move(pcdrag->control.data,selected_key,deltax,deltay);
			clickx=x;
			clicky=y;
		}
		else{
			int x,y;
			x=LOWORD(lparam);
			y=HIWORD(lparam);
			if(!(wparam&MK_LBUTTON)){
				spline_edit.plist.si.vscroll_pressed=FALSE;
				spline_edit.plist.si.hscroll_pressed=FALSE;
			}
			if(spline_edit.plist.si.vscroll_pressed){
				float delta=y-clicky;
				RECT rect={0};
				int h,bh,range,d;
				GetWindowRect(hwnd,&rect);
				h=rect.bottom-rect.top;
				range=sc->h-h;
				bh=h-(range/3);
				if(bh<10){
					bh=10;
					if(h<10)
						bh=h;
				}
				d=h-bh;
				if(d<=0)
					d=1;
				delta=delta*range/d;
				spline_edit.plist.si.vscroll+=(int)delta;
				clicky=y;
			}
			if(spline_edit.plist.si.hscroll_pressed){
				float delta=x-clickx;
				RECT rect={0};
				int w,bw,range,d;
				GetWindowRect(hwnd,&rect);
				w=rect.right-rect.left;
				range=sc->w-w;
				bw=w-(range/3);
				if(bw<10){
					bw=10;
					if(w<10)
						bw=w;
				}
				d=w-bw;
				if(d<=0)
					d=1;
				delta=delta*range/d;
				spline_edit.plist.si.hscroll+=(int)delta;
				clickx=x;
			}
			{
				int x,y;
				PARAM_CONTROL *pc=0;
				x=LOWORD(lparam);
				y=HIWORD(lparam);
				if(hittest_param(p,x,y,&pc)){
					if(pc->control.type==CPOPUPLIST){
						handle_popup_list(&spline_edit.plist,pc,WM_MOUSEMOVE,x,y);
					}
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		if(pcdrag && pcdrag->control.type==CBUTTON){
			BUTTON *b=pcdrag->control.data;
			if(b)
				b->pressed=FALSE;
		}
		spline_edit.plist.si.hscroll_pressed=0;
		spline_edit.plist.si.vscroll_pressed=0;
		pcdrag=0;
		selected_key=0;
		break;
	case WM_LBUTTONDOWN:
		{
			int x,y;
			PARAM_CONTROL *pc=0;
			clickx=x=LOWORD(lparam);
			clicky=y=HIWORD(lparam);
			x+=spline_edit.plist.si.hscroll;
			y+=spline_edit.plist.si.vscroll;
			debounce=0;
			if(check_scroll_hit(sc,&spline_edit.plist.si,hwnd,x,y))
				break;
			clear_param_selected(p);
			if(hittest_param(p,x,y,&pc)){
				int list_handled=FALSE;
				if(pc->control.type==CDROPLIST){
					DROPLIST *dl=pc->control.data;
					handle_drop_list(&spline_edit.plist,pc);
					list_handled=TRUE;
				}
				else if(pc->control.type==CPOPUPLIST){
					handle_popup_list(&spline_edit.plist,pc,WM_LBUTTONDOWN,x,y);
					update_spline_selection(&spline_edit.plist);
					list_handled=TRUE;
				}
				else if(pc->control.type==CBUTTON){
					BUTTON *b=pc->control.data;
					if(b)
						b->pressed=TRUE;
				}
				else if(pc->control.type==CSPLINE){
					handle_spline_click(pc->control.data,x,y,&selected_key,wparam);
				}
				if(!list_handled)
					remove_popup(&spline_edit.plist);
				pc->has_focus=TRUE;
				pcdrag=pc;
			}
			else{
				pcdrag=0;
				remove_popup(&spline_edit.plist);
			}
		}
		break;

	}
	return 0;
}