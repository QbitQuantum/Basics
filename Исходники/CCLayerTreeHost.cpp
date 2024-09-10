PassOwnPtr<CCLayerTreeHost> CCLayerTreeHost::create(CCLayerTreeHostClient* client, const CCSettings& settings)
{
    OwnPtr<CCLayerTreeHost> layerTreeHost = adoptPtr(new CCLayerTreeHost(client, settings));
    if (!layerTreeHost->initialize())
        return nullptr;
    return layerTreeHost.release();
}