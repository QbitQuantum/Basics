void Tab::ResetScrollBars(){
	int widget_height,widget_width;
	int max_height,max_width;
	max_height=0;
	max_width=0;

	// It doesn't make sense to add scrollbars for a TAB without a size
	if(this->w==0 || this->h==0 ) return;

	// Find the Max edges
	Widget* widget;
	list<Widget *>::iterator i;
	for( i = children.begin(); i != children.end(); ++i ) {
		widget = *i;
		widget_width = widget->GetX()+widget->GetW();
		widget_height = widget->GetY()+widget->GetH();
		if( widget_height > max_height) max_height=widget_height;
		if( widget_width > max_width) max_width=widget_width;
	}
	max_height += SCROLLBAR_THICK + SCROLLBAR_PAD;

	// Add a Vertical ScrollBar if necessary
	if ( max_height > GetH() || this->vscrollbar != NULL ){
		int v_x = this->w-SCROLLBAR_THICK-SCROLLBAR_PAD;
		int v_y = SCROLLBAR_PAD;
		int v_l = this->h-2*SCROLLBAR_PAD;
		// Only add a Scrollbar when it doesn't already exist
		if ( this->vscrollbar ){
			Container::DelChild( this->vscrollbar );
			this->vscrollbar = NULL;
			LogMsg(INFO, "Changing Vert ScrollBar to %s: (%d,%d) [%d]\n", GetName().c_str(),v_x,v_y,v_l );
			
		} else {
			LogMsg(INFO, "Adding Vert ScrollBar to %s: (%d,%d) [%d]\n", GetName().c_str(),v_x,v_y,v_l );
		}

		this->vscrollbar = new Scrollbar(v_x, v_y, v_l,this);

		Container::AddChild( this->vscrollbar );

		this->vscrollbar->maxpos = max_height;
	}
}