void TileScene::drawBackground(QPainter *painter, const QRectF &exposed)
{
    // Draws all tiles that intersect the exposed area.
    for (int y = 0; y < numTilesV; ++y) {
        for (int x = 0; x < numTilesH; ++x) {
            QRectF rect = rectForTile(x, y);
            if (exposed.intersects(rect))
                painter->drawPixmap(rect.topLeft(), tiles[y][x]);
        }
    }
}