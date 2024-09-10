bool VideoTheoraPlayer::display(uint32 alpha) {
    Rect32 rc;
    bool res;

    if (_texture && _videoFrameReady) {
        rc.setRect(0, 0, _texture->getWidth(), _texture->getHeight());
        if (_playZoom == 100.0f) {
            res = _texture->displayTrans(_posX, _posY, rc, alpha);
        } else {
            res = _texture->displayTransZoom(_posX, _posY, rc, _playZoom, _playZoom, alpha);
        }
    } else {
        res = STATUS_FAILED;
    }
    // TODO: Add subtitles-support
    /*	if (m_Subtitler && _gameRef->m_VideoSubtitles) {
    		m_Subtitler->display();
    	}*/

    return res;
}