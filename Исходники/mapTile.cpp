void MapTile::init()
{
    
    image = gl::Texture(loadImage(loadResource(MAP_IMG)));
    
    std::cout << "Image size " << image.getSize() << std::endl;
    
    maporigin.x = cinder::app::getWindowWidth()/2;
    maporigin.y = cinder::app::getWindowHeight()/2;
    
    //my vars
    
    track_mode = MODE_IDLE;
    
    currW = 0;
    
    zoom = 0.5;
    offset_zoom = 0.0;
    
    color = ColorA(0.2,0.3,0.4,0.7);
    
    int pad = getWindowWidth()/5;
    

    
    
    sliders.push_back( Slider( Vec2f(getWindowWidth()*0.1, getWindowHeight()/2) , Vec2f(30, 500),  ColorA(0.9,0.4,0.5,0.5), GEST_EL,  Slider::VERTICAL )  );

    
    hide_all_sliders();
    
    
    timer.start();
    
    
    //init pointers
    ref_pos = cv::Point3f(-1,-1,-1);
    empty_hand = new gestoos::nui::Hand();
    empty_hand2 = new gestoos::nui::Hand();
    empty_hand->clear();
    empty_hand2->clear();
    hand_g = empty_hand;
    hand_slider = empty_hand2;

    //std::cout<<" hand_g present "<<hand_g->is_present()<<std::endl;
    
}