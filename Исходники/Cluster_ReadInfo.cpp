void Cluster_ReadInfo::ClusterResults(CpptrajFile& outfile) const {
  outfile.Printf("#Algorithm: Read from file '%s'\n", filename_.c_str());
  if (!algorithm_.empty())
    outfile.Printf("#Original algorithm: %s", algorithm_.c_str());
}