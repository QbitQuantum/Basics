/// Compute between the Views
/// Compute view image description (feature & descriptor extraction using OpenCV)
/// Compute putative local feature matches (descriptor matching)
/// Compute geometric coherent feature matches (robust model estimation from putative matches)
/// Export computed data
int main(int argc, char **argv)
{
  CmdLine cmd;

  std::string sSfM_Data_Filename;
  std::string sOutDir = "";
  bool bForce = false;
#ifdef USE_OCVSIFT
  std::string sImage_Describer_Method = "AKAZE_OPENCV";
#endif

  // required
  cmd.add( make_option('i', sSfM_Data_Filename, "input_file") );
  cmd.add( make_option('o', sOutDir, "outdir") );
  // Optional
  cmd.add( make_option('f', bForce, "force") );
#ifdef USE_OCVSIFT
  cmd.add( make_option('m', sImage_Describer_Method, "describerMethod") );
#endif

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch(const std::string& s) {
      std::cerr << "Usage: " << argv[0] << '\n'
      << "[-i|--input_file]: a SfM_Data file \n"
      << "[-o|--outdir] path \n"
      << "\n[Optional]\n"
      << "[-f|--force: Force to recompute data]\n"
#ifdef USE_OCVSIFT
      << "[-m|--describerMethod\n"
      << "  (method to use to describe an image):\n"
      << "   AKAZE_OPENCV (default),\n"
      << "   SIFT_OPENCV: SIFT FROM OPENCV,\n"
#endif
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << " You called : " <<std::endl
            << argv[0] << std::endl
            << "--input_file " << sSfM_Data_Filename << std::endl
            << "--outdir " << sOutDir << std::endl
#ifdef USE_OCVSIFT
            << "--describerMethod " << sImage_Describer_Method << std::endl
#endif
            ;

  if (sOutDir.empty())  {
    std::cerr << "\nIt is an invalid output directory" << std::endl;
    return EXIT_FAILURE;
  }

  // Create output dir
  if (!stlplus::folder_exists(sOutDir))
  {
    if (!stlplus::folder_create(sOutDir))
    {
      std::cerr << "Cannot create output directory" << std::endl;
      return EXIT_FAILURE;
    }
  }

  //---------------------------------------
  // a. Load input scene
  //---------------------------------------
  SfM_Data sfm_data;
  if (!Load(sfm_data, sSfM_Data_Filename, ESfM_Data(VIEWS|INTRINSICS))) {
    std::cerr << std::endl
      << "The input file \""<< sSfM_Data_Filename << "\" cannot be read" << std::endl;
    return false;
  }

  // Init the image_describer
  // - retrieve the used one in case of pre-computed features
  // - else create the desired one

  using namespace openMVG::features;
  std::unique_ptr<Image_describer> image_describer;

  const std::string sImage_describer = stlplus::create_filespec(sOutDir, "image_describer", "json");
  if (stlplus::is_file(sImage_describer))
  {
    // Dynamically load the image_describer from the file (will restore old used settings)
    std::ifstream stream(sImage_describer.c_str());
    if (!stream.is_open())
      return false;

    cereal::JSONInputArchive archive(stream);
    archive(cereal::make_nvp("image_describer", image_describer));
  }
  else
  {
#ifdef USE_OCVSIFT
    if (sImage_Describer_Method == "AKAZE_OPENCV")
    {
      image_describer.reset(new AKAZE_OCV_Image_describer);
    }
    else
    if (sImage_Describer_Method == "SIFT_OPENCV")
    {
      image_describer.reset(new SIFT_OPENCV_Image_describer());
    }
    else
    {
      std::cerr << "Unknown image describer method." << std::endl;
      return EXIT_FAILURE;
    }
#else
    image_describer.reset(new AKAZE_OCV_Image_describer);
#endif

    // Export the used Image_describer and region type for:
    // - dynamic future regions computation and/or loading
    {
      std::ofstream stream(sImage_describer.c_str());
      if (!stream.is_open())
        return false;

      cereal::JSONOutputArchive archive(stream);
      archive(cereal::make_nvp("image_describer", image_describer));
      std::unique_ptr<Regions> regionsType;
      image_describer->Allocate(regionsType);
      archive(cereal::make_nvp("regions_type", regionsType));
    }
  }

  // Feature extraction routines
  // For each View of the SfM_Data container:
  // - if regions file exist continue,
  // - if no file, compute features
  {
    system::Timer timer;
    Image<unsigned char> imageGray;
    C_Progress_display my_progress_bar( sfm_data.GetViews().size(),
      std::cout, "\n- EXTRACT FEATURES -\n" );
    for(Views::const_iterator iterViews = sfm_data.views.begin();
        iterViews != sfm_data.views.end();
        ++iterViews, ++my_progress_bar)
    {
      const View * view = iterViews->second.get();
      const std::string sView_filename = stlplus::create_filespec(sfm_data.s_root_path,
        view->s_Img_path);
      const std::string sFeat = stlplus::create_filespec(sOutDir,
        stlplus::basename_part(sView_filename), "feat");
      const std::string sDesc = stlplus::create_filespec(sOutDir,
        stlplus::basename_part(sView_filename), "desc");

      //If features or descriptors file are missing, compute them
      if (bForce || !stlplus::file_exists(sFeat) || !stlplus::file_exists(sDesc))
      {
        if (!ReadImage(sView_filename.c_str(), &imageGray))
          continue;

        // Compute features and descriptors and export them to files
        std::unique_ptr<Regions> regions;
        image_describer->Describe(imageGray, regions);
        image_describer->Save(regions.get(), sFeat, sDesc);
      }
    }
    std::cout << "Task done in (s): " << timer.elapsed() << std::endl;
  }
  return EXIT_SUCCESS;
}