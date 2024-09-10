void ThreadSafeCoordinatedSurface::paintToSurface(const IntRect& rect, CoordinatedSurface::Client* client)
{
    ASSERT(client);

    GraphicsContext* context = beginPaint(rect);
    client->paintToSurfaceContext(context);
    endPaint();
}