/**
  * Destructor. Removes the temporary file.
  */
DetXMLFile::~DetXMLFile()
{
    if (m_delete)
    {
      QDir dir;
      dir.remove(m_fileName);
    }
}