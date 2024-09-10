void TileLayer::setCell(int x, int y, const Cell &cell)
{
    Q_ASSERT(contains(x, y));

    if (cell.tile) {
        QSize size = cell.tile->size();

        if (cell.flippedAntiDiagonally)
            size.transpose();

        const QPoint offset = cell.tile->tileset()->tileOffset();

        mMaxTileSize = maxSize(size, mMaxTileSize);
        mOffsetMargins = maxMargins(QMargins(-offset.x(),
                                             -offset.y(),
                                             offset.x(),
                                             offset.y()),
                                    mOffsetMargins);

        if (mMap)
            mMap->adjustDrawMargins(drawMargins());
    }

    mGrid[x + y * mWidth] = cell;
}