  void DataTileCache::ResolveWaysFromParent(Tile& tile,
                                             const Tile& parentTile,
                                             const GeoBox& boundingBox,
                                             const TypeInfoSet& wayTypes)
  {
    if (wayTypes.Intersects(parentTile.GetWayData().GetTypes())) {
      TypeInfoSet subset(wayTypes);

      subset.Intersection(parentTile.GetWayData().GetTypes());

      std::vector<WayRef> data;

      data.reserve(parentTile.GetWayData().GetDataSize());

      parentTile.GetWayData().CopyData([&](const WayRef& way) {
        if (wayTypes.IsSet(way->GetType())) {
          GeoBox wayBoundingBox;

          way->GetBoundingBox(wayBoundingBox);

          if (wayBoundingBox.Intersects(boundingBox)) {
            data.push_back(way);
          }
        }
      });

      tile.GetWayData().SetPrefillData(subset,
                                       data);
    }
  }