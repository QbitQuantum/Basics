size_t GetFileList(const std::string &filePattern, std::vector<std::string> &files, int *start=0, int *end=0)
{
  size_t p0 = filePattern.find_last_of("\\/");
  
  std::string dirname = (p0 == std::string::npos ? "." : filePattern.substr(0, p0));
  std::string basename = (p0 == std::string::npos ? filePattern : filePattern.substr(p0 + 1));
  
  files.clear();
  
  p0 = basename.find('%');
  
  size_t p1 = std::string::npos;
  
  if (p0 != std::string::npos)
  {
    p1 = basename.find('d', p0);
    
    if (p1 != std::string::npos)
    {
      for (size_t p=p0+1; p<p1; ++p)
      {
        char c = basename[p];
        
        if (c < '0' || c > '9')
        {
          p1 = std::string::npos;
          break;
        }
      }
    }
  }
  
  if (p1 == std::string::npos)
  {
    // no frame pattern
    
    files.push_back(filePattern);
    
    if (start)
    {
      *start = -1;
    }
    if (end)
    {
      *end = -1;
    }
  }
  else
  {
    // Build maya filespec string for using with getFileList
    MString mayaSpec;
    
    mayaSpec += basename.substr(0, p0).c_str();
    mayaSpec += "*";
    mayaSpec += basename.substr(p1 + 1).c_str();
    
    p0 = dirname.find('\\');
    while (p0 != std::string::npos)
    {
      dirname[p0] = '/';
      p0 = dirname.find('\\', p0+1);
    }
    
    if (dirname[dirname.length()-1] != '/')
    {
      dirname += "/";
    }
    
    MStringArray allFiles;
    std::map<int, std::string> frameFiles;
    
    MGlobal::executeCommand("getFileList -filespec \"" + mayaSpec + "\" -folder \"" + MString(dirname.c_str()) + "\"", allFiles);
    
    int frame = -1;
    int sframe = 999999;
    int eframe = -999999;
    
    for (unsigned int i=0; i<allFiles.length(); ++i)
    {
      if (sscanf(allFiles[i].asChar(), basename.c_str(), &frame) != 1)
      {
        MGlobal::displayWarning("queryF3d: File \"" + allFiles[i] + "\" doesn't match frame pattern");
      }
      else
      {
        if (frame < sframe)
        {
          sframe = frame;
        }
        else if (frame > eframe)
        {
          eframe = frame;
        }
        frameFiles[frame] = dirname + allFiles[i].asChar();
      }
    }
    
    if (frameFiles.size() > 0)
    {
      files.resize(frameFiles.size());
      
      size_t i = 0;
      
      for (std::map<int, std::string>::iterator it = frameFiles.begin(); it != frameFiles.end(); ++it, ++i)
      {
        files[i] = it->second;
      }
    }
    else
    {
      sframe = -1;
      eframe = -1;
    }
    
    if (start)
    {
      *start = sframe;
    }
    
    if (end)
    {
      *end = eframe;
    }
  }
  
  return files.size();
}