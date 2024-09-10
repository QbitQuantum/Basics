void
Renderer_Dragbox::render_vfunc(
	const Glib::RefPtr<Gdk::Window>& drawable,
	const Gdk::Rectangle& /*expose_area*/
)
{
	assert(get_work_area());
	if(!get_work_area())
		return;

	// const synfig::Vector focus_point(get_work_area()->get_focus_point());
	// Warning : Unused focus_point
	int drawable_w = drawable->get_width();
	int drawable_h = drawable->get_height();

	Cairo::RefPtr<Cairo::Context> cr = drawable->create_cairo_context();

	const synfig::Vector::value_type window_startx(get_work_area()->get_window_tl()[0]);
	const synfig::Vector::value_type window_starty(get_work_area()->get_window_tl()[1]);
	const float pw(get_pw()),ph(get_ph());

	const synfig::Point& curr_point(get_curr_point());
	const synfig::Point& drag_point(get_drag_point());

	{
		cr->save();
		cr->set_line_cap(Cairo::LINE_CAP_BUTT);
		cr->set_line_join(Cairo::LINE_JOIN_MITER);
		cr->set_antialias(Cairo::ANTIALIAS_NONE);

		cr->set_line_width(1.0);
		cr->set_source_rgb(0,0,0);
		std::valarray<double> dashes(2);
		dashes[0]=5.0;
		dashes[1]=5.0;
		cr->set_dash(dashes, 0);

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

		cr->rectangle(
			tl[0],
			tl[1],
			br[0]-tl[0],
			br[1]-tl[1]
		);
		cr->stroke();

		cr->restore();
	}
}