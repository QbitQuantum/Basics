void FileDialog::FilterFiles(HWND hDlg)
{
   HWND parent = ::GetParent(hDlg);
   IShellFolder *ishell = NULL;
   LPMALLOC imalloc = NULL;
   HRESULT hr;
   
   // Get pointer to the ListView control
   HWND lv = ::GetDlgItem(::GetDlgItem(parent, lst2), 1);
   if (lv == NULL)
   {
      wxASSERT(lv != NULL);
      return;
   }
   
   // Get shell's memory allocation interface (must be Release()'d)
   hr = SHGetMalloc(&imalloc);
   if ((hr != NOERROR) || (imalloc == NULL))
   {
      wxASSERT((hr == NOERROR) && (imalloc != NULL));
      return;
   }
   
   // Init
   LVITEM lvi;
   wxZeroMemory(lvi);
   
   // Process all items
   int fltcnt = m_Filters.GetCount();
   int itmcnt = ::SendMessage(lv, LVM_GETITEMCOUNT, 0, 0);
   for (int itm = 0; itm < itmcnt; itm++)
   {
      // Retrieve the file IDL
      lvi.iItem = itm;
      lvi.mask = LVIF_PARAM;
      if (ListView_GetItem(lv, &lvi) != TRUE)
      {
         wxASSERT(FALSE);
         break;
      }
      LPCITEMIDLIST fidl = (LPCITEMIDLIST) lvi.lParam;
      
      // Retrieve the IShellFolder interface of the parent (must be Release()'d)
      if (ishell == NULL)
      {
         hr = SHBindToParent(fidl, IID_IShellFolder, (void **)&ishell, NULL);
         if (!SUCCEEDED(hr))
         {
            wxASSERT(SUCCEEDED(hr));
            break;
         }
      }
      
      // Get the attributes of the object
      DWORD attr = SFGAO_FOLDER | SFGAO_STREAM;
      hr = ishell->GetAttributesOf(1, &fidl, &attr);
      if (!SUCCEEDED(hr))
      {
         wxASSERT(SUCCEEDED(hr));
         break;
      }
      
      // Allow all folders (things like zip files get filtered below)
      if (attr == SFGAO_FOLDER)
      {
         continue;
      }
      
      // Retrieve the parsable name of the object (includes extension)
      STRRET str;
      hr = ishell->GetDisplayNameOf(fidl, SHGDN_INFOLDER | SHGDN_FORPARSING, &str);
      if (hr != NOERROR)
      {
         // For some objects, we get back an error of 80070057.  I'm assuming this
         // means there is no way to represent the name (like some sort of virtual name)
         // or I've not used the correct PIDL.  But, in either case, it "probably"
         // represents some sort of folder (at least in all cases I've seen), so we
         // simply allow it to display.
         continue;
      }
      
      // Convert result to wxString
      wxString filename;
      switch (str.uType)
      {
         case STRRET_WSTR:
            filename = str.pOleStr;
            imalloc->Free(str.pOleStr);
            break;
            
         case STRRET_OFFSET:
            filename = wxString(((char *)fidl) + str.uOffset, wxConvISO8859_1);
            break;
            
         case STRRET_CSTR:
            filename = wxString(str.cStr, wxConvISO8859_1);
            break;
      }
      
      // Attempt to match it to all of our filters
      bool match = false;
      for (int flt = 0; flt < fltcnt; flt++)
      {
         if (wxMatchWild(m_Filters[flt], filename, false))
         {
            match = true;
            break;
         }
      }
      
      // Remove it from the display if it didn't match any of the filters.
      if (!match)
      {
         ListView_DeleteItem(lv, itm);
         itm--;
         itmcnt--;
      }
   }
   
done:
   
   // Release the interface
   if (ishell)
   {
      ishell->Release();
   }
   
   // Release the interface
   if (imalloc)
   {
      imalloc->Release();
   }
}