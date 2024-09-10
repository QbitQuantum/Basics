void AwesomeSilkApp::keyDown( KeyEvent event )
{
	// send key events to Awesomium
	ph::awesomium::handleKeyDown( mWebViewPtr, event );
    if (event.getChar() == 'b'){
        //getWindow().setBorderless(!getWindow().isBorderless());
    }
}