// Cluster_Kmeans::ClusterResults()
void Cluster_Kmeans::ClusterResults(CpptrajFile& outfile) const {
  outfile.Printf("#Algorithm: Kmeans nclusters %i maxit %i\n", nclusters_, maxIt_);
}