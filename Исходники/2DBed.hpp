	Bed_2D(wxWindow* parent) 
	{
		Create(parent, wxID_ANY, wxDefaultPosition, wxSize(250, -1), wxTAB_TRAVERSAL);
//		m_user_drawn_background = $^O ne 'darwin';
		m_user_drawn_background = true;
		Bind(wxEVT_PAINT, ([this](wxPaintEvent e) { repaint(); }));
//		EVT_ERASE_BACKGROUND($self, sub{}) if $self->{user_drawn_background};
//		Bind(EVT_MOUSE_EVENTS, ([this](wxMouseEvent  event){/*mouse_event()*/; }));
		Bind(wxEVT_LEFT_DOWN, ([this](wxMouseEvent  event){ mouse_event(event); }));
		Bind(wxEVT_MOTION, ([this](wxMouseEvent  event){ mouse_event(event); }));
		Bind(wxEVT_SIZE, ([this](wxSizeEvent e) { Refresh(); }));
	}