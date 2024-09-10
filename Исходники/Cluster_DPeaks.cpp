// -----------------------------------------------------------------------------
int Cluster_DPeaks::Cluster_GaussianKernel() {
  mprintf("\tStarting DPeaks clustering. Using Gaussian kernel to calculate density.\n");
  // First determine which frames are being clustered.
  Points_.clear();
  int oidx = 0;
  for (int frame = 0; frame < (int)FrameDistances_.Nframes(); ++frame)
    if (!FrameDistances_.IgnoringRow( frame ))
      Points_.push_back( Cpoint(frame, oidx++) );
  // Sanity check.
  if (Points_.size() < 2) {
    mprinterr("Error: Only 1 frame in initial clustering.\n");
    return 1;
  }

  // Sort distances
  std::vector<float> Distances;
  for (ClusterMatrix::const_iterator mat = FrameDistances_.begin();
                                     mat != FrameDistances_.end(); ++mat)
    Distances.push_back( *mat );
  std::sort( Distances.begin(), Distances.end() );
  unsigned int idx = (unsigned int)((double)Distances.size() * 0.02);
  double bandwidth = (double)Distances[idx];
  mprintf("idx= %u, bandwidth= %g\n", idx, bandwidth);

  // Density via Gaussian kernel
  double maxDist = -1.0;
  for (unsigned int i = 0; i != Points_.size(); i++) {
    for (unsigned int j = i+1; j != Points_.size(); j++) {
      double dist = FrameDistances_.GetFdist(Points_[i].Fnum(), Points_[j].Fnum());
      maxDist = std::max( maxDist, dist );
      dist /= bandwidth;
      double gk = exp(-(dist *dist));
      Points_[i].AddDensity( gk );
      Points_[j].AddDensity( gk );
    }
  }
  mprintf("Max dist= %g\n", maxDist);
  CpptrajFile rhoOut;
  rhoOut.OpenWrite("rho.dat");
  for (unsigned int i = 0; i != Points_.size(); i++)
    rhoOut.Printf("%u %g\n", i+1, Points_[i].Density());
  rhoOut.CloseFile();
  
  // Sort by density, descending
  std::stable_sort( Points_.begin(), Points_.end(), Cpoint::density_sort_descend() );
  CpptrajFile ordrhoOut;
  ordrhoOut.OpenWrite("ordrho.dat");
  for (unsigned int i = 0; i != Points_.size(); i++)
    ordrhoOut.Printf("%u %g %i %i\n", i+1, Points_[i].Density(), Points_[i].Fnum()+1,
                     Points_[i].Oidx()+1);
  ordrhoOut.CloseFile();

  // Determine minimum distances
  int first_idx = Points_[0].Oidx();
  Points_[first_idx].SetDist( -1.0 );
  Points_[first_idx].SetNearestIdx(-1);
  for (unsigned int ii = 1; ii != Points_.size(); ii++) {
    int ord_i = Points_[ii].Oidx();
    Points_[ord_i].SetDist( maxDist );
    for (unsigned int jj = 0; jj != ii; jj++) {
      int ord_j = Points_[jj].Oidx();
      double dist = FrameDistances_.GetFdist(Points_[ord_i].Fnum(), Points_[ord_j].Fnum());
      if (dist < Points_[ord_i].Dist()) {
        Points_[ord_i].SetDist( dist );
        Points_[ord_j].SetNearestIdx( ord_j );
      }
    }
  }
  if (!dvdfile_.empty()) {
    CpptrajFile output;
    if (output.OpenWrite(dvdfile_)) return 1;
    for (Carray::const_iterator point = Points_.begin(); point != Points_.end(); ++point)
      output.Printf("%g %g %i\n", point->Density(), point->Dist(), point->NearestIdx()+1);
    output.CloseFile();
  }
      
  return 0;
}