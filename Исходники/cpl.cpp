INT_PTR CALLBACK DialogProc(
    HWND hwndDlg,	// handle to dialog box
    UINT uMsg,	// message
    WPARAM wParam,	// first message parameter
    LPARAM lParam 	// second message parameter
   )
{

 WPARAM wp=IDC_FORMAT|(CBN_SELCHANGE<<16);

 switch(uMsg)
 {
 	case WM_ERASEBKGND:
 		HDC dc;
 		dc=(HDC)wParam;
 		RECT r;
 		GetWindowRect(hwndDlg,&r);

 		HBRUSH c_b,prev_b;
 		c_b=CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
        prev_b=(HBRUSH)SelectObject(dc,c_b);
        Rectangle(dc,0,0,r.right-r.left,r.bottom-r.top);
        SelectObject(dc,prev_b);                
        DeleteObject(c_b);
 		return 1; // erased

 	case WM_COMMAND:
 		if(wParam==wp) // format has changed?
 		{
                // update buffer size after format change:
        		HWND bufsize_combo=GetDlgItem(hwndDlg,IDC_BUFFER_SIZE);
        		LRESULT bufsize_selection=SendMessage(bufsize_combo, CB_GETCURSEL,0,0);
        		SendMessage(bufsize_combo, CB_RESETCONTENT,0,0);

        		float sr;

        		LRESULT cursel=SendMessage(GetDlgItem(hwndDlg,IDC_FORMAT), CB_GETCURSEL,0,0);
                sr = (float)device_caps[cursel].sample_rate;

         		int l_1=32,l_2=48;
                for(int l=0;l<9;l++)
                {
                            char txt[64];

                            sprintf(txt,"%0.2f ms (%d samples)",l_1*1000.0f/sr,l_1);
                            add_item(bufsize_combo,txt);
                            l_1=l_1*2;

                            sprintf(txt,"%0.2f ms (%d samples)",l_2*1000.0f/sr,l_2);
                            add_item(bufsize_combo,txt);
                            l_2=l_2*2;
                 }

                 SendMessage(bufsize_combo, CB_SETCURSEL, bufsize_selection, 0);
 		}
 		else
 		switch(wParam)
 		{
 		 case IDOK:
 		    {
 		 	     LRESULT b_fr=SendMessage(GetDlgItem(hwndDlg,IDC_BUFFER_SIZE),CB_GETCURSEL,0,0);
        		 
        		 int id=0;
         		 int l_1=32,l_2=48;

                 for(int l=0;l<9;l++)
                 {
                            if(id==b_fr)
                            {
                             b_fr=l_1;
                             break;
                            }
                            l_1=l_1*2;
                            id++;

                            if(id==b_fr)
                            {
                             b_fr=l_2;
                             break;
                            }
                            l_2=l_2*2;
                            id++;
                 }
                 driver_parameters.block_frames=(int)b_fr;


                 LRESULT mode=SendMessage(GetDlgItem(hwndDlg,IDC_FORMAT),CB_GETCURSEL,0,0);
                 if(mode<0) mode=0;

                 driver_parameters.sampleRate=(ASIOSampleRate)device_caps[mode].sample_rate;
                 driver_parameters.bps=device_caps[mode].bps;
                 driver_parameters.num_inputs=device_caps[mode].n_ins;
                 driver_parameters.num_outputs=device_caps[mode].n_outs;


                 LRESULT method=SendMessage(GetDlgItem(hwndDlg,IDC_SYNC_METHOD),CB_GETCURSEL,0,0);
                 if(method_list[method].name!=0 && method_list[method].mask!=0)
                   driver_parameters.asio_method=method_list[method].mask;

 		         EndDialog(hwndDlg,1);
 		     }
 		     break;
 		 case IDCANCEL:
 		     EndDialog(hwndDlg,-1);
 		     break;
 		 case IDDEFAULTS:
 		     {
 		         SendMessage(GetDlgItem(hwndDlg,IDC_FORMAT), CB_SETCURSEL, 0, 0);
 		         SendMessage(GetDlgItem(hwndDlg,IDC_BUFFER_SIZE), CB_SETCURSEL, 7, 0);
 		         SendMessage(GetDlgItem(hwndDlg,IDC_SYNC_METHOD), CB_SETCURSEL, 0, 0);
 		     }
 		  break;
 		 case IDASIO:
 		  {
       		   // try running kX Mixer
       		   int kx_found=0;
                 EnumWindows(MyEnumWindowsProc,(LPARAM)&kx_found); // look for KX Windows
                 if(kx_found==0)
                 {
                   MessageBox(NULL,"Launch kX Mixer first!","kX ASIO",MB_OK|MB_ICONINFORMATION);
                   // launch kX Mixer -now-
                   EnumWindows(MyEnumWindowsProc,0); // look for KX Windows
                 }
       	  }
          break;
 		} // switch wParam

 		return TRUE;
 	case WM_INITDIALOG:
 		 SetDlgItemText(hwndDlg,IDC_COPYRIGHT,
 		     "kX ASIO Driver Version:"KX_DRIVER_VERSION_STR"\n"KX_COPYRIGHT_STR_R"\nASIO Technology by Steinberg");
 		
 		 KXAsio *pseudo_this=(KXAsio *)lParam;
 		 tmp_device=pseudo_this->device_num;

         float cur_sr=(float)pseudo_this->sampleRate;
         int cur_buf_size=pseudo_this->get_config(KXASIO_LATENCY);

         // buffer size combo:
         {
                 HWND bufsize_combo=GetDlgItem(hwndDlg,IDC_BUFFER_SIZE);
                 int l_1=32,l_2=48;
                 for(int l=0;l<9;l++)
                 {
                   char txt[64];
                   LRESULT id=0;

                   sprintf(txt,"%0.2f ms (%d samples)",l_1*1000.0f/cur_sr,l_1);
                   id=add_item(bufsize_combo,txt);
                   if(cur_buf_size==l_1)
                    SendMessage(bufsize_combo, CB_SETCURSEL, id, 0);
                   l_1=l_1*2;

                   sprintf(txt,"%0.2f ms (%d samples)",l_2*1000.0f/cur_sr,l_2);
                   id=add_item(bufsize_combo,txt);
                   if(cur_buf_size==l_2)
                    SendMessage(bufsize_combo, CB_SETCURSEL, id, 0);
                   l_2=l_2*2;
                 }
                 SendMessage(bufsize_combo, CB_SETDROPPEDWIDTH, 40, 0);
                 ShowWindow(bufsize_combo,SW_SHOW);
         }

         // format combo:
         {
                 HWND fmt_combo=GetDlgItem(hwndDlg,IDC_FORMAT);
                 EnableWindow(fmt_combo,TRUE);

                 int caps_sz=sizeof(device_caps);
                 if(pseudo_this->ikx->get_device_caps(device_caps,&caps_sz)==0 && caps_sz>0)
                 {
                   total_caps=caps_sz/sizeof(kx_caps);

                   for(int i=0;i<total_caps;i++)
                   {
                       LRESULT id=add_item(fmt_combo,device_caps[i].friendly_name);

                       if(pseudo_this->bps==device_caps[i].bps &&
                          (int)pseudo_this->sampleRate==device_caps[i].sample_rate &&
                          pseudo_this->num_outputs==device_caps[i].n_outs &&
                          pseudo_this->num_inputs==device_caps[i].n_ins)
                       {
                         SendMessage(fmt_combo, CB_SETCURSEL, id, 0);
                       }
                   }

                 } else EnableWindow(fmt_combo,FALSE);

                 SendMessage(fmt_combo, CB_SETDROPPEDWIDTH, 40, 0);
                 ShowWindow(fmt_combo,SW_SHOW);
         }

         // cardname
         {
                 HWND card=GetDlgItem(hwndDlg,IDC_CARD_NAME);
                 // actually, edit
                 SetWindowText(card,pseudo_this->ikx->get_device_name());
         }

         // method
         {
                 HWND sync_method=GetDlgItem(hwndDlg,IDC_SYNC_METHOD);
                 EnableWindow(sync_method,TRUE);

                 int cur_method=pseudo_this->get_config(KXASIO_ASIO_METHOD);

                 int i=0;
                 while(method_list[i].name)
                 {
                    LRESULT cur_item=SendMessage(sync_method, CB_ADDSTRING, 0, (LPARAM)method_list[i].name);
                    if(method_list[i].mask==cur_method)
                    {
                     SendMessage(sync_method, CB_SETCURSEL, cur_item, 0);
                     cur_method=-2;
                    }
                    i++;
                 }

                 if(cur_method!=-2) // not found?
                 {
                     LRESULT cur_item=SendMessage(sync_method, CB_ADDSTRING, 0, (LPARAM)"(Custom)");
                     SendMessage(sync_method, CB_SETCURSEL, cur_item, 0);
                 }

                 SendMessage(sync_method, CB_SETDROPPEDWIDTH, 40, 0);
                 ShowWindow(sync_method,SW_SHOW);
         }

 		 BringWindowToTop(hwndDlg);

 		 return TRUE;
 }

 return FALSE;
}