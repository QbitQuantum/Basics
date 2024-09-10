void
Renderer_BBox::render_vfunc(
	const Glib::RefPtr<Gdk::Window>& drawable,
	const Gdk::Rectangle& /*expose_area*/
)
{
	assert(get_work_area());
	if(!get_work_area())
		return;

	Cairo::RefPtr<Cairo::Context> cr = drawable->create_cairo_context();

	const synfig::Vector::value_type window_startx(get_work_area()->get_window_tl()[0]);
	const synfig::Vector::value_type window_starty(get_work_area()->get_window_tl()[1]);
	const float pw(get_pw()),ph(get_ph());

	const synfig::Point curr_point(get_bbox().get_min());
	const synfig::Point drag_point(get_bbox().get_max());
	if(get_bbox().area()<10000000000000000.0 && get_bbox().area()>0.00000000000000001)
	{
		Point tl(std::min(drag_point[0],curr_point[0]),std::min(drag_point[1],curr_point[1]));
		Point br(std::max(drag_point[0],curr_point[0]),std::max(drag_point[1],curr_point[1]));

		tl[0]=(tl[0]-window_startx)/pw;
		tl[1]=(tl[1]-window_starty)/ph;
		br[0]=(br[0]-window_startx)/pw;
		br[1]=(br[1]-window_starty)/ph;
		if(tl[0]>br[0])
			swap(tl[0],br[0]);
		if(tl[1]>br[1])
			swap(tl[1],br[1]);

		cr->save();
		cr->set_line_cap(Cairo::LINE_CAP_BUTT);
		cr->set_line_join(Cairo::LINE_JOIN_MITER);

		cr->set_line_width(1.0);
		cr->set_source_rgb(1.0,1.0,1.0);

		// Operator difference was added in Cairo 1.9.4
		// It currently isn't supported by Cairomm
#if CAIRO_VERSION >= 10904
		cairo_set_operator(cr->cobj(), CAIRO_OPERATOR_DIFFERENCE);
#else
		// Fallback: set color to black
        cr->set_source_rgb(0,0,0);
#endif

		cr->rectangle(
			int(tl[0])+0.5,
			int(tl[1])+0.5,
			int(br[0]-tl[0]+1),
			int(br[1]-tl[1]+1)
		);
		cr->stroke();

		cr->restore();
	}
}