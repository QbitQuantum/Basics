//рисуем картину приложения
void LinePicture(HWND hwnd, int Context)
{
//выбираем нужный контектс устройства для экрана
//---------------------------------------------
	HDC hdcWin;
	PAINTSTRUCT ps;
	//получаем контест устройства для экрана
	if(Context == 1)
		hdcWin = BeginPaint(hwnd, &ps);
	else
		hdcWin = GetDC(hwnd);
//-----------------------------------------------


//связываем размеры поля вывода с размерами клиентской области окна
//--------------------------------------------------------------------
	RECT rct;
	GetClientRect(hwnd,&rct);

	ne1 = rct.left+50; ne2 = rct.right -50;
	me1 = rct.bottom -50; me2 = rct.top + 50;
//------------------------------------------------------------------

//создаем контекст экрана
//------------------------------------------------------------
	HDC hdc = CreateCompatibleDC(hdcWin); //создаем контекст
                     //памяти связаный с контекстом экрана

   //памяти надо придать вид экрана - подходт битовая карта с форматом
   // как у экрана. В памяти будем рисовать на битовой карте
	HBITMAP hBitmap, hBitmapOld;
	hBitmap = CreateCompatibleBitmap(hdcWin, ne2, me1); //создаем
               //битовую карту совместмую с контекстом экрана
	hBitmapOld = (HBITMAP)SelectObject(hdc, hBitmap); //помещаем
                // битовую карту в контекст памяти
//--------------------------------------------------------------
	

//выводи значения углов в верхней части поля вывода
//--------------------------------------------------------	
	//создание прямоугольной области для вывода углов поворота
	HRGN hrgn2 = CreateRectRgn(ne1,me2-30,ne2,me1);

	//заливаем выделенную область серым цветом
	HBRUSH hBrush2 = CreateSolidBrush(RGB(0x80,0x80,0x80));
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc,hBrush2); 
    FillRgn(hdc,hrgn2,hBrush2);

	SelectObject(hdc,hBrushOld);   
	DeleteObject(hBrush2);         
	DeleteObject(hrgn2);         

	
	//вычисление угловых коэффициентов поворота системы координат
	sf=sin(M_PI*angl.fi/180);
	cf=cos(M_PI*angl.fi/180);
	st=sin(M_PI*angl.teta/180);
	ct=cos(M_PI*angl.teta/180);


	//информация об углах поворота системы координат
	TCHAR ss[20];
	SetBkColor(hdc,RGB(0xC0,0xC0,0xC0));
	SetTextColor(hdc,RGB(0,0,0x80));
	swprintf_s(ss,20,L"fi = %4.0lf",angl.fi);
	TextOut(hdc,(ne1+ne2)/2-80,me2-25,ss,9);
	swprintf_s(ss,20,L"teta = %4.0lf",angl.teta);
	TextOut(hdc,(ne1+ne2)/2+20,me2-25,ss,11);
//------------------------------------------------

	
	


//выделение памяти под Z-буфер и начальное его заполнение
//-------------------------------------------------------------
	//вычисляем число пикселей в поле  вывода
	Np = ne2-ne1 + 1, Mp = me1-me2 +1, NM = Np*Mp;

	//выделяем память под Z-буфер для каждого пикселя
	zb = new ZbuffS [NM];

	//начальное заполнение z-буфера для каждого пикселя
	for ( long unsigned p=0; p<NM; p++)
	{
   		zb[p].z = -1000;
   		zb[p].c.R = 0xC0; zb[p].c.G = 0xC0; zb[p].c.B = 0xC0;
	}
//-----------------------------------------------------------

	

//"рисуем" магнитную пластинку заданным цветом заполняя Z-буфер	
//-----------------------------------------------------------------------
	//мировые координаты проецируемой точки
	double xt1,yt1,zt1;
	//видовые координаты проецируемой точки
	double xe,ye,ze1;
	//пиксельные координаты проецируемой точки
	int x1,y1;

	//пиксельные координаты 4-х углов пластинки
	int xp[4], yp[4];
	//видовые z-координаты 4-х углов пластинки
	double ze[4];

	for(int n=0; n<4; n++)
	{
		xt1 = Px[n]; yt1 = Py[n]; zt1 = Pz[n];
		xe = Xe(xt1, yt1, zt1);
		ye=Ye(xt1,yt1,zt1);
		ze1=Ze(xt1,yt1,zt1);
		x1=xn(xe);
		y1=ym(ye);
		xp[n] = x1; yp[n] = y1; ze[n] = ze1;
	}	
	//ZbufParallelogram(hdc,xp[0],yp[0],ze[0],xp[1],yp[1],ze[1],
		//xp[2],yp[2],ze[2],xp[3],yp[3],ze[3],RGB(255,255,0));
