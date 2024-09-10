/// Draw this item and its children.
void Fl_Tree_Item::draw(int X, int &Y, int W, Fl_Widget *tree, 
                        const Fl_Tree_Prefs &prefs, int lastchild) {
    if ( ! _visible ) return; 
    fl_font(_labelfont, _labelsize);
    int H = _labelsize + fl_descent() + prefs.linespacing();
    // Colors, fonts
    Fl_Color fg = _selected ? prefs.bgcolor()     : _labelfgcolor;
    Fl_Color bg = _selected ? prefs.selectcolor() : _labelbgcolor;
    if ( ! _active ) {
	fg = fl_inactive(fg);
	if ( _selected ) bg = fl_inactive(bg);
    }
    // Update the xywh of this item
    _xywh[0] = X;
    _xywh[1] = Y;
    _xywh[2] = W;
    _xywh[3] = H;
    // Text size
    int textw=0, texth=0;
    fl_measure(_label, textw, texth, 0);
    int textycenter = Y+(H/2);
    int &icon_x = _collapse_xywh[0] = X-1;
    int &icon_y = _collapse_xywh[1] = textycenter - (prefs.openicon()->h()/2);
    int &icon_w = _collapse_xywh[2] = prefs.openicon()->w();
    _collapse_xywh[3] = prefs.openicon()->h();
    // Horizontal connector values
    int hstartx  = X+icon_w/2-1;
    int hendx    = hstartx + prefs.connectorwidth();
    int hcenterx = X + icon_w + ((hendx - (X + icon_w)) / 2);

    // See if we should draw this item
    //    If this item is root, and showroot() is disabled, don't draw.
    //
    char drawthis = ( is_root() && prefs.showroot() == 0 ) ? 0 : 1;
    if ( drawthis ) {
	// Draw connectors
	if ( prefs.connectorstyle() != FL_TREE_CONNECTOR_NONE ) {
	    // Horiz connector between center of icon and text
	    draw_horizontal_connector(hstartx, hendx, textycenter, prefs);
	    if ( has_children() && is_open() ) {
		// Small vertical line down to children
		draw_vertical_connector(hcenterx, textycenter, Y+H, prefs);
	    }
	    // Connectors for last child
	    if ( ! is_root() ) {
		if ( lastchild ) {
		    draw_vertical_connector(hstartx, Y, textycenter, prefs);
		} else {
		    draw_vertical_connector(hstartx, Y, Y+H, prefs);
		}
	    }
	} 
	// Draw collapse icon
	if ( has_children() && prefs.showcollapse() ) {
	    // Draw icon image
	    if ( is_open() ) {
		prefs.closeicon()->draw(icon_x,icon_y);
	    } else {
		prefs.openicon()->draw(icon_x,icon_y);
	    }
	}
	// Background for this item
	int &bx = _label_xywh[0] = X+(icon_w/2-1+prefs.connectorwidth());
	int &by = _label_xywh[1] = Y;
	int &bw = _label_xywh[2] = W-(icon_w/2-1+prefs.connectorwidth());
	int &bh = _label_xywh[3] = texth;
	// Draw bg only if different from tree's bg
	if ( bg != tree->color() || is_selected() ) {
	    if ( is_selected() ) {
		// Selected? Use selectbox() style
		fl_draw_box(prefs.selectbox(), bx, by, bw, bh, bg);
	    } else {
		// Not Selected? use plain filled rectangle
		fl_color(bg);
		fl_rectf(bx, by, bw, bh);
	    }
	}
	// Draw user icon (if any)
	int useroff = (icon_w/2-1+prefs.connectorwidth());
	if ( usericon() ) {
	    // Item has user icon? Use it
	    useroff += prefs.usericonmarginleft();
	    usericon()->draw(X+useroff,icon_y);
	    useroff += usericon()->w();
	} else if ( prefs.usericon() ) {
	    // Prefs has user icon? Use it
	    useroff += prefs.usericonmarginleft();
	    prefs.usericon()->draw(X+useroff,icon_y);
	    useroff += prefs.usericon()->w();
	}
	useroff += prefs.labelmarginleft();
	// Draw label
	if ( widget() ) {
	    // Widget? Draw it
	    int lx = X+useroff;
	    int ly = by;
	    int lw = widget()->w();
	    int lh = bh;
	    if ( widget()->x() != lx || widget()->y() != ly ||
		 widget()->w() != lw || widget()->h() != lh ) {
		widget()->resize(lx, ly, lw, lh);		// fltk will handle drawing this
	    }
	} else {
	    // No label widget? Draw text label
	    if ( _label ) {
		fl_color(fg);
		fl_draw(_label, X+useroff, Y+H-fl_descent()-1);
	    }
	}
	Y += H;
    }			// end drawthis
    // Draw children
    if ( has_children() && is_open() ) {
	int child_x = drawthis ? 			// offset children to right,
	              (hcenterx - (icon_w/2) + 1) : X;	// unless didn't drawthis
	int child_w = W - (child_x-X);
	int child_y_start = Y;
	for ( int t=0; t<children(); t++ ) {
	    int lchild = ((t+1)==children()) ? 1 : 0;
	    _children[t]->draw(child_x, Y, child_w, tree, prefs, lchild);
	}
	if ( has_children() && is_open() ) {
	    Y += prefs.openchild_marginbottom();	// offset below open child tree
	}
	if ( ! lastchild ) {
	    draw_vertical_connector(hstartx, child_y_start, Y, prefs);
	}
    }
}