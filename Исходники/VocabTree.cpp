double VocabTree::AddImageToDatabase(
    int index, int ndescriptors, uint8_t *descriptors, unsigned long *ids) {
  map<unsigned long, float> node_scores;

  unsigned long off = 0;

  printf("[AddImageToDatabase] Adding image with %d features...\n",
      ndescriptors);
  fflush(stdout);

  for (int i = 0; i < ndescriptors; i++) {
    unsigned long id = m_root->PushAndScoreFeature(
        descriptors + off, index, m_branch_factor, m_dim, true /*add*/,
        node_scores);

    if (ids != NULL) {
      ids[i] = id;
    }

    off += m_dim;
    fflush(stdout);
  }

  double mag = m_root->ComputeDatabaseVectorMagnitude(
      m_branch_factor, m_distance_type, node_scores);

  m_database_images++;

  switch (m_distance_type) {
    case DistanceDot:
      return sqrt(mag);
    case DistanceMin:
      return mag;
    default:
      printf("[VocabTree::AddImageToDatabase] No case value found!\n");
      return 0.0;
  }
}