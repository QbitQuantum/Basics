// Cluster_DBSCAN::ComputeKdistMap()
void Cluster_DBSCAN::ComputeKdistMap( Range const& Kvals, 
                                      std::vector<int> const& FramesToCluster ) const
{
  int pt1_idx, pt2_idx, d_idx, point;
  mprintf("\tCalculating Kdist map for %s\n", Kvals.RangeArg());
  double* kdist_array; // Store distance of pt1 to every other point.
  int nframes = (int)FramesToCluster.size();
  // Ensure all Kdist points are within proper range
  Range::const_iterator kval;
  for (kval = Kvals.begin(); kval != Kvals.end(); ++kval)
    if (*kval < 1 || *kval >= nframes) {
      mprinterr("Error: Kdist value %i is out of range (1 <= Kdist < %i)\n",
                 *kval, nframes);
      return;
    }
  int nvals = (int)Kvals.Size();
  double** KMAP; // KMAP[i] has the ith nearest point for each point.
  KMAP = new double*[ nvals ];
  for (int i = 0; i != nvals; i++)
    KMAP[i] = new double[ nframes ];
  ParallelProgress progress( nframes );
# ifdef _OPENMP
# pragma omp parallel private(pt1_idx, pt2_idx, d_idx, kval, point, kdist_array) firstprivate(progress)
  {
  progress.SetThread( omp_get_thread_num() );
#endif
  kdist_array = new double[ nframes ];
# ifdef _OPENMP
# pragma omp for
# endif
  for (pt1_idx = 0; pt1_idx < nframes; pt1_idx++) // X
  {
    progress.Update( pt1_idx );
    point = FramesToCluster[pt1_idx];
    d_idx = 0;
    // Store distances from pt1 to pt2
    for (pt2_idx = 0; pt2_idx != nframes; pt2_idx++)
      kdist_array[d_idx++] = FrameDistances_.GetFdist(point, FramesToCluster[pt2_idx]);
    // Sort distances; will be smallest to largest
    std::sort( kdist_array, kdist_array + nframes );
    // Save the distance of specified nearest neighbors to this point.
    d_idx = 0;
    for (kval = Kvals.begin(); kval != Kvals.end(); ++kval) // Y
      KMAP[d_idx++][pt1_idx] = kdist_array[ *kval ];
  }
  delete[] kdist_array;
# ifdef _OPENMP
  } // END omp parallel
# endif
  progress.Finish();
  // Sort all of the individual kdist plots, smallest to largest.
  for (int i = 0; i != nvals; i++)
    std::sort(KMAP[i], KMAP[i] + nframes);
  // Save in matrix, largest to smallest.
  DataSet_MatrixDbl kmatrix;
  kmatrix.Allocate2D( FramesToCluster.size(), Kvals.Size() );
  for (int y = 0; y != nvals; y++) {
    for (int x = nframes - 1; x != -1; x--)
      kmatrix.AddElement( KMAP[y][x] );
    delete[] KMAP[y];
  }
  delete[] KMAP;
  // Write matrix to file
  DataFile outfile;
  ArgList outargs("usemap");
  outfile.SetupDatafile(k_prefix_ + "Kmatrix.gnu", outargs, debug_);
  outfile.AddDataSet( (DataSet*)&kmatrix );
  outfile.WriteDataOut();
  // Write out the largest and smallest values for each K.
  // This means for each value of K the point with the furthest Kth-nearest
  // neighbor etc.
  CpptrajFile maxfile;
  if (maxfile.OpenWrite(k_prefix_ + "Kmatrix.max.dat")) return;
  maxfile.Printf("%-12s %12s %12s\n", "#Kval", "MaxD", "MinD");
  d_idx = 0;
  for (kval = Kvals.begin(); kval != Kvals.end(); ++kval, d_idx++)
    maxfile.Printf("%12i %12g %12g\n", *kval, kmatrix.GetElement(0, d_idx),
                   kmatrix.GetElement(nframes-1, d_idx));
  maxfile.CloseFile();
}