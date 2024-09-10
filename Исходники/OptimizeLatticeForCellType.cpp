/**
  @param  inname       Name of workspace containing peaks
  @param  params       optimized cell parameters
  @param  out          residuals from optimization
*/
void OptimizeLatticeForCellType::optLattice(std::string inname,
                                            std::vector<double> &params,
                                            double *out) {
  PeaksWorkspace_sptr ws = boost::dynamic_pointer_cast<PeaksWorkspace>(
      AnalysisDataService::Instance().retrieve(inname));
  const std::vector<Peak> &peaks = ws->getPeaks();
  size_t n_peaks = ws->getNumberPeaks();
  std::vector<V3D> q_vector;
  std::vector<V3D> hkl_vector;

  for (size_t i = 0; i < params.size(); i++)
    params[i] = std::abs(params[i]);
  for (size_t i = 0; i < n_peaks; i++) {
    q_vector.push_back(peaks[i].getQSampleFrame());
    hkl_vector.push_back(peaks[i].getHKL());
  }

  Mantid::API::IAlgorithm_sptr alg = createChildAlgorithm("CalculateUMatrix");
  alg->setPropertyValue("PeaksWorkspace", inname);
  alg->setProperty("a", params[0]);
  alg->setProperty("b", params[1]);
  alg->setProperty("c", params[2]);
  alg->setProperty("alpha", params[3]);
  alg->setProperty("beta", params[4]);
  alg->setProperty("gamma", params[5]);
  alg->executeAsChildAlg();

  ws = alg->getProperty("PeaksWorkspace");
  OrientedLattice latt = ws->mutableSample().getOrientedLattice();
  DblMatrix UB = latt.getUB();
  DblMatrix A = aMatrix(params);
  DblMatrix Bc = A;
  Bc.Invert();
  DblMatrix U1_B1 = UB * A;
  OrientedLattice o_lattice;
  o_lattice.setUB(U1_B1);
  DblMatrix U1 = o_lattice.getU();
  DblMatrix U1_Bc = U1 * Bc;

  for (size_t i = 0; i < hkl_vector.size(); i++) {
    V3D error = U1_Bc * hkl_vector[i] - q_vector[i] / (2.0 * M_PI);
    out[i] = error.norm2();
  }

  return;
}