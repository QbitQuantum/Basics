QList<QSharedPointer<QGeoTileTexture> > QGeoTileRequestManagerPrivate::requestTiles(const QSet<QGeoTileSpec> &tiles)
{
    QSet<QGeoTileSpec> cancelTiles = requested_ - tiles;
    QSet<QGeoTileSpec> requestTiles = tiles - requested_;
    QSet<QGeoTileSpec> cached;
//    int tileSize = tiles.size();
//    int newTiles = requestTiles.size();

    typedef QSet<QGeoTileSpec>::const_iterator iter;

    QList<QSharedPointer<QGeoTileTexture> > cachedTex;

    QGeoTiledMappingManagerEngine *engine = map_ ?
                static_cast<QGeoTiledMappingManagerEngine *>(map_->engine()) : 0;

    // remove tiles in cache from request tiles
    if (engine) {
        iter i = requestTiles.constBegin();
        iter end = requestTiles.constEnd();
        for (; i != end; ++i) {
            QGeoTileSpec tile = *i;
            QSharedPointer<QGeoTileTexture> tex = engine->getTileTexture(tile);
            if (tex) {
                cachedTex << tex;
                cached.insert(tile);
            }
        }
    }

    requestTiles -= cached;

    requested_ -= cancelTiles;
    requested_ += requestTiles;

//    qDebug() << "required # tiles: " << tileSize << ", new tiles: " << newTiles << ", total server requests: " << requested_.size();

    if (!requestTiles.isEmpty() || !cancelTiles.isEmpty()) {
        if (engine) {
//            qDebug() << "new server requests: " << requestTiles.size() << ", server cancels: " << cancelTiles.size();
            engine->updateTileRequests(map_, requestTiles, cancelTiles);

            // Remove any cancelled tiles from the error retry hash to avoid
            // re-using the numbers for a totally different request cycle.
            iter i = cancelTiles.constBegin();
            iter end = cancelTiles.constEnd();
            for (; i != end; ++i) {
                retries_.remove(*i);
                futures_.remove(*i);
            }
        }
    }

    return cachedTex;
}