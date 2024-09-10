/**
 * Create a list of files from the given algorithm property.
 */
void FindFilesThread::getFilesFromAlgorithm() {
  Mantid::API::IAlgorithm_sptr algorithm =
      Mantid::API::AlgorithmManager::Instance().createUnmanaged(
          m_algorithm.toStdString());

  if (!algorithm)
    throw std::invalid_argument("Cannot create algorithm " +
                                m_algorithm.toStdString() + ".");

  algorithm->initialize();
  const std::string propName = m_property.toStdString();
  algorithm->setProperty(propName, m_text);

  Property *prop = algorithm->getProperty(propName);
  m_valueForProperty = QString::fromStdString(prop->value());

  FileProperty *fileProp = dynamic_cast<FileProperty *>(prop);
  MultipleFileProperty *multiFileProp =
      dynamic_cast<MultipleFileProperty *>(prop);

  if (fileProp) {
    m_filenames.push_back(fileProp->value());
  } else if (multiFileProp) {
    // This flattens any summed files to a set of single files so that you lose
    // the information about
    // what was summed
    std::vector<std::vector<std::string>> filenames =
        algorithm->getProperty(propName);
    std::vector<std::string> flattenedNames =
        VectorHelper::flattenVector(filenames);

    for (auto filename = flattenedNames.begin();
         filename != flattenedNames.end(); ++filename) {
      m_filenames.push_back(*filename);
    }
  }
}