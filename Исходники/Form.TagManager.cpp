LRESULT CALLBACK FormTagManager::DlgProc(     
	_In_  HWND hwnd,     
	_In_  UINT uMsg,     
	_In_  WPARAM wParam,     
	_In_  LPARAM lParam     
	)     
{
	//::PrintLog(L"Message: 0x%x, wParam = 0x%x, lParam = 0x%x, hwnd = 0x%x", uMsg, wParam, lParam, hwnd);

	switch(uMsg)     
	{   
	case WM_INITDIALOG:
		{
			::PrintLog(L"Message: WM_INITDIALOG");

			// init
			this->_hwnd = hwnd;
			this->_handler = (CHandler *)lParam;

			this->_handler->AddRef();	// to keep the instance after the Form opend, will be released in WM_NCDESTROY.

			SHGetImageList(SHIL_SMALL,IID_IImageList,(void **)&_sysImgList);
			_sysImgList->AddRef();	// will be released in ~ctor.

			_hErrorInfo = GetDlgItem(_hwnd,IDC_TAGMANAGER_STATIC_ERROR_INFO);
			_hListTags = GetDlgItem(_hwnd,IDC_TAGMANAGER_LIST_TAGS);
			_hListFiles = GetDlgItem(_hwnd,IDC_TAGMANAGER_LIST_SelectedFiles);
			_hEditCtlNewTag = GetDlgItem(_hwnd,IDC_TAGMANAGER_EDIT_TagWord);
			_hCheckAttachToFiles = GetDlgItem(_hwnd, IDC_TAGMANAGER_CHECK_AttachNewTagToFiles);
			_hBuAdd = GetDlgItem(_hwnd,IDC_TAGMANAGER_BU_ADD);
			_hBuEdit = GetDlgItem(_hwnd,IDC_TAGMANAGER_BU_EDIT);
			_hBuDel = GetDlgItem(_hwnd,IDC_TAGMANAGER_BU_DEL);

			InitText();
			InitTagList();
			InitFileList();

			Button_SetCheck(_hCheckAttachToFiles,BST_CHECKED);
			Button_Enable(_hBuAdd,false);
			Edit_TakeFocus(_hEditCtlNewTag);

			break;
		}
	case MSG_TRANSFER_INSTANCES:
		::PrintLog(L"Message: MSG_TRANSFER_INSTANCES: wParam: %d, lParam: %d",wParam, lParam);
		break;
	case WM_CTLCOLORSTATIC:
		{
			// change the text color of static label ERROR_INFO
			if( (UINT)lParam == (UINT)_hErrorInfo){
				HDC hdcStatic = (HDC) wParam;
				SetTextColor(hdcStatic, _msgColor);

				// the background color will be changed to white, that is not what I want, so, restore the background color manual.
				auto oldBkColor = GetSysColor(CTLCOLOR_DLG);
				SetBkColor(hdcStatic,oldBkColor);

				if (_hbrBkgnd == NULL)
				{
					_hbrBkgnd = CreateSolidBrush(oldBkColor);
				}

				// the return value is a handle to a brush that the system uses to paint the background of the static control.
				// http://msdn.microsoft.com/en-us/library/windows/desktop/bb787524(v=vs.85).aspx
				return (INT_PTR)_hbrBkgnd;
			}
		}
	case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_KEYMENU:
				{
					::PrintLog(L"Message: SC_KEYMENU: wParam: %d, lParam: %d",wParam, lParam);
					break;
				}
			case SC_CLOSE:
				{
					DestroyWindow(hwnd);
					break;
				}
			default:
				break;
			}
		}
		break;
	case WM_COMMAND:
		{
			::PrintLog(L"Message: WM_COMMAND");
			switch(LOWORD(wParam))     
			{    
			case IDC_TAGMANAGER_BU_DEL:
				{
					DelTags();
					break;
				}
			case IDC_TAGMANAGER_BU_EDIT:
				{
					EditTag();
					break;
				}
			case IDC_TAGMANAGER_BU_ADD:
				{
					AddTag();
					break;
				}
			case IDC_TAGMANAGER_CHECK_AttachNewTagToFiles:
				::PrintLog(L"Message: IDC_CHECK_AttachNewTagToFiles");
				break;
			case IDC_TAGMANAGER_BU_CANCEL:
				DestroyWindow(hwnd);
				break;
			case IDC_TAGMANAGER_EDIT_TagWord:
				{
					OnNewTagChanged(wParam,lParam);
					break;
				}
			default:
				break;
			}
		}
		break;
		//case WM_SIZE:
		//	{
		//		auto hTreeView = GetDlgItem(hdlg, IDC_TREE1);  
		//		if(hTreeView!=NULL)
		//		{

		//		}
		//		return 0;
		//	}
	case WM_KEYDOWN:
		{
			::PrintLog(L"Message: WM_KEYDOWN");
		}
		break;
	case WM_KEYUP:
		{
			::PrintLog(L"Message: WM_KEYUP");
			if(wParam==VK_ESCAPE)
			{
				DestroyWindow(hwnd);
			}
			else if( wParam == VK_RETURN )
			{
				// simulate text changed to validate the new tag.
				OnNewTagChanged(MAKEWPARAM(IDC_TAGMANAGER_EDIT_TagWord, EN_SETFOCUS),(LPARAM)_hEditCtlNewTag);
				// simulate the button ADD to be Clicked.
				SendMessage(_hwnd,WM_COMMAND, MAKEWPARAM(IDC_TAGMANAGER_BU_ADD, BN_CLICKED),(LPARAM)_hBuAdd);
			}
		}
		break;
	case WM_CHAR:
		{
			::PrintLog(L"Message: WM_CHAR");
		}
		break;
	case WM_SYSCHAR:
		{
			::PrintLog(L"Message: WM_SYSCHAR");
		}
		break;
	case WM_DEADCHAR:
		{
			::PrintLog(L"Message: WM_DEADCHAR");
		}
		break;
	case WM_SYSDEADCHAR:
		{
			::PrintLog(L"Message: WM_SYSDEADCHAR");
		}
		break;
	case WM_NOTIFY:
		{
			LPNMHDR pNmhdr = (LPNMHDR) lParam;
			switch (pNmhdr->idFrom)
			{
			case IDC_TAGMANAGER_LIST_TAGS:
				{
					WM_NOTIFY_LIST_Tags(wParam,lParam);
					break;
				}
			case IDC_TAGMANAGER_LIST_SelectedFiles:
				{
					WM_NOTIFY_LIST_Files(wParam,lParam);
					break;
				}
			default:
				break;
			}
		}
		break;
	case WM_DESTROY:     
		{
			PostQuitMessage(0);
		}
		break;
	case WM_NCDESTROY:
		{
			::PrintLog(L"Message: WM_NCDESTROY");
			if(this->_handler != NULL){
				auto x = this->_handler->Release();
				if( x == 0 ){
					this->_handler = NULL;
				}
			}
		}
		break;
	default:
		break;
	}

	return (INT_PTR)FALSE;
}