void sourceview___::scroll2__(SourceView*sv,Gtk::TextIter ti){
	RefPtr<Gtk::TextBuffer> tb=sv->get_buffer();
	tb->place_cursor(ti);
	Gtk::TextBuffer::iterator i1,i2;
	tb->get_selection_bounds(i1,i2);

	Gdk::Rectangle rect;
	sv->get_visible_rect(rect);
	int y = -1;
	int height = -1;
	sv->get_line_yrange(i1, y, height);
	if (y < rect.get_y() + rect.get_height() + 16)
		 sv->scroll_to_mark(tb->get_insert(), 0);
}