/**
 * Groups the workspace according to grouping provided.
 *
 * @param ws :: Workspace to group
 * @param  g :: The grouping information
 * @return Sptr to created grouped workspace
 */
MatrixWorkspace_sptr groupWorkspace(MatrixWorkspace_const_sptr ws, const Grouping& g)
{
  // As I couldn't specify multiple groups for GroupDetectors, I am going down quite a complicated
  // route - for every group distinct grouped workspace is created using GroupDetectors. These
  // workspaces are then merged into the output workspace.

  // Create output workspace
  MatrixWorkspace_sptr outWs =
    WorkspaceFactory::Instance().create(ws, g.groups.size(), ws->readX(0).size(), ws->blocksize());

  for(size_t gi = 0; gi < g.groups.size(); gi++)
  {
    Mantid::API::IAlgorithm_sptr alg = AlgorithmManager::Instance().create("GroupDetectors");
    alg->setChild(true); // So Output workspace is not added to the ADS
    alg->initialize();
    alg->setProperty("InputWorkspace", boost::const_pointer_cast<MatrixWorkspace>(ws));
    alg->setPropertyValue("SpectraList", g.groups[gi]);
    alg->setPropertyValue("OutputWorkspace", "grouped"); // Is not actually used, just to make validators happy
    alg->execute();

    MatrixWorkspace_sptr grouped = alg->getProperty("OutputWorkspace");

    // Copy the spectrum
    *(outWs->getSpectrum(gi)) = *(grouped->getSpectrum(0));

    // Update spectrum number
    outWs->getSpectrum(gi)->setSpectrumNo(static_cast<specid_t>(gi));

    // Copy to the output workspace
    outWs->dataY(gi) = grouped->readY(0);
    outWs->dataX(gi) = grouped->readX(0);
    outWs->dataE(gi) = grouped->readE(0);
  }

  return outWs;
}