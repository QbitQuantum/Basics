// setters
void
OWLDatabase::update_node(id_t id, const tags_t &attrs, const tags_t &tags) {
  // simple implementation as a delete-add. this isn't efficient, but it might not need to be.
  const int lat = nearbyint(lexical_cast<double>(required_attribute(attrs, "lat")) * SCALE);
  const int lon = nearbyint(lexical_cast<double>(required_attribute(attrs, "lon")) * SCALE);
  delete_node(id);

  stringstream query;
  query << "insert into nodes (id, version, changeset, lat, lon, tile) values ("
        << id << ", "
        << required_attribute(attrs, "version") << ", "
        << required_attribute(attrs, "changeset") << ", "
        << lat << ", " << lon << ", "
        << util::xy2tile(util::lon2x(lon), util::lat2y(lat)) << ")";
  transaction.exec(query);

  add_tags(transaction, "node_tags", id, tags);
}