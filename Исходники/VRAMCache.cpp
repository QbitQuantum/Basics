void VRAMCache::renderTiles(Graphic& g,
                            int tileIndex,
                            GGTileSet& tiles,
                            GGPalette& palette,
                            Graphic::TileTransferTransOption tileTransOption) {
    // Render each tile and blit to Graphic
    for (int j = 0; j < tiles.numTiles(); j++) {
        // Render tile
        Graphic tileGraphic(tiles[j],
                            palette,
                            tileTransOption);

        // Calculate position in Graphic
        int xPos = tileIndex * GGTile::width;
        int yPos = 0;

        // Clear the tiles before writing to them to avoid leaving
        // artifacts from previous contents (due to our program's
        // different concept of transparency from the hardware)
        g.fillRect(xPos, yPos, GGTile::width, GGTile::height,
                   Color(0xFF, 0xFF, 0xFF, Color::fullAlphaTransparency),
                   Graphic::noTransUpdate);

        // Blit if transparency is enabled; copy otherwise
        if (tileTransOption == Graphic::tileTrans) {
            g.blit(tileGraphic,
                   Box(xPos, yPos, 0, 0),
                   Graphic::transUpdate);
        }
        else {
            g.copy(tileGraphic,
                   Box(xPos, yPos, 0, 0),
                   Graphic::transUpdate);
        }

        // Move to next tile position
        ++tileIndex;
    }
}