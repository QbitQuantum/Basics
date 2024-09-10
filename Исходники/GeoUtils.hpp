  static void visitTileRange(const BoundingBox &bbox, int levelOfDetail, const Visitor &visitor) {
    if (!bbox.isValid()) return;

    QuadKey start = GeoCoordinateToQuadKey(bbox.minPoint, levelOfDetail);
    QuadKey end = GeoCoordinateToQuadKey(bbox.maxPoint, levelOfDetail);

    for (int y = end.tileY; y < start.tileY + 1; y++) {
      for (int x = start.tileX; x < end.tileX + 1; x++) {
        const QuadKey currentQuadKey = {levelOfDetail, x, y};
        const BoundingBox currentBbox = quadKeyToBoundingBox(currentQuadKey);
        if (bbox.intersects(currentBbox)) {
          visitor(currentQuadKey, currentBbox);
        }
      }
    }
  }