//------------------------------------------------------------------



//"рисуем" линии поля заполняя Z-буфер
//----------------------------------------------------------------
	for (int i = 0; i < 20; i++)
	{
		LineField(hdc,PointB[i],RGB(255,0,0),1);
		
	}
	
	for(int i=20; i<40; i++)
	{
		LineField(hdc,PointB[i],RGB(0,0,255), 1);
		
	}

	for (int i = 40; i<60; i++)
	{
		LineField(hdc, PointB[i], RGB(0, 255,0), 1);

	}
	
//-----------------------------------------------------------------------


//выводим содержимое Z-буфера в контекст памяти
//--------------------------------------------------------------------
	//двигаемся по всем пикселям окна вывода
	for (unsigned long ij=0; ij<NM; ij++)
	{
   		x1 = ne1 + ij%Np;
		y1 = me2 + ij/Np;
		SetPixel(hdc,x1,y1,RGB(zb[ij].c.R,zb[ij].c.G,zb[ij].c.B));

	}

	delete [] zb; //очищаем память под Z-буфером
//-------------------------------------------------------------



//рисуем координтные оси
//------------------------------------------------------------------------

	HPEN hPen = CreatePen(PS_SOLID,1,RGB(0,255,255));
	HPEN hPenOld = (HPEN)SelectObject(hdc,hPen);    
	
	int x2,y2;

//ось Ox
	xe=Xe(-xmax/3,0,0);
	ye=Ye(-xmax/3,0,0);
	x1=xn(xe);
	y1=ym(ye);
	xe=Xe(xmax,0,0);
	ye=Ye(xmax,0,0);
	x2=xn(xe);
	y2=ym(ye);
	
	MoveToEx(hdc,x1,y1,NULL);
	LineTo(hdc,x2,y2);

	SetBkColor(hdc,RGB(0xC0,0xC0,0xC0));
	SetTextColor(hdc,RGB(120,120,120));
	TextOut(hdc,x2, y2, _T("X"),1);

//Ось Oy
	xe=Xe(0,-ymax/3, 0);
	ye=Ye(0,-ymax/3,0);
	x1=xn(xe);
	y1=ym(ye);
	xe=Xe(0,ymax, 0);
	ye=Ye(0,ymax,0);
	x2=xn(xe);
	y2=ym(ye);
	
	MoveToEx(hdc,x1,y1,NULL);
	LineTo(hdc,x2,y2);

	SetBkColor(hdc,RGB(0xC0,0xC0,0xC0));
	SetTextColor(hdc,RGB(120,120,120));
	TextOut(hdc,x2, y2, _T("Y"),1);

//Ось Oz
	xe=Xe(0,0, 0);
	ye=Ye(0,0,-zmax/3);
	x1=xn(xe);
	y1=ym(ye);
	xe=Xe(0,0, 0);
	ye=Ye(0,0,zmax);
	x2=xn(xe);
	y2=ym(ye);

	MoveToEx(hdc,x1,y1,NULL);
	LineTo(hdc,x2,y2);

	SetBkColor(hdc,RGB(0xC0,0xC0,0xC0));
	SetTextColor(hdc,RGB(120,120,120));
	TextOut(hdc,x2, y2, _T("Z"),1);


	SelectObject(hdc,hPenOld); 
	DeleteObject(hPen);        
//-----------------------------------------------------------------------------


//рисуем куб
//----------------------------------------------------------------------
	hPen = CreatePen(PS_SOLID,1,RGB(160,160,160));
	hPenOld = (HPEN)SelectObject(hdc,hPen);    

	DrawBox(hwnd, hdc, angl);

	SelectObject(hdc,hPenOld); 
	DeleteObject(hPen);        
//------------------------------------------------------------------------


//копируем контекст памяти в контекст экрана
//-----------------------------------------------------------------------	
	BitBlt(hdcWin,ne1,me2-30,ne2,me1,hdc,ne1,me2-30,SRCCOPY); 
//----------------------------------------------------------------------


//завершаем работу с контекстами и памятью
//-------------------------------------------------------------------
	SelectObject(hdc, hBitmapOld); //востанавливаем контекст памяти
	DeleteObject(hBitmap); //убираем битовую карту
	DeleteDC(hdc);  //  освобождаем контекст памяти

	//освобождаем контекст экрана
	if(Context == 1)
		EndPaint(hwnd, &ps);
	else
		ReleaseDC(hwnd, hdcWin);   
}