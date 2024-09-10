Gui_DisplayBaseClass::Gui_DisplayBaseClass(Gui_ProcessorHandler& processor_hand):
    m_processor_hand(processor_hand),
    m_deco(this,processor_hand,m_show_idx,m_show_point,m_ROI),
    m_ROI(cv::Point(0,0),cv::Point(0,0)),
    m_draw_result(false),
    m_alph_mask(128),
    m_show_idx(-1),m_show_point(false),m_show_mask(true),
    m_cursor(Gdk::CROSS)
    {

    this->add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
    this->signal_scroll_event().connect( sigc::mem_fun( *this, &Gui_DisplayBaseClass::on_scroll) );
    this->signal_button_press_event().connect( sigc::mem_fun( *this, &Gui_DisplayBaseClass::on_click) );

    m_color.set_rgb_p(0.2,0.2,0.2);
    this->modify_bg(Gtk::STATE_NORMAL,m_color);

    m_processor_hand.signal_state().connect( sigc::mem_fun(*this,&Gui_DisplayBaseClass::myRedraw));

    Glib::RefPtr< Gdk::Screen > screen = Gdk::Screen::get_default();
    Gdk::Rectangle rect;
    screen->get_monitor_geometry(screen->get_primary_monitor(),rect);
    set_size_request(rect.get_width()/4,rect.get_height()/4);



    makeLUT();




}