NS_IMETHODIMP nsFilePicker::ShowW(PRInt16 *aReturnVal)
{
  NS_ENSURE_ARG_POINTER(aReturnVal);

  // suppress blur events
  if (mParentWidget) {
    nsIWidget *tmp = mParentWidget;
    nsWindow *parent = static_cast<nsWindow *>(tmp);
    parent->SuppressBlurEvents(PR_TRUE);
  }

  PRBool result = PR_FALSE;
  PRUnichar fileBuffer[FILE_BUFFER_SIZE+1];
  wcsncpy(fileBuffer,  mDefault.get(), FILE_BUFFER_SIZE);
  fileBuffer[FILE_BUFFER_SIZE] = '\0'; // null terminate in case copy truncated

  NS_NAMED_LITERAL_STRING(htmExt, "html");
  nsAutoString initialDir;
  if (mDisplayDirectory)
    mDisplayDirectory->GetPath(initialDir);

  // If no display directory, re-use the last one.
  if(initialDir.IsEmpty()) {
    // Allocate copy of last used dir.
    initialDir = mLastUsedUnicodeDirectory;
  }

  mUnicodeFile.Truncate();

  if (mMode == modeGetFolder) {
    PRUnichar dirBuffer[MAX_PATH+1];
    wcsncpy(dirBuffer, initialDir.get(), MAX_PATH);

    BROWSEINFOW browserInfo;
    browserInfo.hwndOwner      = (HWND)
      (mParentWidget.get() ? mParentWidget->GetNativeData(NS_NATIVE_TMP_WINDOW) : 0); 
    browserInfo.pidlRoot       = nsnull;
    browserInfo.pszDisplayName = (LPWSTR)dirBuffer;
    browserInfo.lpszTitle      = mTitle.get();
    browserInfo.ulFlags        = BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
    if (initialDir.Length())
    {
      // the dialog is modal so that |initialDir.get()| will be valid in 
      // BrowserCallbackProc. Thus, we don't need to clone it.
      browserInfo.lParam       = (LPARAM) initialDir.get();
      browserInfo.lpfn         = &BrowseCallbackProc;
    }
    else
    {
    browserInfo.lParam         = nsnull;
      browserInfo.lpfn         = nsnull;
    }
    browserInfo.iImage         = nsnull;

    LPITEMIDLIST list = ::SHBrowseForFolderW(&browserInfo);
    if (list != NULL) {
      result = ::SHGetPathFromIDListW(list, (LPWSTR)fileBuffer);
      if (result) {
          mUnicodeFile.Assign(fileBuffer);
      }
  
      // free PIDL
      CoTaskMemFree(list);
    }
  }
  else 
  {

    OPENFILENAMEW ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    nsString filterBuffer = mFilterList;
                                  
    if (!initialDir.IsEmpty()) {
      ofn.lpstrInitialDir = initialDir.get();
    }
    
    ofn.lpstrTitle   = (LPCWSTR)mTitle.get();
    ofn.lpstrFilter  = (LPCWSTR)filterBuffer.get();
    ofn.nFilterIndex = mSelectedType;
    ofn.hwndOwner    = (HWND) (mParentWidget.get() ? mParentWidget->GetNativeData(NS_NATIVE_TMP_WINDOW) : 0); 
    ofn.lpstrFile    = fileBuffer;
    ofn.nMaxFile     = FILE_BUFFER_SIZE;

    ofn.Flags = OFN_NOCHANGEDIR | OFN_SHAREAWARE |
                OFN_LONGNAMES | OFN_OVERWRITEPROMPT |
                OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

    // Handle add to recent docs settings
    nsCOMPtr<nsIPrivateBrowsingService> pbs =
      do_GetService(NS_PRIVATE_BROWSING_SERVICE_CONTRACTID);
    PRBool privacyModeEnabled = PR_FALSE;
    if (pbs) {
      pbs->GetPrivateBrowsingEnabled(&privacyModeEnabled);
    }
    if (privacyModeEnabled || !mAddToRecentDocs) {
      ofn.Flags |= OFN_DONTADDTORECENT;
    }

    if (!mDefaultExtension.IsEmpty()) {
      ofn.lpstrDefExt = mDefaultExtension.get();
    }
    else {
      // Get file extension from suggested filename
      //  to detect if we are saving an html file
      //XXX: nsIFile SHOULD HAVE A GetExtension() METHOD!
      PRInt32 extIndex = mDefault.RFind(".");
      if ( extIndex >= 0) {
        nsAutoString ext;
        mDefault.Right(ext, mDefault.Length() - extIndex);
        // Should we test for ".cgi", ".asp", ".jsp" and other
        // "generated" html pages?

        if ( ext.LowerCaseEqualsLiteral(".htm")  ||
             ext.LowerCaseEqualsLiteral(".html") ||
             ext.LowerCaseEqualsLiteral(".shtml") ) {
          // This is supposed to append ".htm" if user doesn't supply an extension
          //XXX Actually, behavior is sort of weird:
          //    often appends ".html" even if you have an extension
          //    It obeys your extension if you put quotes around name
          ofn.lpstrDefExt = htmExt.get();
        }
      }
    }

    MOZ_SEH_TRY {
      if (mMode == modeOpen) {
        // FILE MUST EXIST!
        ofn.Flags |= OFN_FILEMUSTEXIST;
        result = ::GetOpenFileNameW(&ofn);
      }
      else if (mMode == modeOpenMultiple) {
        ofn.Flags |= OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
        result = ::GetOpenFileNameW(&ofn);
      }
      else if (mMode == modeSave) {
        ofn.Flags |= OFN_NOREADONLYRETURN;

        // Don't follow shortcuts when saving a shortcut, this can be used
        // to trick users (bug 271732)
        NS_ConvertUTF16toUTF8 ext(mDefault);
        ext.Trim(" .", PR_FALSE, PR_TRUE); // watch out for trailing space and dots
        ToLowerCase(ext);
        if (StringEndsWith(ext, NS_LITERAL_CSTRING(".lnk")) ||
            StringEndsWith(ext, NS_LITERAL_CSTRING(".pif")) ||
            StringEndsWith(ext, NS_LITERAL_CSTRING(".url")))
          ofn.Flags |= OFN_NODEREFERENCELINKS;

        result = ::GetSaveFileNameW(&ofn);
        if (!result) {
          // Error, find out what kind.
          if (::GetLastError() == ERROR_INVALID_PARAMETER 
              || ::CommDlgExtendedError() == FNERR_INVALIDFILENAME
              ) {
            // probably the default file name is too long or contains illegal characters!
            // Try again, without a starting file name.
            ofn.lpstrFile[0] = 0;
            result = ::GetSaveFileNameW(&ofn);
          }
        }
      } 
      else {
        NS_ERROR("unsupported mode"); 
      }
    }
    MOZ_SEH_EXCEPT(PR_TRUE) {
      MessageBoxW(ofn.hwndOwner,
                  0,
                  L"The filepicker was unexpectedly closed by Windows.",
                  MB_ICONERROR);
      result = PR_FALSE;
    }

    if (result) {
      // Remember what filter type the user selected
      mSelectedType = (PRInt16)ofn.nFilterIndex;

      // Set user-selected location of file or directory
      if (mMode == modeOpenMultiple) {
        
        // from msdn.microsoft.com, "Open and Save As Dialog Boxes" section:
        // If you specify OFN_EXPLORER,
        // The directory and file name strings are NULL separated, 
        // with an extra NULL character after the last file name. 
        // This format enables the Explorer-style dialog boxes
        // to return long file names that include spaces. 
        PRUnichar *current = fileBuffer;
        
        nsAutoString dirName(current);
        // sometimes dirName contains a trailing slash
        // and sometimes it doesn't.
        if (current[dirName.Length() - 1] != '\\')
          dirName.Append((PRUnichar)'\\');
        
        nsresult rv;
        while (current && *current && *(current + nsCRT::strlen(current) + 1)) {
          current = current + nsCRT::strlen(current) + 1;
          
          nsCOMPtr<nsILocalFile> file = do_CreateInstance("@mozilla.org/file/local;1", &rv);
          NS_ENSURE_SUCCESS(rv,rv);
          
          rv = file->InitWithPath(dirName + nsDependentString(current));
          NS_ENSURE_SUCCESS(rv,rv);
          
          rv = mFiles.AppendObject(file);
          NS_ENSURE_SUCCESS(rv,rv);
        }
        
        // handle the case where the user selected just one
        // file.  according to msdn.microsoft.com:
        // If you specify OFN_ALLOWMULTISELECT and the user selects 
        // only one file, the lpstrFile string does not have 
        // a separator between the path and file name.
        if (current && *current && (current == fileBuffer)) {
          nsCOMPtr<nsILocalFile> file = do_CreateInstance("@mozilla.org/file/local;1", &rv);
          NS_ENSURE_SUCCESS(rv,rv);
          
          rv = file->InitWithPath(nsDependentString(current));
          NS_ENSURE_SUCCESS(rv,rv);
          
          rv = mFiles.AppendObject(file);
          NS_ENSURE_SUCCESS(rv,rv);
        }
      }
      else {
        // I think it also needs a conversion here (to unicode since appending to nsString) 
        // but doing that generates garbage file name, weird.
        mUnicodeFile.Assign(fileBuffer);
      }
    }
    if (ofn.hwndOwner) {
      ::DestroyWindow(ofn.hwndOwner);
    }
  }

  if (result) {
    PRInt16 returnOKorReplace = returnOK;

    // Remember last used directory.
    nsCOMPtr<nsILocalFile> file(do_CreateInstance("@mozilla.org/file/local;1"));
    NS_ENSURE_TRUE(file, NS_ERROR_FAILURE);

    // XXX  InitWithPath() will convert UCS2 to FS path !!!  corrupts unicode 
    file->InitWithPath(mUnicodeFile);
    nsCOMPtr<nsIFile> dir;
    if (NS_SUCCEEDED(file->GetParent(getter_AddRefs(dir)))) {
      mDisplayDirectory = do_QueryInterface(dir);
      if (mDisplayDirectory) {
        if (mLastUsedUnicodeDirectory) {
          NS_Free(mLastUsedUnicodeDirectory);
          mLastUsedUnicodeDirectory = nsnull;
        }

        nsAutoString newDir;
        mDisplayDirectory->GetPath(newDir);
        if(!newDir.IsEmpty())
          mLastUsedUnicodeDirectory = ToNewUnicode(newDir);
      }
    }

    if (mMode == modeSave) {
      // Windows does not return resultReplace,
      //   we must check if file already exists
      PRBool exists = PR_FALSE;
      file->Exists(&exists);

      if (exists)
        returnOKorReplace = returnReplace;
    }
    *aReturnVal = returnOKorReplace;
  }
  else {
    *aReturnVal = returnCancel;
  }
  if (mParentWidget) {
    nsIWidget *tmp = mParentWidget;
    nsWindow *parent = static_cast<nsWindow *>(tmp);
    parent->SuppressBlurEvents(PR_FALSE);
  }

  return NS_OK;
}