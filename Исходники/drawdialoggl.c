/* Also sets radius variable used to draw points.
 */
static void
handleInit(HWND hDlg)
{
   RECT winSize;
	 	RECT drawSize;
		 int orig_x,orig_y,ext_x,ext_y;
	 	//char mess [240]; /*used for debugging message text*/
   //hdc = GetDC(hDlg);


   jointlist = make_dl();
   pointlist = make_dl();


			GetWindowRect(hDlg, &winSize);
			GetWindowRect(GetDlgItem(hDlg,IDC_DRAWSPACE), &drawSize);
			hdc = GetDC(GetDlgItem(hDlg,IDC_DRAWSPACE)); /*get device context of the draw area*/

			SetClassLong(GetDlgItem(hDlg,IDC_DRAWSPACE), GCL_HCURSOR, (long)LoadCursor(NULL,"IDC_CROSS "));

			hCurrentPen = drawPen[1];  // black
			
			SetMapMode(hdc, MM_ISOTROPIC);
						
  /*
			sprintf(mess, "Dialog top is %d bottom is %d\nDraw top is %d bottom is %d.\n\nClick to continue.", 
									winSize.top,winSize.bottom,drawSize.top,drawSize.bottom);
			MessageBox( hDlg, mess, "Geometry: Window Size", MB_ICONINFORMATION );
		 */
	
			orig_x= drawSize.left-winSize.left;
			orig_y= drawSize.top-winSize.top;
			ext_x=drawSize.right-drawSize.left;
			ext_y=drawSize.bottom-drawSize.top;

			
			SetWindowOrgEx(hdc,orig_x,orig_y, NULL);
			SetWindowExtEx(hdc,ext_x,ext_y,NULL);

			// want square area to draw in

			maxSize = ext_x-orig_x; /*> ury-lly ? urx : ury;*/
			if (ury-lly>maxSize) 
      maxSize=ext_y-orig_y; 


			SetViewportOrgEx(hdc,orig_x,ext_y-orig_y-1, NULL); /*device units*/
			SetViewportExtEx(hdc, maxSize, -maxSize, NULL); /*device units*/
  /*
			sprintf(mess, "Viewport origin x is %d y is %d\nExtent x is %d y is %d.\n\nClick to continue.", 
									orig_x,ext_y-orig_y-1,maxSize,-maxSize);
			MessageBox( hDlg, mess, "Geometry: Window Size", MB_ICONINFORMATION );
			*/
//			EnableOpenGL (hDlg, &hdc, &hRC1);
//			hRC1 = wglCreateContext( hdc );
//			wglMakeCurrent( hdc, hRC1 );
//			glViewport (drawSize.left,drawSize.top,urx,ury);
//			glViewport (0,0,urx, ury);
//			glMatrixMode (GL_PROJECTION);
//			glLoadIdentity();
//			gluOrtho2D(0.0,1.0,1.0,0.0);
//			glutMouseFunc(Mouse);
			
			   
			radius = (int) ((urx-llx)/20);
			SetDlgItemInt(hDlg,IDC_MINX,llx,TRUE);
			SetDlgItemInt(hDlg,IDC_MINY,lly,TRUE);
			SetDlgItemInt(hDlg,IDC_MAXX,urx,TRUE);
			SetDlgItemInt(hDlg,IDC_MAXY,ury,TRUE);
			SetDlgItemInt(hDlg,IDC_GRID,gridSp,TRUE);
			ScaleX=Scale(urx,llx);
			ScaleY=Scale(ury,lly);
			CheckRadioButton(hDlg, DD_J1, DD_HP, DD_J1);
			CheckRadioButton(hDlg, DD_GRON, DD_GROFF, DD_GROFF);
 
			if(jp) 
				free(jp);
			if(pp) 
				free(pp);

			jp = (Joint *) malloc(sizeof(Joint) * estNumJts);
			pp = (DPoint *) malloc(sizeof(DPoint) * estNumPts);

			nLines=0; nPoints=0; nfp=0; nmp=0; nlp=0; nhp=0;
			tool=0; type=1; inside = TRUE;

//   if (grid == TRUE)
//      SendMessage(hDlg, WM_COMMAND, DD_GRON, 0L);

			//ReleaseDC(hDlg, hdc);

}  /* close handleInit() */