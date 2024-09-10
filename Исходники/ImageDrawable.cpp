static void copyCairoClip(const Cairo::RefPtr<Cairo::Context> &src, const Cairo::RefPtr<Cairo::Context> &dst) {
	try {
		vector<Cairo::Rectangle> rects;
		src->copy_clip_rectangle_list(rects);
		for (auto& rect : rects) {
			//cout << "clip " << rect.x << "x" << rect.y << "+" << rect.width << "+" << rect.height << endl;
			dst->rectangle(rect.x, rect.y, rect.width, rect.height);
		}
		dst->clip();
	} catch (...) {
		Cairo::Rectangle rect;
		src->get_clip_extents(rect.x, rect.y, rect.width, rect.height);
		rect.width -= rect.x;
		rect.height -= rect.y;
		//cout << "clip " << rect.x << "x" << rect.y << "+" << rect.width << "+" << rect.height << endl;
		dst->rectangle(rect.x, rect.y, rect.width, rect.height);
		dst->clip();
	}
}