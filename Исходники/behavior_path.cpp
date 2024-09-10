		virtual BOOL on_draw   (HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc ) 
		{ 
			if( draw_type != DRAW_CONTENT )
				return FALSE; /*do default draw*/ 

			dom::element el = he;
			const wchar_t* filename = el.get_attribute("filename");
			if( !filename )
				return FALSE;  // no such attribute at all.

			// 先画图标
			SHFILEINFOW sfi;
			HIMAGELIST hlist = (HIMAGELIST) SHGetFileInfoW( filename,
				0, &sfi, sizeof(SHFILEINFO), 
				/*SHGFI_USEFILEATTRIBUTES |*/ SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
			if(!hlist)
				return FALSE;
			int szx = 16;
			int szy = 16;
			ImageList_GetIconSize(hlist, &szx, &szy);
			int x = rc.left - 19; // 水平居左 // + (rc.right - rc.left - szx) / 2; 
			int y = rc.top + (rc.bottom - rc.top - szy) / 2; // 垂直居中

			//draw_file_icon(hdc, x, y, filename);
			ImageList_Draw(hlist, sfi.iIcon, hdc, x, y, ILD_TRANSPARENT);

			// 输出文字
			UINT pta = GetTextAlign(hdc);
			SetTextAlign(hdc, TA_LEFT | TA_TOP |TA_NOUPDATECP); 
			DrawTextW(hdc,  (is_fullpath(el) && (wcslen(filename) > 1)) ? filename : el.text(),
				-1,const_cast<RECT*>(&rc), 
				DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_PATH_ELLIPSIS | DT_NOPREFIX);
			SetTextAlign(hdc, pta); 

			return TRUE; /*skip default draw as we did it already*/ 
		}