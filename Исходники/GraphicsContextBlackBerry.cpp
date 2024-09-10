void GraphicsContext::clipOutRoundedRect(const RoundedRect& rect)
{
    if (paintingDisabled())
        return;

    BlackBerry::Platform::FloatRoundedRect r = BlackBerry::Platform::FloatRoundedRect(
        FloatRect(rect.rect()),
        FloatSize(rect.radii().topLeft()),
        FloatSize(rect.radii().topRight()),
        FloatSize(rect.radii().bottomLeft()),
        FloatSize(rect.radii().bottomRight()));
    platformContext()->clipOutRoundedRect(r);
}