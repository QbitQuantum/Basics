		void setPos(Point2 pos)
		{
			if(IsWindow(hwnd_)) {
				Context himc(hwnd_);
				COMPOSITIONFORM form = { CFS_POINT, { pos.x, pos.y }, { 0, 0, 0, 0} };
				ImmSetCompositionWindow(himc, &form);
			}
		}