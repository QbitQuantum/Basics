void FolApp::keyDown(KeyEvent event)
{
    if (event.getChar() == 'f')
        setFullScreen(!isFullScreen());
    if (event.getCode() == KeyEvent::KEY_ESCAPE)
        quit();
}