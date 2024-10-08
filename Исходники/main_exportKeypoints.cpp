int main(int argc, char ** argv)
{
  CmdLine cmd;

  std::string sImaDirectory;
  std::string sMatchesDir;
  std::string sOutDir = "";

  cmd.add( make_option('i', sImaDirectory, "imadir") );
  cmd.add( make_option('d', sMatchesDir, "matchdir") );
  cmd.add( make_option('o', sOutDir, "outdir") );

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch(const std::string& s) {
      std::cerr << "Export pairwise matches.\nUsage: " << argv[0] << "\n"
      << "[-i|--imadir path]\n"
      << "[-d|--matchdir path]\n"
      << "[-o|--outdir path]\n"
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  if (sOutDir.empty())  {
    std::cerr << "\nIt is an invalid output directory" << std::endl;
    return EXIT_FAILURE;
  }


  //---------------------------------------
  // Read images names
  //---------------------------------------

  std::vector<SfMIO::CameraInfo> vec_camImageName;
  std::vector<SfMIO::IntrinsicCameraInfo> vec_focalGroup;
  if (!SfMIO::loadImageList(
    vec_camImageName,
    vec_focalGroup,
    stlplus::create_filespec(sMatchesDir, "lists", "txt")))
  {
    std::cerr << "\nEmpty image list." << std::endl;
    return false;
  }


  // ------------
  // For each image, export visually the keypoints
  // ------------

  stlplus::folder_create(sOutDir);
  std::cout << "\n Export extracted keypoints for all images" << std::endl;
  C_Progress_display my_progress_bar( vec_camImageName.size() );
  for (std::vector<SfMIO::CameraInfo>::const_iterator iterFilename = vec_camImageName.begin();
    iterFilename != vec_camImageName.end();
    ++iterFilename, ++my_progress_bar)
  {
    const size_t I = std::distance(
      (std::vector<SfMIO::CameraInfo>::const_iterator)vec_camImageName.begin(),
      iterFilename);

    const std::pair<size_t, size_t>
      dimImage = std::make_pair(vec_focalGroup[I].m_w, vec_focalGroup[I].m_h);

    svgDrawer svgStream( dimImage.first, dimImage.second);
    svgStream.drawImage(stlplus::create_filespec(sImaDirectory,iterFilename->m_sImageName),
      dimImage.first,
      dimImage.second);

    // Load the features from the feature file
    std::vector<SIOPointFeature> vec_feat;
    loadFeatsFromFile(
      stlplus::create_filespec(sMatchesDir, stlplus::basename_part(iterFilename->m_sImageName), ".feat"),
      vec_feat);

    //-- Draw features
    for (size_t i=0; i< vec_feat.size(); ++i)  {
      const SIOPointFeature & feature = vec_feat[i];
      svgStream.drawCircle(feature.x(), feature.y(), feature.scale(),
          svgStyle().stroke("yellow", 2.0));
    }

    // Write the SVG file
    std::ostringstream os;
    os << stlplus::folder_append_separator(sOutDir)
      << stlplus::basename_part(iterFilename->m_sImageName)
      << "_" << vec_feat.size() << "_.svg";
    ofstream svgFile( os.str().c_str() );
    svgFile << svgStream.closeSvgFile().str();
    svgFile.close();
  }
  return EXIT_SUCCESS;
}