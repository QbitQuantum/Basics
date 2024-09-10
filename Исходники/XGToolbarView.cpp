void XGToolbarView::DrawButton(XGDraw &draw, XRect where, long index, unsigned char mode)
{
	bool down;
	short icon;
	
	icon = GetItemIcon(index);
	
	/*
	 *	Draw button frame
	 */
	
	if (0 == (mode & kEnable)) {
		draw.Draw3DRect(where,KXGEBackground);
		::InsetRect(&where,3,3);
		down = false;
	} else {
		if (mode & (kCheck | kDown)) {
			/*
			 *	Draw the outer frame down
			 */
			
			draw.Draw3DRect(where,KXGEInset);
			::InsetRect(&where,1,1);
			draw.Draw3DRect(where,KXGEBackFrame);
			::InsetRect(&where,1,1);
			down = true;
		} else {
			if (index == fOverTool) {
				draw.Draw3DRect(where,KXGEOutset);
			} else {
				draw.Draw3DRect(where,KXGEBackFrame);
			}
			::InsetRect(&where,1,1);
			draw.Draw3DRect(where,KXGEBackFrame);
			::InsetRect(&where,1,1);
			down = false;
		}
		
		/*
		 *	Draw the button outline
		 */
		
		if ((mode & kCheck) && (0 == (mode & kDown))) {
			/*
			 *	Draw the light background
			 */
			
			short r,g,b;
			Color back,light;
			
			back = draw.ColorFromPalette(KXGColorBtnFace);
			light= draw.ColorFromPalette(KXGColorBtnHilite);
			
			r = GetRValue(back);
			r = (r + GetRValue(light))/2;
			g = GetRValue(back);
			g = (g + GetRValue(light))/2;
			b = GetRValue(back);
			b = (b + GetRValue(light))/2;
			
			draw.FillRect(where,RGB(r,g,b));
		} else {
			draw.Draw3DRect(where,KXGEBackground);
		}
		::InsetRect(&where,1,1);
	}

	if (mode & kEnable) {
		if (down) {
			draw.DrawIcon(icon,where.left+1,where.top+1);
		} else {
			draw.DrawIcon(icon,where.left,where.top);
		}
	} else {
		draw.DrawIcon(icon,where.left,where.top,false);
	}
}