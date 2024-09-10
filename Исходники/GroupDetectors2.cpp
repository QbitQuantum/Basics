/**
*  Move the user selected spectra in the input workspace into groups in the output workspace
*  @param inputWS :: user selected input workspace for the algorithm
*  @param outputWS :: user selected output workspace for the algorithm
*  @param prog4Copy :: the amount of algorithm progress to attribute to moving a single spectra
*  @return number of new grouped spectra
*/
size_t GroupDetectors2::formGroups( API::MatrixWorkspace_const_sptr inputWS, API::MatrixWorkspace_sptr outputWS, 
            const double prog4Copy)
{
  // get "Behaviour" string
  const std::string behaviour = getProperty("Behaviour");
  int bhv = 0;
  if ( behaviour == "Average" ) bhv = 1;

  API::MatrixWorkspace_sptr beh = API::WorkspaceFactory::Instance().create(
    "Workspace2D", static_cast<int>(m_GroupSpecInds.size()), 1, 1);

  g_log.debug() << name() << ": Preparing to group spectra into " << m_GroupSpecInds.size() << " groups\n";

  // where we are copying spectra to, we start copying to the start of the output workspace
  size_t outIndex = 0;
  // Only used for averaging behaviour. We may have a 1:1 map where a Divide would be waste as it would be just dividing by 1
  bool requireDivide(false);
  for ( storage_map::const_iterator it = m_GroupSpecInds.begin(); it != m_GroupSpecInds.end() ; ++it )
  {
    // This is the grouped spectrum
    ISpectrum * outSpec = outputWS->getSpectrum(outIndex);

    // The spectrum number of the group is the key
    outSpec->setSpectrumNo(it->first);
    // Start fresh with no detector IDs
    outSpec->clearDetectorIDs();

    // Copy over X data from first spectrum, the bin boundaries for all spectra are assumed to be the same here
    outSpec->dataX() = inputWS->readX(0);

    // the Y values and errors from spectra being grouped are combined in the output spectrum
    // Keep track of number of detectors required for masking
    size_t nonMaskedSpectra(0);
    beh->dataX(outIndex)[0] = 0.0;
    beh->dataE(outIndex)[0] = 0.0;
    for( std::vector<size_t>::const_iterator wsIter = it->second.begin(); wsIter != it->second.end(); ++wsIter)
    {
      const size_t originalWI = *wsIter;

      // detectors to add to firstSpecNum
      const ISpectrum * fromSpectrum = inputWS->getSpectrum(originalWI);

      // Add up all the Y spectra and store the result in the first one
      // Need to keep the next 3 lines inside loop for now until ManagedWorkspace mru-list works properly
      MantidVec &firstY = outSpec->dataY();
      MantidVec::iterator fYit;
      MantidVec::iterator fEit = outSpec->dataE().begin();
      MantidVec::const_iterator Yit = fromSpectrum->dataY().begin();
      MantidVec::const_iterator Eit = fromSpectrum->dataE().begin();
      for (fYit = firstY.begin(); fYit != firstY.end(); ++fYit, ++fEit, ++Yit, ++Eit)
      {
        *fYit += *Yit;
        // Assume 'normal' (i.e. Gaussian) combination of errors
        *fEit = std::sqrt( (*fEit)*(*fEit) + (*Eit)*(*Eit) );
      }

      // detectors to add to the output spectrum
      outSpec->addDetectorIDs(fromSpectrum->getDetectorIDs() );
      try
      {
        Geometry::IDetector_const_sptr det = inputWS->getDetector(originalWI);
        if( !det->isMasked() ) ++nonMaskedSpectra;
      }
      catch(Exception::NotFoundError&)
      {
        // If a detector cannot be found, it cannot be masked
        ++nonMaskedSpectra;
      }
    }
    if( nonMaskedSpectra == 0 ) ++nonMaskedSpectra; // Avoid possible divide by zero
    if(!requireDivide) requireDivide = (nonMaskedSpectra > 1);
    beh->dataY(outIndex)[0] = static_cast<double>(nonMaskedSpectra);

    // make regular progress reports and check for cancelling the algorithm
    if ( outIndex % INTERVAL == 0 )
    {
      m_FracCompl += INTERVAL*prog4Copy;
      if ( m_FracCompl > 1.0 )
        m_FracCompl = 1.0;
      progress(m_FracCompl);
      interruption_point();
    }
    outIndex ++;
  }
  
  // Refresh the spectraDetectorMap
  outputWS->generateSpectraMap();

  if ( bhv == 1 && requireDivide )
  {
    g_log.debug() << "Running Divide algorithm to perform averaging.\n";
    Mantid::API::IAlgorithm_sptr divide = createChildAlgorithm("Divide");
    divide->initialize();
    divide->setProperty<API::MatrixWorkspace_sptr>("LHSWorkspace", outputWS);
    divide->setProperty<API::MatrixWorkspace_sptr>("RHSWorkspace", beh);
    divide->setProperty<API::MatrixWorkspace_sptr>("OutputWorkspace", outputWS);
    divide->execute();
  }

  g_log.debug() << name() << " created " << outIndex << " new grouped spectra\n";
  return outIndex;
}