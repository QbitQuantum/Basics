static void  MyWnd_COMMAND(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	int comboint;
	HDC testhdc;
//	if (!zoomviewflag)
//		return;
	switch (id)
	{
	case SC_UPDATE:
//		ShowOpenGLParams(hDlg);
		InvalidateRect(hDlgOpenGL, NULL, TRUE);
		break;

	case IDC_OPENGL_ZOOM_IN:
		capowgl->ZoomIn();
		break;
	case IDC_OPENGL_ZOOM_OUT:
		capowgl->ZoomOut();
		break;

	case IDC_OPENGL_GRAPHTYPES:
		comboint = SendMessage((HWND)hwndCtl, CB_GETCURSEL, 0, 0L); 
		capowgl->Type(comboint);
		UpdateWindow(hDlg);
		break;

	case IDC_OPENGL_SURFACE:
		comboint = SendMessage((HWND)hwndCtl, CB_GETCURSEL, 0 , 0L);
		capowgl->SurfaceType(comboint);
		UpdateWindow(hDlg);
		break;
	case IDC_OPENGL_MATERIAL:
		comboint = SendMessage((HWND)hwndCtl, CB_GETCURSEL, 0, 0L); 
		capowgl->Material(comboint);
		UpdateWindow(hDlg);
		break;

	case IDC_OPENGL_RESOLUTION:
		comboint = SendMessage((HWND)hwndCtl, CB_GETCURSEL, 0, 0L);
		capowgl->Resolution(comboint);
		UpdateWindow(hDlg);
		break;

	case IDC_OPENGL_PAN_UP:
		capowgl->Pan(0);
		break;
	case IDC_OPENGL_PAN_DOWN:
		capowgl->Pan(1);
		break;
	case IDC_OPENGL_PAN_LEFT:
		capowgl->Pan(2);
		break;
	case IDC_OPENGL_PAN_RIGHT:
		capowgl->Pan(3);
		break;
	case IDC_OPENGL_MOUSE_CA:
	case IDC_OPENGL_ORIENT:
		capowgl->MouseMode(0);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_LIGHT:
		capowgl->MouseMode(1);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_PAN:
	case IDC_OPENGL_PAN:
		capowgl->MouseMode(2);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_POINT:
		capowgl->MouseMode(3);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_ZOOM:
	case IDC_OPENGL_ZOOM:
		capowgl->MouseMode(4);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_HEIGHT:
	case IDC_OPENGL_HEIGHT:
		capowgl->MouseMode(5);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MOUSE_FLY:
	case IDC_OPENGL_FLY:
		capowgl->MouseMode(6);
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_RESET:
		capowgl->Reset();
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_FLAT:
		break;
	case IDC_OPENGL_FLIP_TYPE:  //to let clicking on the bitmap be a switch
		/* Was like this.  the three types are FLATCOLOR, SHEET, TORUS defined as 0, 1, 2.
		I changed this code so Flip works on FLATCOLOR. */
		/*===============
		if (oldtype == 0)  //flat
		{
			oldtype  = capowgl->Type();
			capowgl->Type(0);
		}
		else
		{
			capowgl->Type(oldtype);
			oldtype = 0;
		}
		==================*/
			//New RR 2007 code below.
		if (capowgl->Type() == FLATCOLOR)  //flat
			capowgl->Type(SHEET);
		else // capowgl->Type() is SHEET or TORUS
			capowgl->Type(FLATCOLOR);
		// End New RR 2007 code.
		InvalidateRect(hDlg,NULL,FALSE);
		break;
	case IDC_OPENGL_SHOW_GENERATORS:
		capowgl->ShowGenerators(!capowgl->ShowGenerators());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_ZERO_PLANE:
		capowgl->ZeroPlane(!capowgl->ZeroPlane());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_MAX_PLANE:
		capowgl->MaxPlane(!capowgl->MaxPlane());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_SPIN:
		capowgl->Spin(!capowgl->Spin());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_FLY_SHOW:
		capowgl->ShowFlyPos(!capowgl->ShowFlyPos());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_GLASSES:
		capowgl->ThreeDGlasses(!capowgl->ThreeDGlasses());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_ANTIALIASED:
		capowgl->AntiAliased(!capowgl->AntiAliased());
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_PAUSE:
		SendMessage(masterhwnd, WM_COMMAND, IDM_PAUSE, 0);
		/*this has the effect of calling
			calife_list->ToggleSleep();
			capowgl->FocusIsActive(calife_list->GetSleep());
		*/
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_GLSLEEP: //Rudy added this 12/2/97
		calife_list->ToggleGlSleep();
/*
		if (calife_list->GetGlSleep()) //gl_sleep on
			calife_list->SetGlSleep(0); //turn it off
		else //gl_sleep off
			calife_list->SetGlSleep(1); //TRY to turn it on (you can't if sleep is off)
*/
		ShowOpenGLParams(hDlg);
		break;
	case IDC_OPENGL_TO_VRML:
//		capowgl->CaptureToVRML();  //this one doesn't work
		capowgl->CaptureVRML();
		break;
//		case IDOK:
//		case IDCANCEL:
//		case IDIGNORE:
		EndDialog(hDlg, 0);
	}
}