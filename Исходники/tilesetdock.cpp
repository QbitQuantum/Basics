/**
 * Synchronizes the selection with the given stamp. Ignored when the stamp is
 * changing because of a selection change in the TilesetDock.
 */
void TilesetDock::selectTilesInStamp(const TileStamp &stamp)
{
    if (mEmittingStampCaptured)
        return;

    QSet<Tile*> processed;
    QMap<QItemSelectionModel*, QItemSelection> selections;

    for (const TileStampVariation &variation : stamp.variations()) {
        const TileLayer &tileLayer = *variation.tileLayer();
        for (const Cell &cell : tileLayer) {
            if (Tile *tile = cell.tile) {
                if (processed.contains(tile))
                    continue;

                processed.insert(tile); // avoid spending time on duplicates

                Tileset *tileset = tile->tileset();
                int tilesetIndex = mTilesets.indexOf(tileset->sharedPointer());
                if (tilesetIndex != -1) {
                    TilesetView *view = tilesetViewAt(tilesetIndex);
                    if (!view->model()) // Lazily set up the model
                        setupTilesetModel(view, tileset);

                    const TilesetModel *model = view->tilesetModel();
                    const QModelIndex modelIndex = model->tileIndex(tile);
                    QItemSelectionModel *selectionModel = view->selectionModel();
                    selections[selectionModel].select(modelIndex, modelIndex);
                }
            }
        }
    }

    if (!selections.isEmpty()) {
        mSynchronizingSelection = true;

        // Mark captured tiles as selected
        for (auto i = selections.constBegin(); i != selections.constEnd(); ++i) {
            QItemSelectionModel *selectionModel = i.key();
            const QItemSelection &selection = i.value();
            selectionModel->select(selection, QItemSelectionModel::SelectCurrent);
        }

        // Show/edit properties of all captured tiles
        mMapDocument->setSelectedTiles(processed.toList());

        // Update the current tile (useful for animation and collision editors)
        auto first = selections.begin();
        QItemSelectionModel *selectionModel = first.key();
        const QItemSelection &selection = first.value();
        const QModelIndex currentIndex = selection.first().topLeft();
        if (selectionModel->currentIndex() != currentIndex)
            selectionModel->setCurrentIndex(currentIndex, QItemSelectionModel::NoUpdate);
        else
            currentChanged(currentIndex);

        mSynchronizingSelection = false;
    }
}