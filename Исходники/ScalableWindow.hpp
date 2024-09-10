		[[nodiscard]] inline RectF GetVirtualWindowArea(const Size& baseSize = Window::BaseSize())
		{
			const double sx = static_cast<double>(Window::Width()) / baseSize.x;
	
			const double sy = static_cast<double>(Window::Height()) / baseSize.y;
	
			const double s = Min(sx, sy);
	
			if (sx <= sy)
			{
				return RectF(baseSize * s).moveBy(0, (Window::Height() - baseSize.y * s) * 0.5);
			}
			else
			{
				return RectF(baseSize * s).moveBy((Window::Width() - baseSize.x * s) * 0.5, 0);
			}
		}