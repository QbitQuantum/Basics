void __declspec(dllexport) onDropFiles(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra)
{  
  HWND hwCtl;
  //LONG lwnd;
  nsFunction  callback;

  // get info from stack

  hwCtl = (HWND) popint();
  callback = (nsFunction) popint();

  if (!IsWindow(hwCtl))
    return;

  //lwnd = GetWindowLong(hwCtl, GWL_EXSTYLE);
  //SetWindowLong(hwCtl, GWL_EXSTYLE, lwnd | WS_EX_ACCEPTFILES);
	DragAcceptFiles(hwCtl, TRUE);

  pushint((nsFunction) callback);
//  pushint((int) hwCtl);

	if (hwCtl == g_window.hwWindow)
		SetWindowCallback(WND_CALLBACK_IDX(onDropFiles));
	else
		{
			//size_t id;
			//id = g_window.controlCount - 1;
			//MessageBox(g_window.hwWindow,"control dropfiles",NULL,MB_OK);
			//g_window.controls[id].oldWndProc = (WNDPROC) SetWindowLong(hwCtl, GWL_WNDPROC, (long) DropFilesWndProc);
			ctl = GetControl(hwCtl);
			if (ctl == NULL)
				return;
			ctl->oldWndProc = (WNDPROC) SetWindowLong(hwCtl, GWL_WNDPROC, (long) DropFilesWndProc);

			pushint((int) hwCtl);

			SetControlCallback(CTL_CALLBACK_IDX(onDropFiles));
		}
}