int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);

   /* Show main window */
   DialogBox(hInstance, MAKEINTRESOURCE(IDD_SINGLETON), NULL, Dlg_Proc);

   /* Don't forget to clean up and release kernel resources */
   if (g_hSingleton != NULL) 
   {
       CloseHandle(g_hSingleton);
   }

   if (g_hNamespace != NULL) 
   {
	   /* Open namespace */
       if (g_bNamespaceOpened) 
	   {  
		   /* Open namespace */
           ClosePrivateNamespace(g_hNamespace, 0);
       } 
	   else 
	   {  
		   /* Created namespace */
           ClosePrivateNamespace(g_hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
       }
   }

   if (g_hBoundary != NULL) 
   {
       DeleteBoundaryDescriptor(g_hBoundary);
   }

   return(0);
}