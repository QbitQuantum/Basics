void CoordinatedBackingStore::paintToTextureMapper(TextureMapper* textureMapper, const FloatRect& targetRect, const TransformationMatrix& transform, float opacity)
{
    if (m_tiles.isEmpty())
        return;
    ASSERT(!m_size.isZero());

    Vector<TextureMapperTile*> tilesToPaint;
    Vector<TextureMapperTile*> previousTilesToPaint;

    // We have to do this every time we paint, in case the opacity has changed.
    CoordinatedBackingStoreTileMap::iterator end = m_tiles.end();
    FloatRect coveredRect;
    for (CoordinatedBackingStoreTileMap::iterator it = m_tiles.begin(); it != end; ++it) {
        CoordinatedBackingStoreTile& tile = it->value;
        if (!tile.texture())
            continue;

        if (tile.scale() == m_scale) {
            tilesToPaint.append(&tile);
            coveredRect.unite(tile.rect());
            continue;
        }

        // Only show the previous tile if the opacity is high, otherwise effect looks like a bug.
        // We show the previous-scale tile anyway if it doesn't intersect with any current-scale tile.
        if (opacity < 0.95 && coveredRect.intersects(tile.rect()))
            continue;

        previousTilesToPaint.append(&tile);
    }

    // targetRect is on the contents coordinate system, so we must compare two rects on the contents coordinate system.
    // See TiledBackingStore.
    TransformationMatrix adjustedTransform = transform * adjustedTransformForRect(targetRect);

    paintTilesToTextureMapper(previousTilesToPaint, textureMapper, adjustedTransform, opacity, rect());
    paintTilesToTextureMapper(tilesToPaint, textureMapper, adjustedTransform, opacity, rect());
}