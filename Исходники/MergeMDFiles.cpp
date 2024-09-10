/** Execute the algorithm.
 */
void MergeMDFiles::exec() {
  // clear disk buffer which can remain from previous runs
  // the existence/ usage of the buffer indicates if the algorithm works with
  // file based or memory based target workspaces;
  // pDiskBuffer = NULL;
  MultipleFileProperty *multiFileProp =
      dynamic_cast<MultipleFileProperty *>(getPointerToProperty("Filenames"));
  if (!multiFileProp) {
    throw std::logic_error(
        "Filenames property must have MultipleFileProperty type.");
  }
  m_Filenames =
      MultipleFileProperty::flattenFileNames(multiFileProp->operator()());
  if (m_Filenames.size() == 0)
    throw std::invalid_argument("Must specify at least one filename.");
  std::string firstFile = m_Filenames[0];

  std::string outputFile = getProperty("OutputFilename");
  m_fileBasedTargetWS = false;
  if (!outputFile.empty()) {
    m_fileBasedTargetWS = true;
    if (Poco::File(outputFile).exists())
      throw std::invalid_argument(
          " File " + outputFile + " already exists. Can not use existing file "
                                  "as the target to MergeMD files.\n" +
          " Use it as one of source files if you want to add MD data to it");
  }

  // Start by loading the first file but just the box structure, no events, and
  // not file-backed
  // m_BoxStruct.loadBoxStructure(firstFile,
  IAlgorithm_sptr loader = createChildAlgorithm("LoadMD", 0.0, 0.05, false);
  loader->setPropertyValue("Filename", firstFile);
  loader->setProperty("MetadataOnly", false);
  loader->setProperty("BoxStructureOnly", true);
  loader->setProperty("FileBackEnd", false);
  loader->executeAsChildAlg();
  IMDWorkspace_sptr result = (loader->getProperty("OutputWorkspace"));

  auto firstWS = boost::dynamic_pointer_cast<API::IMDEventWorkspace>(result);
  if (!firstWS)
    throw std::runtime_error(
        "Can not load MDEventWorkspace from initial file " + firstFile);

  // do the job
  this->doExecByCloning(firstWS, outputFile);

  m_OutIWS->setFileNeedsUpdating(false);

  setProperty("OutputWorkspace", m_OutIWS);
}