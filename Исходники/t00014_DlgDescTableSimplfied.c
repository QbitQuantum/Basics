LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   static SQLHENV henv;
   static SQLHDBC hdbc;
   static SQLHSTMT hstmt;
   static int ifconnect=0;
   static SQLCHAR server[32];
   static char Content[10240] ;
   static RECT rect;
   static PAINTSTRUCT ps;
   static HBRUSH hbrush;	
   static HDC hDC ;
	static RedrawFlag = 0;
	LPDRAWITEMSTRUCT pdis;
	//~ char Content2[10240] ;
	SQLCHAR sqlstr[1024];	
	SQLRETURN retcode;
 
	//~ SQLHENV env;
	char dsn[256];
	char desc[256];
	SQLSMALLINT dsn_ret;
	SQLSMALLINT desc_ret;
	SQLUSMALLINT direction;
	SQLRETURN ret;
	HWND hEditTN = GetDlgItem(hwndDlg, IDC_EDIT1);
	HWND hEdit = GetDlgItem(hwndDlg, IDC_EDIT2);
	HWND hCBox = GetDlgItem(hwndDlg,IDC_COMBO1);
	HWND hBTN1 = GetDlgItem(hwndDlg,IDC_BUTTON1);
	int curSel;
	char szTable[256]; // receives name of item to delete. 
	LPDRAWITEMSTRUCT dItem;
	char text[20];
	int len;
	SIZE sz;

	GetWindowRect(hBTN1,&rect);
	
	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{
		   // Allocate environment handle
		   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
		   // Set the ODBC version environment attribute
		   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			  retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		   }
		   else {
					MessageBoxPrintf("Prompt","fail to SQLAllocHandle SQL_HANDLE_ENV\n");
					return FALSE;
			}
			
		  direction = SQL_FETCH_FIRST;
		  while(SQL_SUCCEEDED(ret = SQLDataSources(henv, direction,
							   dsn, sizeof(dsn), &dsn_ret,
							   desc, sizeof(desc), &desc_ret))) 
		  {
			direction = SQL_FETCH_NEXT;
			//MessageBoxPrintf("DSN","%s\n",dsn);
			ComboBox_InsertString(hCBox,0,dsn);								   
			if (ret == SQL_SUCCESS_WITH_INFO) printf("\tdata truncation\n");
		  }
			
			return TRUE;
		}
		break;
	case WM_COMMAND://
		{
			switch (LOWORD(wParam)) 
            { 
                // Process the accelerator and menu commands. 
 
                case ID_ACCELERATOR1: 
				//~ MessageBoxPrintf("hi","hello");
				//~ GetModuleHandle()
				SendMessage(hEdit, EM_SETSEL,(WPARAM)0,(LPARAM) sizeof(Content)/sizeof(char));
			return TRUE;
			}
			
			switch(wParam)
			{
				case IDC_BUTTON1:
				{
					//disconnect
					if (ifconnect) {
						retcode = SQLDisconnect(hdbc);	
					   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							SetWindowText(GetDlgItem(hwndDlg, IDC_BUTTON1), (LPCTSTR )"Connect");				   
							//~ MessageBoxPrintf("Prompt","Disconnected from %s!\n",server);
							ifconnect = 0;
						InvalidateRect(GetDlgItem(hwndDlg, IDC_BUTTON1),NULL, TRUE);  
						UpdateWindow(GetDlgItem(hwndDlg, IDC_BUTTON1));						   
							return 0;
					   }
					   //~ else
					   //~ {
							//~ MessageBoxPrintf("Prompt","Not Connect yet!\n");						
						//~ }
					}

					  // Allocate connection handle
						 retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
					  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							 // Set login timeout to 5 seconds					  
							SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);	
					  }
					  else{
							SQLFreeHandle(SQL_HANDLE_DBC, hdbc);  
							SQLFreeHandle(SQL_HANDLE_ENV, henv);								
							return FALSE;					  
					  }

					// Connect to data source
						if(!ComboBox_GetTextLength(hCBox)){
							MessageBoxPrintf("ERROR","Please Select an Item!");
							return FALSE;
						}
						curSel=ComboBox_GetCurSel(hCBox);
						ComboBox_GetLBText(hCBox,curSel,server);
						retcode = SQLConnect(
						hdbc
						, (SQLCHAR*) server
						, SQL_NTS
						, (SQLCHAR*) NULL
						, 0
						, NULL
						, 0);
					  
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						ifconnect=1;
						SetWindowText(GetDlgItem(hwndDlg, IDC_BUTTON1), (LPCTSTR )"Connected");
						RedrawFlag=1;
						//~ SendMessage(hBTN1, WM_CTLCOLORBTN, (WPARAM)GetWindowDC(hBTN1), (LPARAM)hBTN1);
						//~ SendDlgItemMessage(hwndDlg,IDC_BUTTON1
						//~ ,WM_CTLCOLORBTN,(WPARAM)GetWindowDC(hBTN1), (LPARAM)hBTN1);
						InvalidateRect(GetDlgItem(hwndDlg, IDC_BUTTON1),NULL, TRUE);  
						UpdateWindow(GetDlgItem(hwndDlg, IDC_BUTTON1));
						//~ InvalidateRect(hwndDlg,NULL,TRUE);
						//~ MessageBoxPrintf("Prompt","Connected to %s!\n" ,server);							
					}
					else {
						MessageBoxPrintf("Prompt","Fail to Connect to %s!\n",server);	
						ShowDBStmtError(hwndDlg,hdbc);								
					}
				}
				break;
				
				case IDC_BUTTON3:
				{
					//~ MessageBoxPrintf("INFO","length:%d\n",Edit_GetTextLength(hEdit));
					if(!Edit_GetTextLength(hEditTN)){
						MessageBoxPrintf("Error","[SKM.]TABNAME");
						return FALSE;
					}
					
					ZeroMemory(Content,sizeof(Content)/sizeof(char));
					SetDlgItemText(hwndDlg,IDC_EDIT2,Content);										
					if (!ifconnect) {
						MessageBoxPrintf("Prompt","Not Connect yet!\n");						
						return 0;
					}
					//初始化语句句柄
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
					//SQL_NTS telling the function the previous parameter is Null-Terminated String, 
					//please alculate the string length for me
                    if (!GetDlgItemText(hwndDlg, IDC_EDIT1, szTable, sizeof(szTable)/sizeof(SQLCHAR))) 
					{
						*szTable=0;
						MessageBoxPrintf("","%s\n",sqlstr);
					}
					
					// 判断表是否存在
					wsprintf(sqlstr,"select count(0) from syscat.columns where tabname = upper('%s')",szTable);
					retcode = SQLPrepare(hstmt,(SQLCHAR*)sqlstr,SQL_NTS);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					retcode =SQLExecute(hstmt);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					while ( SQLFetch(hstmt) != SQL_NO_DATA_FOUND ){
						SQLINTEGER id=0;
						SQLGetData(hstmt,1,SQL_C_ULONG,&id,sizeof(SQLINTEGER),(SQLINTEGER*)NULL);
						if(0==id){
						MessageBoxPrintf("ERROR","TABLE <%s> does not exists!",szTable);
							return FALSE;
						}
					}
					SQLFreeStmt(hstmt,SQL_CLOSE);

					// do the job
					wsprintf(sqlstr,"select COLNAME from syscat.columns where tabname = upper('%s') ORDER BY COLNO ASC",szTable);
					retcode = SQLPrepare(hstmt,(SQLCHAR*)sqlstr,SQL_NTS);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					retcode =SQLExecute(hstmt);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					while ( SQLFetch(hstmt) != SQL_NO_DATA_FOUND ){
						//~ SQLINTEGER id=0;
						char name[32];
						ZeroMemory(name,sizeof(name)/sizeof(char));
						//~ SQLGetData(hstmt,1,SQL_C_ULONG,&id,sizeof(SQLINTEGER),(SQLINTEGER*)NULL);
						SQLGetData(hstmt,1,SQL_C_CHAR,name,sizeof(name)/sizeof(SQLCHAR),(SQLINTEGER*)NULL);
						//~ MessageBoxPrintf("Result","%s",name);
						strncat(Content,name,32);
						strncat(Content,"\r\n,",32);
					}
					*(Content+strlen(Content)-1)=0;
					//~ strncpy(Content2,Content,strlen(Content)-2);
					SetDlgItemText(hwndDlg,IDC_EDIT2,Content);
					//~ SendMessage(hEdit, EM_LINESCROLL, 0, 80);//WS_VSCROLL
					SQLFreeStmt(hstmt,SQL_CLOSE);
				}				
				default:
					break;
			}
			return TRUE;
		}
		break;
		
	case WM_CTLCOLORBTN:
			//~ hDC = BeginPaint((HWND)wParam, &ps);
			//~ FillRect(hDC, &rect, hbrush);
			//~ EndPaint((HWND)wParam, &ps);		
			//~ if(RedrawFlag){
				//~ hbrush = CreateSolidBrush(RGB(0,255,0));			
				//~ SetTextColor((HDC)wParam,RGB(0,0,0));						
				//~ SetBkColor((HDC)wParam,RGB(0,255,0));
			//~ return (long)hbrush ;
			//~ }
			//~ else 
			//~ {
				//~ SetTextColor((HDC)wParam,RGB(255,0,0));	
				//~ SetBkColor((HDC)wParam,RGB(0,0,0));		
				//~ SetBkMode((HDC)wParam, TRANSPARENT);
				//~ return (long)hbrush ;
			//~ }
	break;
	
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
			SQLFreeStmt(hstmt,SQL_CLOSE);	
			SQLDisconnect(hdbc);	
			SQLFreeHandle(SQL_HANDLE_DBC, hdbc);  
			SQLFreeHandle(SQL_HANDLE_ENV, henv);					
			//~ EndDialog(hwndDlg,0);
			DestroyWindow(hwndDlg);			
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0); 
			return TRUE;
		}
	case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle.
		{
			break;			
		}
	case WM_PAINT:
		{
			if (RedrawFlag == 1){
				hbrush = CreateSolidBrush(RGB(0,255,0));
				hDC = BeginPaint(hBTN1, &ps);
				FillRect(hDC, &rect, hbrush);
				EndPaint(hBTN1, &ps);
				return (LONG)hbrush;
			}
			break;	
		}
	case WM_DRAWITEM:
	{
				dItem = (DRAWITEMSTRUCT*)lParam;
				if (ifconnect){
				SetBkColor(dItem->hDC, RGB(0,255,0));				
					}
					else
					{
				SetBkColor(dItem->hDC, RGB(255,0,0));						
					}
                //~ SetTextColor(dItem->hDC, RGB(0,0,0xFF));
				memset(text, '\0', 20);

				GetWindowText(dItem->hwndItem, text, 20);
				len=lstrlen(text);

				GetTextExtentPoint32(dItem->hDC, text, len, &sz);

				ExtTextOut( dItem->hDC
							, ((dItem->rcItem.right - dItem->rcItem.left) / 2) + dItem->rcItem.left - (sz.cx / 2)
							, ((dItem->rcItem.bottom - dItem->rcItem.top) / 2) + dItem->rcItem.top - (sz.cy / 2)
							, ETO_OPAQUE | ETO_CLIPPED, &dItem->rcItem, text, len, NULL);

				DrawEdge( dItem->hDC, &dItem->rcItem
						, (dItem->itemState & ODS_SELECTED ? BDR_SUNKENOUTER : BDR_RAISEDOUTER), BF_RECT);
                return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
break;			
		
	}
	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{
			break;			
		}
	default:
		break;			
	}
	return FALSE;
}