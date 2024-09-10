void CollectionMapBridge::onCollectionsLoaded(std::vector<Collection> collections, bool /*ok*/)
{
  qDebug() << "Loaded" << collections.size() << "collections";

  // clear deleted collections on map
  if (delegatedMap == nullptr) {
    displayedCollection.clear();
  }else{
    QMap<qint64, DisplayedCollection> collectionToHide = displayedCollection;

    for (const auto &c: collections){
      if (c.visible){
        collectionToHide.remove(c.id);
        collectionDetailRequest(c);
      }
    }

    for (const auto &colId: collectionToHide.keys()) {
      DisplayedCollection col=displayedCollection.take(colId);
      for (const auto &wpt: col.waypoints) {
        delegatedMap->removeOverlayObject(wpt.id);
      }
      for (const auto &trk:col.tracks){
        for (const auto &id:trk.ids){
          delegatedMap->removeOverlayObject(id);
        }
      }
    }
  }
}