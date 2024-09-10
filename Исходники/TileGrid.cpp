void TileGrid::setNeedsDisplay()
{
    for (auto& entry : m_tiles) {
        TileInfo& tileInfo = entry.value;
        IntRect tileRect = rectForTileIndex(entry.key);

        if (tileRect.intersects(m_primaryTileCoverageRect) && tileInfo.layer->superlayer())
            tileInfo.layer->setNeedsDisplay();
        else
            tileInfo.hasStaleContent = true;
    }
}