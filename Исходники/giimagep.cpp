bool GiGdipImage::draw(GiCanvasWin& graph, const Box2d& rectW, bool fast) const
{
    bool ret = false;

    if (getWidth() > 0)
    {
        if (graph.getCanvasType() == 2)
        {
            GiCanvasGdip* gs = (GiCanvasGdip*)(&graph);
            ret = gs->drawGdipImage(
                getHmWidth(), getHmHeight(), m_impl->bmp, rectW, fast);
        }
        else
        {
            HBITMAP hBmp = createBitmap(graph.getBkColor());
            ret = graph.drawImage(getHmWidth(), getHmHeight(),
                hBmp, rectW, fast);
            ::DeleteObject(hBmp);
        }
    }

    return ret;
}