void LibraryModel::SongsDeleted(const SongList& songs) {
  // Delete the actual song nodes first, keeping track of each parent so we
  // might check to see if they're empty later.
  QSet<LibraryItem*> parents;
  for (const Song& song : songs) {
    if (song_nodes_.contains(song.id())) {
      LibraryItem* node = song_nodes_[song.id()];

      if (node->parent != root_) parents << node->parent;

      beginRemoveRows(ItemToIndex(node->parent), node->row, node->row);
      node->parent->Delete(node->row);
      song_nodes_.remove(song.id());
      endRemoveRows();
    } else {
      // If we get here it means some of the songs we want to delete haven't
      // been lazy-loaded yet.  This is bad, because it would mean that to
      // clean up empty parents we would need to lazy-load them all
      // individually to see if they're empty.  This can take a very long time,
      // so better to just reset the model and be done with it.
      Reset();
      return;
    }
  }

  // Now delete empty parents
  QSet<QString> divider_keys;
  while (!parents.isEmpty()) {
    // Since we are going to remove elements from the container, we
    // need a copy to iterate over. If we iterate over the original,
    // the behavior will be undefined.
    QSet<LibraryItem*> parents_copy = parents;
    for (LibraryItem* node : parents_copy) {
      parents.remove(node);
      if (node->children.count() != 0) continue;

      // Consider its parent for the next round
      if (node->parent != root_) parents << node->parent;

      // Maybe consider its divider node
      if (node->container_level == 0)
        divider_keys << DividerKey(group_by_[0], node);

      // Special case the Various Artists node
      if (IsCompilationArtistNode(node))
        node->parent->compilation_artist_node_ = nullptr;
      else
        container_nodes_[node->container_level].remove(node->key);

      // It was empty - delete it
      beginRemoveRows(ItemToIndex(node->parent), node->row, node->row);
      node->parent->Delete(node->row);
      endRemoveRows();
    }
  }

  // Delete empty dividers
  for (const QString& divider_key : divider_keys) {
    if (!divider_nodes_.contains(divider_key)) continue;

    // Look to see if there are any other items still under this divider
    bool found = false;
    for (LibraryItem* node : container_nodes_[0].values()) {
      if (DividerKey(group_by_[0], node) == divider_key) {
        found = true;
        break;
      }
    }

    if (found) continue;

    // Remove the divider
    int row = divider_nodes_[divider_key]->row;
    beginRemoveRows(ItemToIndex(root_), row, row);
    root_->Delete(row);
    endRemoveRows();
    divider_nodes_.remove(divider_key);
  }
}