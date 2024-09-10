GlobalViewFrame::GlobalViewFrame(QWidget *p_parent,Editor *p_editor) : QFrame (p_parent) {
	
	editor=p_editor;
	
	QGridLayout *l = new QGridLayout(this);
	
	cursor_op= new GlobalViewCursor(this);
	
	l->addWidget(cursor_op,0,0,1,3);
		
	
	QFrame *gb_frame = new QFrame( this );
	gb_frame->setLayout(new QHBoxLayout(gb_frame));
	gb_frame->setLineWidth(0);
	gb_frame->setFrameStyle(Panel+Sunken);
	gb_frame->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	l->addWidget(gb_frame,1,0,1,2);
	marker_column = new MarkerColumn(gb_frame,editor);
	gb_frame->layout()->addWidget(marker_column);	
	loop_column = new LoopColumn(gb_frame,editor);
	gb_frame->layout()->addWidget(loop_column);
	beat_bar_column = new GlobalBeatBarColumn(gb_frame,editor);
	gb_frame->layout()->addWidget(beat_bar_column);
	
	
	CVBox *gv_vbox = new CVBox( gb_frame );
	
	global_view = new GlobalView( gv_vbox, p_editor);
	gb_frame->layout()->addWidget(gv_vbox);
	gb_frame->layout()->setMargin(0);
	gb_frame->layout()->setSpacing(0);
	
	
	marker_column->set_global_view( global_view );
	loop_column->set_global_view( global_view );
	beat_bar_column->set_global_view( global_view );


//	v_scroll = new QScrollBar(Qt::Vertical,this);
	v_scroll = new PixmapScrollBar(this,PixmapScrollBar::Skin(GET_SKIN(SKINBOX_THEME_SCROLLBAR_V_BG),GET_SKIN(SKINBOX_THEME_SCROLLBAR_GRABBER)),PixmapScrollBar::TYPE_VERTICAL);
	
	
	l->addWidget(v_scroll,1,2);
	
	
	
	QWidget *hw = new QWidget(this);
	QHBoxLayout *h = new QHBoxLayout(hw);
	hw->setLayout(h);
	
	l->addWidget(hw,2,1);
	//h_scroll = new QScrollBar(Qt::Horizontal,hw);
	h_scroll = new PixmapScrollBar(gv_vbox,PixmapScrollBar::Skin(GET_SKIN(SKINBOX_THEME_SCROLLBAR_H_BG),GET_SKIN(SKINBOX_THEME_SCROLLBAR_GRABBER)),PixmapScrollBar::TYPE_HORIZONTAL);
	h_scroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	h_scroll->hide();
	//h->addWidget(h_scroll);
	//l->addWidget( new PixmapLabel(this,GET_QPIXMAP(THEME_GLOBAL_TOOLBAR__BOTTOM_RIGHT_PIXMAP)),2,2);
//	zoom = new QSlider(Qt::Horizontal,hw);
//	zoom->setRange(0,100);
//	zoom->setValue(0);
	
//	h->addWidget(zoom);
//	h->setStretchFactor(h_scroll,4);
//	h->setStretchFactor(zoom,1);
//	QLabel *z=new QLabel(this);
//	z->setPixmap(GET_QPIXMAP(ICON_ZOOM_SMALL));
//	l->addWidget(z,2,2);
	
	//some default
//	zoom_changed_slot( 35 );
//	zoom->setValue(35); 
	
	QObject::connect(global_view,SIGNAL(resized_signal()),this,SLOT(block_list_changed_slot()));
	QObject::connect(global_view,SIGNAL(resized_signal()),this,SIGNAL(global_view_changed_blocks_signal()));
	QObject::connect(h_scroll,SIGNAL(value_changed_signal( int )),this,SLOT(h_scollbar_changed_slot( int )));
	QObject::connect(v_scroll,SIGNAL(value_changed_signal(int)),this,SLOT(v_scollbar_changed_slot( int )));
	QObject::connect(cursor_op,SIGNAL(zoom_changed( float )),this,SLOT(zoom_changed_slot(float)));
	QObject::connect(cursor_op,SIGNAL(edit_mode_changed_signal( int )),global_view,SLOT(set_edit_mode( int )));
	QObject::connect(cursor_op,SIGNAL(delete_clicked_signal()),global_view,SLOT(delete_selected_blocks()));
	
	QObject::connect(cursor_op,SIGNAL(select_linked_signal()),global_view,SLOT(select_linked_slot()));
	QObject::connect(cursor_op,SIGNAL(unlink_selected_signal()),global_view,SLOT(unlink_selected_slot()));

	QObject::connect(cursor_op,SIGNAL(repeat_set_signal()),global_view,SLOT(block_repeat_set_signal()));
	QObject::connect(cursor_op,SIGNAL(repeat_unset_signal()),global_view,SLOT(block_repeat_unset_signal()));
	
	l->setMargin(0);
	l->setSpacing(0);
	h->setMargin(0);
	
	//setFrameStyle(Panel+Sunken);
	setLineWidth(0);
	
}