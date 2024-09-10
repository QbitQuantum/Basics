	static Color Sample(const Bitmap& bitmap, float u, float v)
	{
		int width = bitmap.GetWidth();
		int height = bitmap.GetHeight();

		float fx = XAddresserType::CalcAddress(u, width);
		int x0 = Mathf::FloorToInt(fx);
		float fy = YAddresserType::CalcAddress(v, height);
		int y0 = Mathf::FloorToInt(fy);
		float xFrac = fx - x0;
		float yFrac = fy - y0;
		x0 = XAddresserType::FixAddress(x0, width);
		y0 = YAddresserType::FixAddress(y0, height);
		int x1 = XAddresserType::FixAddress(x0 + 1, width);
		int y1 = YAddresserType::FixAddress(y0 + 1, height);

		Color c0 = bitmap.GetPixel(x0, y0);
		Color c1 = bitmap.GetPixel(x1, y0);
		Color c2 = bitmap.GetPixel(x0, y1);
		Color c3 = bitmap.GetPixel(x1, y1);

		return Color::Lerp(c0, c1, c2, c3, xFrac, yFrac);
	}