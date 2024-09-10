bool RequestURI::virtualFileExists(const VirtualHost *vhost,
                                   const string &sourceRoot,
                                   const string &pathTranslation,
                                   CStrRef filename) {
  if (filename.empty() || filename.charAt(filename.length() - 1) == '/') {
    return false;
  }
  if (!vhost->getDocumentRoot().empty()) {
    string fullname = filename.data();
    if (fullname[0] == '/') {
      fullname = fullname.substr(1);
    } else {
      fullname = pathTranslation + fullname;
    }
    m_path = fullname;
    m_absolutePath = String(sourceRoot) + m_path;

    if (StaticContentCache::TheFileCache && !fullname.empty() &&
        StaticContentCache::TheFileCache->fileExists(fullname.c_str())) {
      return true;
    }

    struct stat st;
    return RuntimeOption::AllowedFiles.find(fullname.c_str()) !=
      RuntimeOption::AllowedFiles.end() ||
      (stat(m_absolutePath.c_str(), &st) == 0 &&
       (st.st_mode & S_IFMT) == S_IFREG);
  }
  m_path = filename;
  m_absolutePath = String(sourceRoot) + filename;
  return true;
}