/** Execute the algorithm.
 */
void LoadDNSSCD::exec() {
  MultipleFileProperty *multiFileProp =
      dynamic_cast<MultipleFileProperty *>(getPointerToProperty("Filenames"));
  if (!multiFileProp) {
    throw std::logic_error(
        "Filenames property must have MultipleFileProperty type.");
  }
  std::vector<std::string> filenames =
      VectorHelper::flattenVector(multiFileProp->operator()());
  if (filenames.empty())
    throw std::invalid_argument("Must specify at least one filename.");

  // set type of normalization
  std::string normtype = getProperty("Normalization");
  if (normtype == "monitor") {
    m_normtype = "Monitor";
    m_normfactor = 1.0;
  } else {
    m_normtype = "Timer";
    m_normfactor = 0.0; // error for time should be 0
  }

  g_log.notice() << "The normalization workspace will contain " << m_normtype
                 << ".\n";

  ExperimentInfo_sptr expinfo = boost::make_shared<ExperimentInfo>();
  API::Run &run = expinfo->mutableRun();
  for (auto fname : filenames) {
    std::map<std::string, std::string> str_metadata;
    std::map<std::string, double> num_metadata;
    try {
      read_data(fname, str_metadata, num_metadata);
      // if no stop_time, take file_save_time
      std::string time(str_metadata["stop_time"]);
      if (time.empty()) {
        g_log.warning()
            << "stop_time is empty! File save time will be used instead."
            << std::endl;
        time = str_metadata["file_save_time"];
      }
      updateProperties<std::string>(run, str_metadata, time);
      updateProperties<double>(run, num_metadata, time);
    } catch (...) {
      g_log.warning() << "Failed to read file " << fname;
      g_log.warning() << ". This file will be ignored. " << std::endl;
      g_log.debug() << boost::current_exception_diagnostic_information()
                    << std::endl;
    }
  }

  if (m_data.empty())
    throw std::runtime_error(
        "No valid DNS files have been provided. Nothing to load.");

  m_OutWS = MDEventFactory::CreateMDWorkspace(m_nDims, "MDEvent");

  m_OutWS->addExperimentInfo(expinfo);

  // load huber angles from a table workspace if given
  ITableWorkspace_sptr huberWS = getProperty("LoadHuberFrom");
  if (huberWS) {
    g_log.notice() << "Huber angles will be loaded from " << huberWS->getName()
                   << std::endl;
    loadHuber(huberWS);
  }

  // get wavelength
  TimeSeriesProperty<double> *wlprop =
      dynamic_cast<TimeSeriesProperty<double> *>(
          expinfo->run().getProperty("Lambda"));
  // assume, that lambda is in nm
  double wavelength =
      wlprop->minValue() * 10.0; // needed to estimate extents => minValue
  run.addProperty("wavelength", wavelength);
  run.getProperty("wavelength")->setUnits("Angstrom");

  fillOutputWorkspace(wavelength);

  std::string saveHuberTableWS = getProperty("SaveHuberTo");
  if (!saveHuberTableWS.empty()) {
    Mantid::API::ITableWorkspace_sptr huber_table = saveHuber();
    setProperty("SaveHuberTo", huber_table);
  }
  setProperty("OutputWorkspace", m_OutWS);
}