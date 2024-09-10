void Simple_GOL_Area::draw_background(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	cr->set_source_rgb(0,0,0);
	cr->rectangle(0, 0, width, height);
 	cr->fill();
}