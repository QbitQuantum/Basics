void ReorderWindows(ATTACHED_WINDOWS& atws, int& bRedraw, int &redo, HWND hParent)
{
	std::vector<HWND_DEPENDENCY> dependencies;

	redo = 0;

	std::vector<ATTACHED_WINDOW>::iterator atw = atws.begin();
	HRGN rgn_final = CreateRectRgn(0,0,0,0);
	
	/* iterate through all attachments */
	for (; atw != atws.end(); atw++) {
	
		HWND_DEPENDENCY hwnd_dependency;
		hwnd_dependency.hWnd = atw->hWnd;

		RECT r_dest;
		GetWindowRect(atw->hWnd, &r_dest);
		
		int w_dest = r_dest.right - r_dest.left;
		int h_dest = r_dest.bottom - r_dest.top;

		if (atw->flags & ATTB_WIDTHRATIO) {
			RECT r;
			GetWindowRect(atw->hWndWidth, &r);
			int _w_dest = (int)((float)(r.right - r.left) * atw->width_ratio);
			if (_w_dest != w_dest) {
				hwnd_dependency.hWnd_depends_on.push_back(atw->hWndWidth);
				redo = 1;
				w_dest = _w_dest;
			} 
		}

		if (atw->flags & ATTB_HEIGHTRATIO) {
			RECT r;
			GetWindowRect(atw->hWndHeight, &r);
			int _h_dest = (int)((float)(r.bottom - r.top) * atw->height_ratio);
			if (h_dest != _h_dest) {
				hwnd_dependency.hWnd_depends_on.push_back(atw->hWndHeight);
				h_dest = _h_dest;
				redo = 1;
			} 
		}

		bool keep_width  = (atw->flags & ATTB_LEFTRIGHT) != ATTB_LEFTRIGHT;
		bool keep_height = (atw->flags & ATTB_TOPBOTTOM) != ATTB_TOPBOTTOM;

		ScreenToClient(hParent, &r_dest);

		RECT r_old = r_dest;
		HRGN rgn_old  = CreateRectRgn(r_dest.left, r_dest.top, r_dest.right - 2, r_dest.bottom - 2);
		HRGN rgn_upd  = CreateRectRgn(0,0,0,0);

		// obtain border region
		HRGN rgn_border = CreateRectRgn(0,0,0,0);
		bool bError = false;

		if (rgn_old == ERROR || rgn_upd == ERROR || rgn_border == ERROR) 
			bError = true;

		RECT r_client;
		GetClientRect(atw->hWnd, &r_client);
		ClientToScreen(atw->hWnd, &r_client);
		ScreenToClient(hParent, &r_client);
		HRGN rgn_clt = CreateRectRgn(r_client.left, r_client.top, r_client.right, r_client.bottom);
		if (rgn_clt == ERROR)
			bError = true;

		if (CombineRgn(rgn_border, rgn_clt, rgn_old, RGN_XOR) == ERROR)
			bError = true;

		std::vector<ATTACHED_BORDER>::iterator atb = atw->attached_borders.begin();

		for (; atb != atw->attached_borders.end(); atb++) {
			RECT r_source;
			GetWindowRect(atb->hWndAttachedTo, &r_source);
			ScreenToClient(hParent, &r_source);

			int value1 = -1;
			int value2 = -1;
			LONG* target1 = NULL;
			LONG* target2 = NULL;

			switch (atb->border) {
				case ATTB_LEFT: 
				case ATTB_HCENTER:
					target1 = &r_dest.left; 
					if (keep_width)
						target2 = &r_dest.right;
					break;
				case ATTB_RIGHT: 
					target1 = &r_dest.right; 
					if (keep_width)
						target2 = &r_dest.left;
					break;
				case ATTB_TOP: 
				case ATTB_VCENTER:
					target1 = &r_dest.top; 
					if (keep_height)
						target2 = &r_dest.bottom;
					break;
				case ATTB_BOTTOM: 
					target1 = &r_dest.bottom; 
					if (keep_height)
						target2 = &r_dest.top;
					break;
				default:
					ASSERT(0);
			}
			
			switch (atb->target_border) {
				case ATTB_LEFT: 
				case ATTB_RIGHT:
				case ATTB_HCENTER:
					if (atb->target_border == ATTB_LEFT)
						value1 = r_source.left + atb->distance; 
					else if (atb->target_border == ATTB_RIGHT)
						value1 = r_source.right + atb->distance;
					else if (atb->target_border == ATTB_HCENTER)
						value1 = (r_source.left + r_source.right)/2 + atb->distance;
					else
						ASSERT(0);
	
					if (atb->border == ATTB_LEFT) 
						value2 = value1 + w_dest;
					else if (atb->border == ATTB_RIGHT)
						value2 = value1 - w_dest;
					else if (atb->border == ATTB_HCENTER) {
						value1 = value1 - w_dest/2;
						value2 = value1 + w_dest;
					} else
						ASSERT(0);

					break;
				case ATTB_TOP: 
				case ATTB_BOTTOM:
				case ATTB_VCENTER:
					if (atb->target_border == ATTB_TOP)
						value1 = r_source.top + atb->distance; 
					else if (atb->target_border == ATTB_BOTTOM)
						value1 = r_source.bottom + atb->distance;
					else if (atb->target_border == ATTB_VCENTER)
						value1 = (r_source.bottom + r_source.top)/2 + atb->distance;
					else
						ASSERT(0);

					if (atb->border == ATTB_TOP)
						value2 = value1 + h_dest;
					else if (atb->border == ATTB_BOTTOM)
						value2 = value1 - h_dest;
					else if (atb->border == ATTB_VCENTER) {
						value1 = value1 - h_dest/2;
						value2 = value1 + h_dest;
					} else
						ASSERT(0);
					break;
				default:
					ASSERT(0);
			}

			*target1 = value1;			
			if (target2)
				*target2 = value2;
		}

		MoveWindow(atw->hWnd, r_dest.left, r_dest.top, 
			r_dest.right - r_dest.left, r_dest.bottom - r_dest.top, false);

		HRGN rgn_new = CreateRectRgn(r_dest.left, r_dest.top, r_dest.right + 1, r_dest.bottom + 1);
		if (rgn_new == ERROR) bError = true;
		if (CombineRgn(rgn_upd, rgn_old, rgn_new, RGN_XOR) == ERROR) bError = true;
		
		if (IsWindowVisible(atw->hWnd))
			if (CombineRgn(rgn_final, rgn_final, rgn_upd, RGN_OR) == ERROR) bError = true;

		int border_size = 2;
		HRGN rgn_temp = CreateRectRgn(r_old.right - border_size, r_old.top, r_old.right + 1, r_old.bottom + 1);
		if (rgn_temp == ERROR) bError = true;

		if (IsWindowVisible(atw->hWnd))
			if (CombineRgn(rgn_final, rgn_final, rgn_temp, RGN_OR) == ERROR) bError = true;
		DeleteObject(rgn_temp);

		rgn_temp = CreateRectRgn(r_old.left, r_old.bottom - border_size, r_old.right + 1, r_old.bottom + 1);
		if (rgn_temp == ERROR) bError = true;

		if (IsWindowVisible(atw->hWnd))
			if (CombineRgn(rgn_final, rgn_final, rgn_temp, RGN_OR) == ERROR) bError = true;;
		DeleteObject(rgn_temp);

		if (!bError)
			if (IsWindowVisible(atw->hWnd))
				if (CombineRgn(rgn_final, rgn_final, rgn_border, RGN_OR) == ERROR) bError = true;

		if (r_old.top != r_dest.top || r_old.left != r_dest.left) {
			if (IsWindowVisible(atw->hWnd))
				CombineRgn(rgn_final, rgn_final, rgn_new, RGN_OR);
		}	

		DeleteObject(rgn_old);
		DeleteObject(rgn_new);
		DeleteObject(rgn_upd);
		DeleteObject(rgn_border);
		DeleteObject(rgn_clt);

		if (!hwnd_dependency.hWnd_depends_on.empty())
			dependencies.push_back(hwnd_dependency);

	}

	InvalidateRgn(hParent, rgn_final, true);

	ASSERT(!cross_dependencies(dependencies));

	DeleteObject(rgn_final);
	bRedraw = 1;
}