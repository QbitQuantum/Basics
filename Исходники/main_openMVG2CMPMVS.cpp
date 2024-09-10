int main(int argc, char *argv[]) {

  CmdLine cmd;
  std::string sSfMDir;
  std::string sOutDir = "";

  cmd.add( make_option('i', sSfMDir, "sfmdir") );
  cmd.add( make_option('o', sOutDir, "outdir") );

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch(const std::string& s) {
      std::cerr << "Usage: " << argv[0] << ' '
      << "[-i|--sfmdir path, the SfM_output path] "
      << "[-o|--outdir path] "
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  // Create output dir
  if (!stlplus::folder_exists(sOutDir))
    stlplus::folder_create( sOutDir );
  
  Document m_doc;
  if (m_doc.load(sSfMDir))
  {
    exportToCMPMVSFormat(m_doc,
      stlplus::folder_append_separator(sOutDir) + "CMPMVS",
      stlplus::folder_append_separator(sSfMDir) + "images");

    return( EXIT_SUCCESS );
  }

  // Exit program
  return( EXIT_FAILURE );
}