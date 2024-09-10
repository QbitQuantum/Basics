void Example4App::setup()
{
    gl::clear( Color( 1, 1, 1 ) );
    gl::enableAlphaBlending();
    
    generator_.seed(randInt());
    app::setWindowSize(600, 200);
    mean_ = getWindowWidth() / 2;
}