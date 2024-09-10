int DriveBox_Fill(HWND hwnd)
{

  LPSHELLFOLDER lpsfDesktop;
  LPSHELLFOLDER lpsf; // Workspace == CSIDL_DRIVES

  LPITEMIDLIST  pidl;
  LPITEMIDLIST  pidlEntry;

  LPENUMIDLIST  lpe;

  COMBOBOXEXITEM  cbei;
  LPDC_ITEMDATA   lpdcid;

  ULONG dwAttributes = 0;

  DWORD grfFlags = SHCONTF_FOLDERS;


  // Init ComboBox
  SendMessage(hwnd,WM_SETREDRAW,0,0);
  SendMessage(hwnd,CB_RESETCONTENT,0,0);

  ZeroMemory(&cbei,sizeof(COMBOBOXEXITEM));
  cbei.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_LPARAM;
  cbei.pszText = LPSTR_TEXTCALLBACK;
  cbei.cchTextMax = MAX_PATH;
  cbei.iImage = I_IMAGECALLBACK;
  cbei.iSelectedImage = I_IMAGECALLBACK;


  // Get pidl to [My Computer]
  if (NOERROR == SHGetSpecialFolderLocation(hwnd,
                                            CSIDL_DRIVES,
                                            &pidl))
  {

    // Get Desktop Folder
    if (NOERROR == SHGetDesktopFolder(&lpsfDesktop))
    {

      // Bind pidl to IShellFolder
      if (NOERROR == lpsfDesktop->lpVtbl->BindToObject(
                                            lpsfDesktop,
                                            pidl,
                                            NULL,
                                            &IID_IShellFolder,
                                            &lpsf))

      {

        // Create an Enumeration object for lpsf
        if (NOERROR == lpsf->lpVtbl->EnumObjects(
                                        lpsf,
                                        hwnd,
                                        grfFlags,
                                        &lpe))

        {

          // Enumerate the contents of [My Computer]
          while (NOERROR == lpe->lpVtbl->Next(
                                            lpe,
                                            1,
                                            &pidlEntry,
                                            NULL))

          {

            // Add item to the List if it is part of the
            // Filesystem
            dwAttributes = SFGAO_FILESYSTEM;

            lpsf->lpVtbl->GetAttributesOf(
                            lpsf,
                            1,
                            &pidlEntry,
                            &dwAttributes);

            if (dwAttributes & SFGAO_FILESYSTEM)
            {

              // Windows XP: check if pidlEntry is a drive
              SHDESCRIPTIONID di;
              HRESULT hr;
              hr = SHGetDataFromIDList(lpsf,pidlEntry,SHGDFIL_DESCRIPTIONID,
                                        &di,sizeof(SHDESCRIPTIONID));
              if (hr != NOERROR || (di.dwDescriptionId >= SHDID_COMPUTER_DRIVE35 &&
                                    di.dwDescriptionId <= SHDID_COMPUTER_OTHER))
              {

                lpdcid = CoTaskMemAlloc(sizeof(DC_ITEMDATA));

                //lpdcid->pidl = IL_Copy(pidlEntry);
                lpdcid->pidl = pidlEntry;
                lpdcid->lpsf = lpsf;

                lpsf->lpVtbl->AddRef(lpsf);

                // Insert sorted ...
                {
                  COMBOBOXEXITEM cbei2;
                  LPDC_ITEMDATA lpdcid2;
                  HRESULT hr;
                  cbei2.mask = CBEIF_LPARAM;
                  cbei2.iItem = 0;

                  while ((SendMessage(hwnd,CBEM_GETITEM,0,(LPARAM)&cbei2)))
                  {
                    lpdcid2 = (LPDC_ITEMDATA)cbei2.lParam;
                    hr = (lpdcid->lpsf->lpVtbl->CompareIDs(
                                lpdcid->lpsf,
                                0,
                                lpdcid->pidl,
                                lpdcid2->pidl));

                    if ((short)(SCODE_CODE(GetScode(hr))) < 0)
                      break;
                    else
                      cbei2.iItem++;
                  }

                  cbei.iItem = cbei2.iItem;
                  cbei.lParam = (LPARAM)lpdcid;
                  SendMessage(hwnd,CBEM_INSERTITEM,0,(LPARAM)&cbei);

                }

              }

            }

          } // IEnumIDList::Next()

          lpe->lpVtbl->Release(lpe);

        } // IShellFolder::EnumObjects()

        lpsf->lpVtbl->Release(lpsf);

      } // IShellFolder::BindToObject()

      CoTaskMemFree(pidl);

    } // SHGetSpecialFolderLocation()

    lpsfDesktop->lpVtbl->Release(lpsfDesktop);

  } // SHGetDesktopFolder()


  SendMessage(hwnd,WM_SETREDRAW,1,0);
  // Return number of items added to combo box
  return ((int)SendMessage(hwnd,CB_GETCOUNT,0,0));

}