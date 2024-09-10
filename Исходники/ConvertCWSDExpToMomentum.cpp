/** Set goniometer to matrix workspace and get its rotation matrix R (from
 * Q-sample to Q-lab
 * and output 1/R
 * @brief ConvertCWSDExpToMomentum::setupTransferMatrix
 * @param dataws :: matrix workspace containing sample rotation angles
 * @param rotationMatrix :: output as matrix 1/R to convert from Q-lab to
 * Q-sample
 */
void ConvertCWSDExpToMomentum::setupTransferMatrix(
    API::MatrixWorkspace_sptr dataws, Kernel::DblMatrix &rotationMatrix) {
  // Check sample logs
  if (!dataws->run().hasProperty("_omega") ||
      !dataws->run().hasProperty("_chi") || !dataws->run().hasProperty("_phi"))
    throw std::runtime_error(
        "Data workspace does not have sample log _phi, _chi or _omega. "
        "Unable to set goniometer and calcualte roation matrix R.");

  // Call algorithm SetGoniometer
  IAlgorithm_sptr setalg = createChildAlgorithm("SetGoniometer");
  setalg->initialize();
  setalg->setProperty("Workspace", dataws);
  setalg->setProperty("Axis0", "_omega,0,1,0,-1");
  setalg->setProperty("Axis1", "_chi,0,0,1,-1");
  setalg->setProperty("Axis2", "_phi,0,1,0,-1");
  setalg->execute();

  if (setalg->isExecuted()) {
    rotationMatrix = dataws->run().getGoniometer().getR();
    g_log.debug() << "Ratation matrix: " << rotationMatrix.str() << "\n";
    rotationMatrix.Invert();
    g_log.debug() << "Ratation matrix: " << rotationMatrix.str() << "\n";
  } else
    throw std::runtime_error("Unable to set Goniometer.");

  return;
}