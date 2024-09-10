  void EstimatePDDetectorResolution::retrieveInstrumentParameters()
  {
#if 0
    // Call SolidAngle to get solid angles for all detectors
    Algorithm_sptr calsolidangle = createChildAlgorithm("SolidAngle", -1, -1, true);
    calsolidangle->initialize();

    calsolidangle->setProperty("InputWorkspace", m_inputWS);

    calsolidangle->execute();
    if (!calsolidangle->isExecuted())
      throw runtime_error("Unable to run solid angle. ");

    m_solidangleWS = calsolidangle->getProperty("OutputWorkspace");
    if (!m_solidangleWS)
      throw runtime_error("Unable to get solid angle workspace from SolidAngle(). ");


    size_t numspec = m_solidangleWS->getNumberHistograms();
    for (size_t i = 0; i < numspec; ++i)
      g_log.debug() << "[DB]: " << m_solidangleWS->readY(i)[0] << "\n";
#endif

    // Calculate centre neutron velocity
    Property* cwlproperty = m_inputWS->run().getProperty("LambdaRequest");
    if (!cwlproperty)
      throw runtime_error("Unable to locate property LambdaRequest as central wavelength. ");
    TimeSeriesProperty<double>* cwltimeseries = dynamic_cast<TimeSeriesProperty<double>* >(cwlproperty);
    if (!cwltimeseries)
      throw runtime_error("LambdaReqeust is not a TimeSeriesProperty in double. ");
    if (cwltimeseries->size() != 1)
      throw runtime_error("LambdaRequest should contain 1 and only 1 entry. ");

    double centrewavelength = cwltimeseries->nthValue(0);
    string unit = cwltimeseries->units();
    if (unit.compare("Angstrom") == 0)
      centrewavelength *= 1.0E-10;
    else
      throw runtime_error("Unit is not recognized");

    m_centreVelocity = PhysicalConstants::h/PhysicalConstants::NeutronMass/centrewavelength;
    g_log.notice() << "Centre wavelength = " << centrewavelength << ", Centre neutron velocity = " << m_centreVelocity << "\n";

    // Calcualte L1 sample to source
    Instrument_const_sptr instrument = m_inputWS->getInstrument();
    V3D samplepos = instrument->getSample()->getPos();
    V3D sourcepos = instrument->getSource()->getPos();
    m_L1 = samplepos.distance(sourcepos);
    g_log.notice() << "L1 = " << m_L1 << "\n";

    return;
  }