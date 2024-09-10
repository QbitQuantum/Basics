/**
 * Setup output workspace
 * @param inputWorkspace: the input workspace
 * @returns a copy of the input workspace
 */
MatrixWorkspace_sptr TOFSANSResolutionByPixel::setupOutputWorkspace(
    MatrixWorkspace_sptr inputWorkspace) {
  IAlgorithm_sptr duplicate = createChildAlgorithm("CloneWorkspace");
  duplicate->initialize();
  duplicate->setProperty<Workspace_sptr>("InputWorkspace", inputWorkspace);
  duplicate->execute();
  Workspace_sptr temp = duplicate->getProperty("OutputWorkspace");
  return boost::dynamic_pointer_cast<MatrixWorkspace>(temp);
}