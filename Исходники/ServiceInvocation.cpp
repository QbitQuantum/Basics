/** A convenience function that creates the callback,
 *  collects results, and makes them available in the
 *  return argument.
 */
ResultSet cvac::detect(
                    const std::string& algorithm,
                    const cvac::RunSet& runset,
                    const cvac::FilePath& model,
                    const cvac::DetectorProperties* detprops )
{
  // Connect to detector
  Ice::Identity det_cb;
  CallbackHandlerI *cr = new CallbackHandlerI();
  DetectorPrx detector = initIceConnection( algorithm, det_cb, cr );
  if(NULL == detector.get())
  {
    localAndClientMsg( VLogger::ERROR, NULL, "Could not connect to CVAC Ice Services" );
    return ResultSet();
  }
  cvac::DetectorProperties dprops;
  // If user did not supply any detector properties then provide default one.
  if (NULL == detprops)
  {
      // need to initialize detector properties to their defaults
      dprops = detector->getDetectorProperties();   
      detprops = &dprops;
  }

  try
    {	
      detector->process(det_cb, runset, model, *detprops);
    }
  catch (const Ice::Exception& ex)
    {
      throw ex;
    }

  iceComm->shutdown();  // Shut down at the end of either branch
  return cr->rs;
}