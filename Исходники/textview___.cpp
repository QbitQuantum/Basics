int textview___::insert__(std::deque<Glib::ustring>* p,size_t start){
	Gtk::TextView* tv=tv__(p,1+start);
	if(!tv){
		return 1;
	}
	int i=0;
	size_t i_ctl=3+start;
	if(p->size()>i_ctl){
		if((*p)[i_ctl]=="头")
			i=1;
		else if((*p)[i_ctl]=="尾")
			i=2;
		else{
			d_(sh_,err_show_buzhichi_,2,p,i_ctl);
			return 1;
		}
	}
	Glib::RefPtr < Gtk::TextBuffer > tb = tv->get_buffer();
	Gtk::TextBuffer::iterator i1,i2;
	switch(i){
	case 1:
		i1=tb->begin();
		break;
	case 2:
		i1=tb->end();
		break;
	default:
		tb->get_selection_bounds(i1,i2);
		if(i2>i1){
			i1=tb->erase(i1,i2);
		}
		break;
	}
	Gdk::Rectangle rect;
	tv->get_visible_rect(rect);
	int y = -1;
	int height = -1;
	tv->get_line_yrange(i1, y, height);
	tb->place_cursor(tb->insert(i1, (*p)[2+start]));
	if (y < rect.get_y() + rect.get_height() + 16)
		 tv->scroll_to_mark(tb->get_insert(), 0);
	return 1;
}