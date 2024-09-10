void CFrmPlayer::slotPresent(const QVideoFrame &frame)
{
    if(frame.pixelFormat() != QVideoFrame::Format_BGR32)
    {
        m_Process.slotFrameConvertedToRGB32(frame);
        return;
    }
    m_VideoFrame = frame;
    update();
}