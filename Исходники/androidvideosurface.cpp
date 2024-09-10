bool AndroidVideoSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
        || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();
        return false;
    } else {
        paintLock.lock();
        m_currentFrame = frame;
        m_widget->update(m_targetRect);
        paintLock.unlock();
        return true;
    }
}