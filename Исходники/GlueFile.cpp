bool GlueFile::AddItem(const std::string& filename)
{
  AMJU_CALL_STACK;

  string lowname = ToLower(filename);

  // Convert \ to /
  // So we can add files in subdirs in DOS, which uses "\", and use "/" to 
  //  retrieve the subdirs 
  lowname = Replace(lowname, "\\", "/"); 

  // Check for sub-file already existing.
  if (m_table.find(lowname) != m_table.end())
  {
    // Sub-file already exists
    std::string s = "GLUE FILE: file already exists in glue file: ";
    s += filename;
    ReportError(s);
    return false;
  }

  // Stick the contents of the file onto the end of the final sub-file.
  // Then update the number of files, the table position, and
  // rewrite the table.
  
  // Get the new sub-file size.
  struct stat buf;  
  if (stat(filename.c_str(), &buf) != 0)
  {
    // Couldn't get info for the sub-file. 
    std::string s = "GLUE FILE: failed to stat file: ";
    s += filename;
    ReportError(s);
    return false;
  }

  uint32 subfilesize = buf.st_size;

  // Open the new sub-file for reading.
  ifstream subfile;
  subfile.open(filename.c_str(), ios::in | ios::binary);
  if (!subfile.is_open())
  {
    std::string s = "GLUE FILE: failed to open file for reading: ";
    s += filename;
    ReportError(s);
    return false;
  }

  // Work out where the new sub-file should go in the GlueFile.
  // It's the position of the final sub-file plus its size.
  uint32 newpos = BASE;
  FileList::reverse_iterator rit = m_filenames.rbegin();
  if (rit != m_filenames.rend())
  {
    string last = *rit;
    uint32 lastsize = (m_table[last]).first;
    uint32 lastpos = (m_table[last]).second;
    newpos = lastpos + lastsize;
  } 
  // Seek to the new position.
  m_gluefile.seekg(newpos);

  // Write the new sub-file to the GlueFile.
#ifdef GLUE_FILE_DEBUG
std::cout << "GLUE FILE: Writing file " << filename.c_str() << " starting at pos: " << newpos << " size: " << subfilesize << "\n";
#endif
  unsigned char* filebuf = new unsigned char[subfilesize];
  subfile.read((char*)filebuf, subfilesize);
  m_gluefile.write((char*)filebuf, subfilesize);
  delete [] filebuf;

  // Add the new sub-file to the table.
  m_table[lowname] = make_pair(subfilesize, newpos);
  // This reorders m_table, so we also maintain a list of the files
  // in the order in which they were added to the glue file.
  m_filenames.push_back(lowname);

  // New table position
  m_tablePos += subfilesize;

  // Rewrite the table.
  WriteTable();

  return true;
}