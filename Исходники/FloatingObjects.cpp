inline FloatingObjectInterval FloatingObjects::intervalForFloatingObject(FloatingObject& floatingObject)
{
    if (m_horizontalWritingMode)
        return FloatingObjectInterval(floatingObject.frameRect().pixelSnappedY(), floatingObject.frameRect().pixelSnappedMaxY(), &floatingObject);
    return FloatingObjectInterval(floatingObject.frameRect().pixelSnappedX(), floatingObject.frameRect().pixelSnappedMaxX(), &floatingObject);
}