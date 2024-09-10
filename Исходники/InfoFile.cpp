InfoFile::InfoFile(string id)
{
  stringstream fileName; 
  fileName << INF_FILE_NAME << "." << id; 
  fh =  openFile(fileName.str(), "w"); 
}