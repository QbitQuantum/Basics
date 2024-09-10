long FAR PASCAL _export ProcVentApp (HWND hwnd, WORD message,
				     WORD wParam, LONG lParam)
{
 static HANDLE      hInstance;
 PAINTSTRUCT        ps;

 switch (message)
 {
  case WM_CREATE:
  {
   /* Obtenemos el handle a la ocurrencia del m�dulo, que se guarda forever */
   hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

   return (0);
  }

  case WM_PAINT:
  {
   /* Obtenemos el contexto de la ventana */
   hdc = BeginPaint (hwnd, &ps);

   /* Redibujamos el MetaFile */
   PlayMetaFile (hdc, hMF);

   /* Liberamos el contexto */
   EndPaint (hwnd, &ps);

   return (0);
  }

  case WM_DESTROY:
  {
   PostQuitMessage (0);
   return (0);
  }
 }

 return (DefFrameProc (hwnd, hwndCliente, message, wParam, lParam));
}