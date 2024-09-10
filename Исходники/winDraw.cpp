LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_LINE:
			d_flag=1;
			break;
		case ID_DRAW_REC:
			d_flag=2;
			break;
		case ID_DRAW_Ellipse:
			d_flag=3;
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN :		
		{
			xPaintpos[0]=GET_X_LPARAM(lParam);      
			yPaintpos[0]=GET_Y_LPARAM(lParam);	

		}
		break;

	case WM_LBUTTONUP :
		{
			xPaintpos[1]=GET_X_LPARAM(lParam);      
			yPaintpos[1]=GET_Y_LPARAM(lParam);
			GetClientRect(hWnd,&rect);

			InvalidateRect(hWnd,&rect,TRUE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		switch(d_flag)
		{
		case 1:
		MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
		LineTo(hdc,xPaintpos[1],yPaintpos[1]);
			
		break;
	   case 2:
		Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		
		break;
		case 3:
		Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		
		break;
		default:
			//Rectangle(hdc,40,40,100,100) ;
			break;
		}
		/*if (d_flag==1)
		{
		MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
		LineTo(hdc,xPaintpos[1],yPaintpos[1]);
		}
		else if (d_flag==2)
		{
		Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		}
		else if (d_flag==3)
		{
		Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		}*/
			//MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
			//LineTo(hdc,xPaintpos[1],yPaintpos[1]);
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//case 2:
		//	//Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//case 3:
		//	//Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//default:
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//}
		
		EndPaint(hWnd, &ps);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}