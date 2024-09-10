/** Add workspace2 to workspace1 by adding spectrum.
  */
MatrixWorkspace_sptr
AlignAndFocusPowder::conjoinWorkspaces(API::MatrixWorkspace_sptr ws1,
                                       API::MatrixWorkspace_sptr ws2,
                                       size_t offset) {
  // Get information from ws1: maximum spectrum number, and store original
  // spectrum Nos
  size_t nspec1 = ws1->getNumberHistograms();
  specnum_t maxspecNo1 = 0;
  std::vector<specnum_t> origspecNos;
  for (size_t i = 0; i < nspec1; ++i) {
    specnum_t tmpspecNo = ws1->getSpectrum(i).getSpectrumNo();
    origspecNos.push_back(tmpspecNo);
    if (tmpspecNo > maxspecNo1)
      maxspecNo1 = tmpspecNo;
  }

  g_log.information() << "[DBx536] Max spectrum number of ws1 = " << maxspecNo1
                      << ", Offset = " << offset << ".\n";

  size_t nspec2 = ws2->getNumberHistograms();

  // Conjoin 2 workspaces
  Algorithm_sptr alg = this->createChildAlgorithm("AppendSpectra");
  alg->initialize();
  ;

  alg->setProperty("InputWorkspace1", ws1);
  alg->setProperty("InputWorkspace2", ws2);
  alg->setProperty("OutputWorkspace", ws1);
  alg->setProperty("ValidateInputs", false);

  alg->executeAsChildAlg();

  API::MatrixWorkspace_sptr outws = alg->getProperty("OutputWorkspace");

  // FIXED : Restore the original spectrum Nos to spectra from ws1
  for (size_t i = 0; i < nspec1; ++i) {
    specnum_t tmpspecNo = outws->getSpectrum(i).getSpectrumNo();
    outws->getSpectrum(i).setSpectrumNo(origspecNos[i]);

    g_log.information() << "[DBx540] Conjoined spectrum " << i
                        << ": restore spectrum number to "
                        << outws->getSpectrum(i).getSpectrumNo()
                        << " from spectrum number = " << tmpspecNo << ".\n";
  }

  // Rename spectrum number
  if (offset >= 1) {
    for (size_t i = 0; i < nspec2; ++i) {
      specnum_t newspecid = maxspecNo1 + static_cast<specnum_t>((i) + offset);
      outws->getSpectrum(nspec1 + i).setSpectrumNo(newspecid);
      // ISpectrum* spec = outws->getSpectrum(nspec1+i);
      // if (spec)
      // spec->setSpectrumNo(3);
    }
  }

  return outws;
}