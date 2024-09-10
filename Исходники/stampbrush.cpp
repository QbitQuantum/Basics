void StampBrush::drawPreviewLayer(const QVector<QPoint> &points)
{
    mPreviewMap.clear();

    if (mStamp.isEmpty() && !mIsWangFill)
        return;

    if (mIsRandom) {
        if (mRandomCellPicker.isEmpty())
            return;

        QRect bounds;
        for (const QPoint &p : points)
            bounds |= QRect(p, p);

        SharedMap preview = SharedMap::create(mapDocument()->map()->orientation(),
                                              bounds.size(),
                                              mapDocument()->map()->tileSize());

        std::unique_ptr<TileLayer> previewLayer {
            new TileLayer(QString(), bounds.topLeft(), bounds.size())
        };

        for (const QPoint &p : points) {
            const Cell &cell = mRandomCellPicker.pick();
            previewLayer->setCell(p.x() - bounds.left(),
                                  p.y() - bounds.top(),
                                  cell);
        }

        preview->addLayer(previewLayer.release());
        preview->addTilesets(preview->usedTilesets());
        mPreviewMap = preview;
    } else if (mIsWangFill) {
        if (!mWangSet)
            return;

        const TileLayer *tileLayer = currentTileLayer();
        if (!tileLayer)
            return;

        QRegion paintedRegion;
        for (const QPoint &p : points)
            paintedRegion += QRect(p, p);

        const QRect bounds = paintedRegion.boundingRect();
        SharedMap preview = SharedMap::create(mapDocument()->map()->orientation(),
                                              bounds.size(),
                                              mapDocument()->map()->tileSize());

        std::unique_ptr<TileLayer> previewLayer {
            new TileLayer(QString(), bounds.topLeft(), bounds.size())
        };

        WangFiller wangFiller(mWangSet,
                              dynamic_cast<StaggeredRenderer *>(mapDocument()->renderer()),
                              mapDocument()->map()->staggerAxis());

        for (const QPoint &p : points) {
            Cell cell = wangFiller.findFittingCell(*tileLayer,
                                                   *previewLayer,
                                                   paintedRegion,
                                                   p);

            previewLayer->setCell(p.x() - bounds.left(),
                                  p.y() - bounds.top(),
                                  cell);
        }

        preview->addLayer(previewLayer.release());
        preview->addTileset(mWangSet->tileset()->sharedPointer());
        mPreviewMap = preview;
    } else {
        QRegion paintedRegion;
        QVector<PaintOperation> operations;
        QHash<const Map *, QRegion> regionCache;
        QHash<const Map *, Map *> shiftedCopies;

        for (const QPoint &p : points) {
            Map *map = mStamp.randomVariation().map;
            mapDocument()->unifyTilesets(map, mMissingTilesets);

            Map::StaggerAxis mapStaggerAxis = mapDocument()->map()->staggerAxis();

            // if staggered map, makes sure stamp stays the same
            if (mapDocument()->map()->isStaggered()
                    && ((mapStaggerAxis == Map::StaggerY) ? map->height() > 1 : map->width() > 1)) {

                Map::StaggerIndex mapStaggerIndex = mapDocument()->map()->staggerIndex();
                Map::StaggerIndex stampStaggerIndex = map->staggerIndex();

                if (mapStaggerAxis == Map::StaggerY) {
                    bool topIsOdd = (p.y() - map->height() / 2) & 1;

                    if ((stampStaggerIndex == mapStaggerIndex) == topIsOdd) {
                        Map *shiftedMap = shiftedCopies.value(map);
                        if (!shiftedMap) {
                            shiftedMap = new Map(*map);
                            shiftedCopies.insert(map, shiftedMap);

                            LayerIterator it(shiftedMap, Layer::TileLayerType);
                            while (auto tileLayer = static_cast<TileLayer*>(it.next()))
                                shiftRows(tileLayer, stampStaggerIndex);
                        }
                        map = shiftedMap;
                    }
                } else {
                    bool leftIsOdd = (p.x() - map->width() / 2) & 1;

                    if ((stampStaggerIndex == mapStaggerIndex) == leftIsOdd) {
                        Map *shiftedMap = shiftedCopies.value(map);
                        if (!shiftedMap) {
                            shiftedMap = new Map(*map);
                            shiftedCopies.insert(map, shiftedMap);

                            LayerIterator it(shiftedMap, Layer::TileLayerType);
                            while (auto tileLayer = static_cast<TileLayer*>(it.next()))
                                shiftColumns(tileLayer, stampStaggerIndex);
                        }
                        map = shiftedMap;
                    }
                }
            }

            QRegion stampRegion;
            if (regionCache.contains(map)) {
                stampRegion = regionCache.value(map);
            } else {
                stampRegion = map->tileRegion();
                regionCache.insert(map, stampRegion);
            }

            QPoint centered(p.x() - map->width() / 2,
                            p.y() - map->height() / 2);

            const QRegion region = stampRegion.translated(centered.x(),
                                                          centered.y());
            if (!paintedRegion.intersects(region)) {
                paintedRegion += region;

                PaintOperation op = { centered, map };
                operations.append(op);
            }
        }

        const QRect bounds = paintedRegion.boundingRect();
        SharedMap preview = SharedMap::create(mapDocument()->map()->orientation(),
                                              bounds.size(),
                                              mapDocument()->map()->tileSize());

        for (const PaintOperation &op : operations) {
            LayerIterator layerIterator(op.stamp, Layer::TileLayerType);
            while (auto tileLayer = static_cast<TileLayer*>(layerIterator.next())) {
                TileLayer *target = findTileLayerByName(*preview, tileLayer->name());
                if (!target) {
                    target = new TileLayer(tileLayer->name(), bounds.topLeft(), bounds.size());
                    preview->addLayer(target);
                }
                target->merge(op.pos - bounds.topLeft() + tileLayer->position(), tileLayer);
            }
        }

        qDeleteAll(shiftedCopies);

        preview->addTilesets(preview->usedTilesets());
        mPreviewMap = preview;
    }
}