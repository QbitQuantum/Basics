bool OsmAnd::MapRenderer::prePrepareFrame()
{
    if(!_isRenderingInitialized)
        return false;

    // If we have current configuration invalidated, we need to update it
    // and invalidate frame
    if(_currentConfigurationInvalidatedMask)
    {
        {
            QReadLocker scopedLocker(&_configurationLock);

            _currentConfiguration = _requestedConfiguration;
        }

        bool ok = updateCurrentConfiguration();
        if(ok)
            _currentConfigurationInvalidatedMask = 0;

        invalidateFrame();

        // If configuration is still invalidated, abort processing
        if(_currentConfigurationInvalidatedMask)
            return false;
    }

    // If we have current state invalidated, we need to update it
    // and invalidate frame
    if(_currentStateInvalidated)
    {
        {
            QReadLocker scopedLocker(&_stateLock);

            _currentState = _requestedState;
        }

        bool ok = updateCurrentState();
        if(ok)
            _currentStateInvalidated = false;

        invalidateFrame();

        // If state is still invalidated, abort processing
        if(_currentStateInvalidated)
            return false;
    }

    // If we have invalidated resources, purge them
    if(_invalidatedRasterLayerResourcesMask)
    {
        QReadLocker scopedLocker(&_invalidatedRasterLayerResourcesMaskLock);

        for(int layerId = 0; layerId < RasterMapLayersCount; layerId++)
        {
            if((_invalidatedRasterLayerResourcesMask & (1 << layerId)) == 0)
                continue;

            validateRasterLayerResources(static_cast<RasterMapLayerId>(layerId));

            _invalidatedRasterLayerResourcesMask &= ~(1 << layerId);
        }
    }
    if(_invalidatedElevationDataResources)
    {
        validateElevationDataResources();
        _invalidatedElevationDataResources = false;
    }

    // Sort visible tiles by distance from target
    qSort(_visibleTiles.begin(), _visibleTiles.end(), [this](const TileId& l, const TileId& r) -> bool
    {
        const auto lx = l.x - _targetTileId.x;
        const auto ly = l.y - _targetTileId.y;

        const auto rx = r.x - _targetTileId.x;
        const auto ry = r.y - _targetTileId.y;

        return (lx*lx + ly*ly) > (rx*rx + ry*ry);
    });

    // Get set of tiles that are unique: visible tiles may contain same tiles, but wrapped
    _uniqueTiles.clear();
    for(auto itTileId = _visibleTiles.begin(); itTileId != _visibleTiles.end(); ++itTileId)
    {
        const auto& tileId = *itTileId;
        _uniqueTiles.insert(Utilities::normalizeTileId(tileId, _currentState.zoomBase));
    }

    //TODO: Keep cache fresh and throw away outdated tiles

    return true;
}