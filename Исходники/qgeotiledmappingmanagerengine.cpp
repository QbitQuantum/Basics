void QGeoTiledMappingManagerEngine::deregisterMap(QGeoTiledMapData *map)
{
    d_ptr->tileMaps_.remove(map);
    d_ptr->mapHash_.remove(map);

    QHash<QGeoTileSpec, QSet<QGeoTiledMapData *> > newTileHash = d_ptr->tileHash_;
    typedef QHash<QGeoTileSpec, QSet<QGeoTiledMapData *> >::const_iterator h_iter;
    h_iter hi = d_ptr->tileHash_.constBegin();
    h_iter hend = d_ptr->tileHash_.constEnd();
    for (; hi != hend; ++hi) {
        QSet<QGeoTiledMapData *> maps = hi.value();
        if (maps.contains(map)) {
            maps.remove(map);
            if (maps.isEmpty())
                newTileHash.remove(hi.key());
            else
                newTileHash.insert(hi.key(), maps);
        }
    }
    d_ptr->tileHash_ = newTileHash;
}