int populate_insert_dlg(HWND hwnd,HWND hlistview,TABLE_WINDOW *win)
{
	int i,count,widths[4]={0,0,0,0};
	int row_sel;
	char *cols[]={"field","data","type","size"};
	if(hlistview==0 || win==0)
		return FALSE;

	for(i=0;i<4;i++)
		widths[i]=lv_add_column(hlistview,cols[i],i);

	row_sel=ListView_GetSelectionMark(win->hlistview);

	count=lv_get_column_count(win->hlistview);

	for(i=0;i<count;i++){
		int w;
		char str[80]={0};
		lv_get_col_text(win->hlistview,i,str,sizeof(str));
		lv_insert_data(hlistview,i,FIELD_POS,str);
		w=get_str_width(hlistview,str);
		if(w>widths[FIELD_POS])
			widths[FIELD_POS]=w;
		if(row_sel>=0){
			str[0]=0;
			ListView_GetItemText(win->hlistview,row_sel,i,str,sizeof(str));
			lv_insert_data(hlistview,i,DATA_POS,str);
			w=get_str_width(hlistview,str);
			if(w>widths[DATA_POS])
				widths[DATA_POS]=w;
		}
		if(win->col_attr!=0){
			char *s="";
			if(!find_sql_type_str(win->col_attr[i].type,&s)){
				_snprintf(str,sizeof(str),"%i",win->col_attr[i].type);
				lv_insert_data(hlistview,i,TYPE_POS,str);
			}
			else
				lv_insert_data(hlistview,i,TYPE_POS,s);
			w=get_str_width(hlistview,s);
			if(w>widths[TYPE_POS])
				widths[TYPE_POS]=w;

			_snprintf(str,sizeof(str),"%i",win->col_attr[i].length);
			lv_insert_data(hlistview,i,SIZE_POS,str);
			w=get_str_width(hlistview,str);
			if(w>widths[SIZE_POS])
				widths[SIZE_POS]=w;
		}
	}
	{
		int total_width=0;
		for(i=0;i<4;i++){
			widths[i]+=12;
			ListView_SetColumnWidth(hlistview,i,widths[i]);
			total_width+=widths[i];
		}
		if(total_width>0){
			int width,height;
			RECT rect={0},irect={0},nrect={0};
			GetWindowRect(hwnd,&irect);
			get_nearest_monitor(irect.left,irect.top,total_width,100,&nrect);
			ListView_GetItemRect(hlistview,0,&rect,LVIR_BOUNDS);
			height=80+(count*(rect.bottom-rect.top+2));
			if((irect.top+height)>nrect.bottom){
				height=nrect.bottom-nrect.top-irect.top;
				if(height<320)
					height=320;
			}
			width=total_width+20;
			SetWindowPos(hwnd,NULL,0,0,width,height,SWP_NOMOVE|SWP_NOZORDER);
		}
	}

	return TRUE;
}