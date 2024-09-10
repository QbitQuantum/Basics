bool MyArea_private::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	if (pixbuf == 0) return false;
	cr->set_source_rgba(0xff, 0xff, 0xff, 0xff);
	cr->rectangle(0, 0, 800, 640);
	cr->fill();
	Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
	cr->paint();
	cr->stroke();
	return true;
}