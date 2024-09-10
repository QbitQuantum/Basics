HRESULT SHPathToPIDL(LPCTSTR szPath, LPITEMIDLIST* ppidl)
{
   LPSHELLFOLDER pShellFolder = NULL;
   OLECHAR wszPath[MAX_PATH] = {0};
   ULONG nCharsParsed = 0;

   // Get an IShellFolder interface pointer
   HRESULT hr = SHGetDesktopFolder(&pShellFolder);
   if(FAILED(hr))
      return hr;

   // Convert the path name to Unicode
   MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1, wszPath, MAX_PATH);

   // Call ParseDisplayName() to do the job
   hr = pShellFolder->lpVtbl->ParseDisplayName(pShellFolder,NULL, NULL, wszPath, &nCharsParsed, ppidl, NULL);

   // Clean up
   pShellFolder->lpVtbl->Release(pShellFolder);
   return hr;
}