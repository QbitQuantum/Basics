/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {

HWND hw_mainfreq, hw_powfreq, hw_attconst, hw_powampl, hw_startspd, hw_startpos;
char G[20], A[20], W1[20], W2[20], V0[20], X0[20];

HDC hDC;
PAINTSTRUCT ps; //создаём контекст устройства


HPEN Pen1 = CreatePen( PS_SOLID, 1, RGB(0, 0, 255));
HPEN Pen2 = CreatePen( PS_SOLID, 2, RGB(0, 0, 0));
HPEN Pen3 = CreatePen( PS_SOLID, 2, RGB(255, 255, 255));
HPEN Pen4 = CreatePen( PS_SOLID, 1, RGB(0, 255, 0));
HPEN Pen5 = CreatePen( PS_SOLID, 1, RGB(255, 0, 0));
HBRUSH Brush1 = CreateSolidBrush( RGB(255, 255, 255) );


 switch (msg) {
  case WM_CREATE:
   /* при создании окна внедряем в него кнопочку */
   CreateWindow("button","START",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    520,420,200,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);
   /* стиль WS_CHILD означает, что это дочернее окно и для него
    вместо дескриптора меню будет передан целочисленный идентификатор,
    который будет использоваться дочерним окном для оповещения
    родительского окна через WM_COMMAND */

   hw_mainfreq = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,340,160,20,hw,(HMENU)ID_MAINFREQ,NULL,NULL);
   hw_attconst = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,360,160,20,hw,(HMENU)ID_ATTCONST,NULL,NULL);
   hw_powampl = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,380,160,20,hw,(HMENU)ID_PWAMPLIT,NULL,NULL);
   hw_powfreq = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,400,160,20,hw,(HMENU)ID_PWFREQUE,NULL,NULL);
   hw_startpos = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,320,160,20,hw,(HMENU)ID_STARTPOS,NULL,NULL);
   hw_startspd = CreateWindow("EDIT","0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        560,300,160,20,hw,(HMENU)ID_STARTSPD,NULL,NULL);

   CreateWindow("STATIC", "X'' + GX'+W1^2X = Acos(W2t)", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 280, 200, 20, hw, (HMENU)ID_EQUASION, NULL, NULL);
   CreateWindow("STATIC", "W1 = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 340, 40, 20, hw, (HMENU)ID_FIRSTNAM, NULL, NULL);
   CreateWindow("STATIC", "G = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 360, 40, 20, hw, (HMENU)ID_SECONDNM, NULL, NULL);
   CreateWindow("STATIC", "A = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 380, 40, 20, hw, (HMENU)ID_THIRDNAM, NULL, NULL);
   CreateWindow("STATIC", "W2 = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 400, 40, 20, hw, (HMENU)ID_FOURTHNM, NULL, NULL);
   CreateWindow("STATIC", "X0 = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 320, 40, 20, hw, (HMENU)ID_FITHNAME, NULL, NULL);
   CreateWindow("STATIC", "V0 = ", WS_BORDER|WS_VISIBLE|WS_CHILD, 520, 300, 40, 20, hw, (HMENU)ID_SIXTHNAM, NULL, NULL);
   CreateWindow("STATIC", "Эйлер\nh=0,1", WS_BORDER|WS_VISIBLE|WS_CHILD, 370, 300, 60, 40, hw, (HMENU)ID_LINEINF1, NULL, NULL );
   CreateWindow("STATIC", "Эйлер\nh=0,0001", WS_BORDER|WS_VISIBLE|WS_CHILD, 370, 340, 60, 40, hw, (HMENU)ID_LINEINF2, NULL, NULL );
   CreateWindow("STATIC", "Рунге\nКутт\nh=0,1", WS_BORDER|WS_VISIBLE|WS_CHILD, 370, 380, 60, 60, hw, (HMENU)ID_LINEINF3, NULL, NULL );
   CreateWindow("STATIC", "V(T)", WS_BORDER|WS_VISIBLE|WS_CHILD, 0, 0, 30, 20, hw, (HMENU)ID_GRAFINF1, NULL, NULL );
   CreateWindow("STATIC", "X(T)", WS_BORDER|WS_VISIBLE|WS_CHILD, 0, 240, 30, 20, hw, (HMENU)ID_GRAFINF2, NULL, NULL );
   CreateWindow("STATIC", "V(X)", WS_BORDER|WS_VISIBLE|WS_CHILD, 370, 0, 30, 20, hw, (HMENU)ID_GRAFINF3, NULL, NULL );

break;

        case WM_PAINT:
hDC = BeginPaint(hw, &ps);

SelectObject( hDC, Pen3);
SelectObject( hDC, Brush1);

Rectangle( hDC, 0, 0, 739, 479);

SelectObject( hDC, Pen2);

MoveToEx( hDC, 0, 240,NULL );
LineTo( hDC, 739, 240 );
MoveToEx( hDC, 370, 0,NULL );
LineTo( hDC, 370, 489 );

MoveToEx( hDC, 0, 120, NULL ); //30, 120 середина
LineTo( hDC, 739, 120 );
MoveToEx( hDC, 30, 0, NULL );
LineTo( hDC, 30, 489 );

MoveToEx( hDC, 555, 0, NULL ); //555, 120 середина
LineTo( hDC, 555, 240 );

MoveToEx( hDC, 0, 360, NULL); //30, 360 cередина
LineTo( hDC, 370, 360);

SelectObject(hDC, Pen4);

MoveToEx( hDC, 435, 320, NULL);
LineTo( hDC, 475, 320 );

SelectObject(hDC, Pen5);

MoveToEx( hDC, 435, 410, NULL);
LineTo( hDC, 475, 410 );

SelectObject(hDC, Pen1);

MoveToEx( hDC, 435, 360, NULL);
LineTo( hDC, 475, 360 );

//v = 1;

if((x0 != 0) || (v0 != 0)){
        x = x0;
        v = v0;

for(t = -6.0; t <= 11; t = t + 0.0001 ){
    v = v + 0.0001*(a*cos(w2*t)-g*v-w1*w1*x) ;
	x = x+0.0001*v;
	vn = v + 0.0001*(a*cos(w2*t)-g*v-w1*w1*x);
    xn = x+0.0001*v;

if(((20*t+150)<370) && ((-20*x+360)>240) && ((20*(t+0.0001)+150)<370) && ((-20*xn+360)>240)){
	MoveToEx( hDC, 20*t+150, -20*x+360, NULL );
	LineTo( hDC, 20*(t+0.0001)+150, -20*xn+360 );
	}

if(((20*t+150)<370) && ((-20*v+120)<240) && ((20*(t+0.0001)+150)<370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*t+150, -20*v+120, NULL );
	LineTo( hDC, 20*(t+0.0001)+150, -20*vn+120);
}

if(((20*x+555)>370) && ((-20*v+120)<240) && ((20*xn+555)>370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*x+555, -20*v+120, NULL );
	LineTo( hDC, 20*xn+555, -20*vn+120);
	}
}

v = v0;
x = x0;
SelectObject(hDC, Pen4);

for(t = -6.0; t <= 11; t = t + 0.1 ){

    v = v + 0.1*(a*cos(w2*t)-g*v-w1*w1*x) ;
	x = x+0.1*v;

	vn = v + 0.1*(a*cos(w2*t)-g*v-w1*w1*x);
    xn = x+0.1*v;

if(((20*t+150)<370) && ((-20*x+360)>240) && ((20*(t+0.1)+150)<370) && ((-20*xn+360)>240)){
	MoveToEx( hDC, 20*t+150, -20*x+360, NULL );
	LineTo( hDC, 20*(t+0.1)+150, -20*xn+360 );
	}

if(((20*t+150)<370) && ((-20*v+120)<240) && ((20*(t+0.1)+150)<370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*t+150, -20*v+120, NULL );
	LineTo( hDC, 20*(t+0.1)+150, -20*vn+120);
}

if(((20*x+555)>370) && ((-20*v+120)<240) && ((20*xn+555)>370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*x+555, -20*v+120, NULL );
	LineTo( hDC, 20*xn+555, -20*vn+120);
	}
}

v = v0;
x = x0;

SelectObject(hDC, Pen5);

for(t = -6.0; t <= 11; t = t + 0.1 ){
    k1=-(g*v +w1*w1*x)+a*cos(w2*t);
	k2=-(g*(v+k1/2)+w1*w1*x) + a*cos(w2*(t+0.05));
	k3=-(g*(v+k2/2)+w1*w1*x) + a*cos(w2*(t+0.05));
	k4=-(g*(v+k3)+w1*w1*x) + a*cos(w2*(t+0.1));

	v=v+(k1+2*k2+2*k3+k4)/60;
	x=x+0.1*v;

	k1n=-(g*v +w1*w1*x)+a*cos(w2*t);
	k2n=-(g*(v+k1/2)+w1*w1*x) + a*cos(w2*(t+0.05));
	k3n=-(g*(v+k2/2)+w1*w1*x) + a*cos(w2*(t+0.05));
	k4n=-(g*(v+k3)+w1*w1*x) + a*cos(w2*(t+0.1));

	vn=v+(k1n+2*k2n+2*k3n+k4n)/60;
	xn=x+0.1*v;

if(((20*t+150)<370) && ((-20*x+360)>240) && ((20*(t+0.1)+150)<370) && ((-20*xn+360)>240)){
	MoveToEx( hDC, 20*t+150, -20*x+360, NULL );
	LineTo( hDC, 20*(t+0.1)+150, -20*xn+360 );
	}

if(((20*t+150)<370) && ((-20*v+120)<240) && ((20*(t+0.1)+150)<370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*t+150, -20*v+120, NULL );
	LineTo( hDC, 20*(t+0.1)+150, -20*vn+120);
}

if(((20*x+555)>370) && ((-20*v+120)<240) && ((20*xn+555)>370) && ((-20*vn+120)<240)){
	MoveToEx( hDC, 20*x+555, -20*v+120, NULL );
	LineTo( hDC, 20*xn+555, -20*vn+120);
	}
}

}

EndPaint(hw, &ps);
return 0;
break;

  case WM_COMMAND:
   /* нажата наша кнопочка? */
   if ((HIWORD(wp)==0) && (LOWORD(wp)==ID_MYBUTTON)){
   // MessageBox(hw,"You pressed my button","MessageBox",MB_OK|MB_ICONWARNING);

      GetDlgItemText(hw, ID_STARTSPD, LPSTR(V0), 80 );
      GetDlgItemText(hw, ID_STARTPOS, LPSTR(X0), 80 );
      GetDlgItemText(hw, ID_MAINFREQ, LPSTR(W1), 80 );
      GetDlgItemText(hw, ID_ATTCONST, LPSTR(G), 80 );
      GetDlgItemText(hw, ID_PWFREQUE, LPSTR(W2), 80 );
      GetDlgItemText(hw, ID_PWAMPLIT, LPSTR(A), 80 );

      if(V0[0] == 0){
         MessageBox(hw,"Input start speed","ERROR",MB_OK|MB_ICONERROR);
      }
      if(X0[0] == 0){
         MessageBox(hw,"Input start position","ERROR",MB_OK|MB_ICONERROR);
      }
      if(W1[0] == 0){
         MessageBox(hw,"Input main frequency","ERROR",MB_OK|MB_ICONERROR);
      }
      if(G[0] == 0){
         MessageBox(hw,"Input attenuation constant","ERROR",MB_OK|MB_ICONERROR);
      }
      if(W2[0] == 0){
         MessageBox(hw,"Input driving force's frequency","ERROR",MB_OK|MB_ICONERROR);
      }
      if(A[0] == 0){
         MessageBox(hw,"Input driving force's amplitude","ERROR",MB_OK|MB_ICONERROR);
      }

      v0 = atof(V0);
      x0 = atof(X0);
      w1 = atof(W1);
      g = atof(G);
      w2 = atof(W2);
      a = atof(A);

      v = v0;
      x = x0;

        InvalidateRect(hw, NULL, FALSE);
    //  UpdateWindow(hw);
    //MoveWindow(hw, 0, 0, 740, 480, true);
   }
return 0;
  case WM_DESTROY:
   /* пользователь закрыл окно, программа может завершаться */
   PostQuitMessage(0);
   return 0;
 }
 return DefWindowProc(hw,msg,wp,lp);
}