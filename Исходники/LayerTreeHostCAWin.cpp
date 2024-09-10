PassRefPtr<LayerTreeHostCAWin> LayerTreeHostCAWin::create(WebPage* webPage)
{
    RefPtr<LayerTreeHostCAWin> host = adoptRef(new LayerTreeHostCAWin(webPage));
    host->initialize();
    return host.release();
}