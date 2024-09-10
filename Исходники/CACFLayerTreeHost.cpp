PassRefPtr<CACFLayerTreeHost> CACFLayerTreeHost::create()
{
    if (!acceleratedCompositingAvailable())
        return nullptr;
    RefPtr<CACFLayerTreeHost> host = WKCACFViewLayerTreeHost::create();
    host->initialize();
    return host.release();
}