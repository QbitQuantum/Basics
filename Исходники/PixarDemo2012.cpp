void PixarDemo2012::keyDown( KeyEvent event )
{
    if ( event.getChar() == 'u' ) drawScreenUV = !drawScreenUV;
    if ( event.getChar() == 'm' ) drawMindField = !drawMindField;
    if ( event.getChar() == 'c' ) drawCairoFBO = !drawCairoFBO;
    if ( event.getChar() == 'f' ) drawFFT = !drawFFT;
    if ( event.getChar() == 't' ) drawFPS = !drawFPS;
    if ( event.getChar() == 'v' ) drawCubes = !drawCubes;
    if ( event.getChar() == 'b' ) drawCloth = !drawCloth;
    if ( event.getChar() == 'x' ) mFullScreen = !mFullScreen;
    if ( event.getChar() == 's' ) bindShaders();
    if ( event.getChar() == 'n' ) {
        doFade = true;
        printf("%f\n",mTime);
    }

}