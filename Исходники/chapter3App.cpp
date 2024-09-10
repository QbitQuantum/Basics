void chapter3App::keyDown( KeyEvent event )
{
    if (event.getChar() == '1' )
    {
        mDrawImage = !mDrawImage;
    }
    else if( event.getChar() == '2' )
    {
        mDrawParticles = !mDrawParticles;
    }
    else if( event.getCode() == KeyEvent::KEY_RIGHT )
    {
        console() << " well key r pushed too fecker " << std::endl;
        Color myColor( 1.0f, 0.5f, 0.25f);
        console() << " here is the col " << myColor << std::endl;
    }
}