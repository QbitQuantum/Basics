vtkDCMParser::vtkDCMParser(const char *filename)
{
  Init();
  OpenFile(filename);
}