int main(int argc, char **argv)
{
  Config cfg;

  try
  {
    cfg.readFile("invalid.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "File I/O error" << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }

  return(EXIT_SUCCESS);
}