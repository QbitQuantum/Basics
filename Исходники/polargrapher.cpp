	//plots point to pixel(s)
	void plot() {

		//convert polar to cartesian
		double x = r * cos(t);
		double y = r * sin(t);

		if(x + 1 + size/2 > size || x - 1 + size/2 < 0 || y + 1 + size/2 > size || y - 1 + size/2 < 0)
			return;

		graph.setPixel((x + size/2), (y + size/2), color);

		if(line_width == 1 || line_width == 2) {
			graph.setPixel((x + size/2), (y + 1 + size/2), color);
			graph.setPixel((x + size/2), (y - 1 + size/2), color);
			graph.setPixel((x + 1 + size/2), (y + size/2), color);
			graph.setPixel((x - 1 + size/2), (y + size/2), color);
		}

		if(line_width == 2) {
			graph.setPixel((x + 1 + size/2), (y + 1 + size/2), color);
			graph.setPixel((x + 1 + size/2), (y - 1 + size/2), color);
			graph.setPixel((x - 1 + size/2), (y - 1 + size/2), color);
			graph.setPixel((x - 1 + size/2), (y + 1 + size/2), color);
		}
	}