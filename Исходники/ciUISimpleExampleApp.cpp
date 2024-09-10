void ciUISimpleExampleApp::keyDown( KeyEvent event )
{
    if(event.getChar() == 'g')
    {
        gui->toggleVisible(); 
    }
}