void FrownLogoParticlesApp::keyDown( KeyEvent event )
{

    if ( event.getChar() == ' ')
    {
        //Pressing the spacebar causes the particles to change direction
        // in one case they are making up the word "Frown"
        // and in the other case "Frown" explodes into particles.
        
        mKeyPressed = !mKeyPressed;
    } else if ( ( event.getChar() == 'P' ) || ( event.getChar() == 'p' ) )
    {
        // Pause and "unpause" using the p ( or P ) key
        mPaused = !mPaused;
    }
}