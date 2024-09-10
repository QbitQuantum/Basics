bool VideoWidgetSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
            || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();

        return false;
    }
    else
    {
        currentFrame = frame;
        currentFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage image(currentFrame.bits(),
                     currentFrame.width(),
                     currentFrame.height(),
                     imageFormat);
        emit aviImage(image);
        currentFrame.unmap();
        return true;
    }
}