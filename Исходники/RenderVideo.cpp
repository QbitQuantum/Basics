void RenderVideo::updatePlayer()
{
    MediaPlayer* mediaPlayer = player();
    if (!mediaPlayer)
        return;
    if (!mediaElement()->inActiveDocument()) {
        mediaPlayer->setVisible(false);
        return;
    }
    
    // FIXME: This doesn't work correctly with transforms.
    FloatPoint absPos = localToAbsolute();
    IntRect videoBounds = videoBox(); 
    videoBounds.move(absPos.x(), absPos.y());
    mediaPlayer->setFrameView(document()->view());
    mediaPlayer->setRect(videoBounds);
    mediaPlayer->setVisible(true);
}