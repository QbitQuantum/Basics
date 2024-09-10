//
// Create the description of an input image dataset for OpenMVG toolsuite
// - Export a SfM_Data file with View & Intrinsic data
//
int main(int argc, char **argv)
{
  CmdLine cmd;

  std::string sImageDir,
    sGroundTruthDir,
    sOutputDir = "";
  int ground_truth_Dataset = 0;


  cmd.add( make_option('i', sImageDir, "imageDirectory") );
  cmd.add( make_option('g', sGroundTruthDir, "groundTruthDirectory") );
  cmd.add( make_option('t', ground_truth_Dataset, "groundTruthDataset"));
  cmd.add( make_option('o', sOutputDir, "outputDirectory") );


  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch (const std::string& s) {
      std::cerr << "Usage: " << argv[0] << '\n'
      << "[-i|--imageDirectory]\n"
      << "[-g|--groundTruthDirectory]\n"
      << "[-t]--groundTruthDataset]\n"
      << "\t 1: Strecha's Dataset\n"
      << "\t 2: MiddleBury's Dataset\n"
      << "\t 3: DTU MVS Dataset\n"
      << "\t 4: ETH 3D Dataset\n"
      << "\t 5: Kitti Odometry Dataset\n"
      << "[-o|--outputDirectory]\n"
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << " You called : " <<std::endl
            << argv[0] << std::endl
            << "--imageDirectory " << sImageDir << std::endl
            << "--groundTruthDirectory " << sGroundTruthDir << std::endl
            << "--groundTruthDataset " << ground_truth_Dataset << std::endl
            << "--outputDirectory " << sOutputDir << std::endl;


  if ( !stlplus::folder_exists( sImageDir ) )
  {
    std::cerr << "\nThe input directory doesn't exist" << std::endl;
    return EXIT_FAILURE;
  }

  if ( !stlplus::folder_exists( sGroundTruthDir ) )
  {
    std::cerr << "\nThe input ground truth directory doesn't exist" << std::endl;
    return EXIT_FAILURE;
  }

  if (sOutputDir.empty())
  {
    std::cerr << "\nInvalid output directory" << std::endl;
    return EXIT_FAILURE;
  }

  if ( !stlplus::folder_exists( sOutputDir ) )
  {
    if ( !stlplus::folder_create( sOutputDir ))
    {
      std::cerr << "\nCannot create output directory" << std::endl;
      return EXIT_FAILURE;
    }
  }


  // Configure an empty scene with Views and their corresponding cameras
  std::shared_ptr<SfM_Data_GT_Loader_Interface> sfm_data_gt;
  switch(ground_truth_Dataset)
  {
    case 1:
      sfm_data_gt = std::make_shared<SfM_Data_GT_Loader_Strecha>();
      break;
    case 2:
      sfm_data_gt = std::make_shared<SfM_Data_GT_Loader_MiddleBury>();
      break;
    case 3:
      sfm_data_gt = std::make_shared<SfM_Data_GT_Loader_DTU_MVS>();
      break;
    case 4:
      sfm_data_gt = std::make_shared<SfM_Data_GT_Loader_ETH_3D>();
      break;
    case 5:
      sfm_data_gt = std::make_shared<SfM_Data_GT_Loader_Kitti>();
      break;
    default:
      std::cerr<<"Error: Not Support Dataset \n";
      return EXIT_FAILURE;
  }

  // Load the gt data
  if (!sfm_data_gt->run(sGroundTruthDir, sImageDir))
  {
    return EXIT_FAILURE;
  }

  // Store SfM_Data views & intrinsic data
  if (!Save(
    sfm_data_gt->GetSfMData(),
    stlplus::create_filespec( sOutputDir, "sfm_data.json" ).c_str(),
    ESfM_Data(ALL)))
  {
    return EXIT_FAILURE;
  }

  std::cout << std::endl
    << "SfMInit_ImageListing report:\n"
    << "listed #File(s): " << sfm_data_gt->GetImageNumber() << "\n"
    << "usable #File(s) listed in sfm_data: " << sfm_data_gt->GetSfMData().GetViews().size() << "\n"
    << "usable #Pose(s) listed in sfm_data: " << sfm_data_gt->GetSfMData().GetPoses().size() << "\n"
    << "usable #Intrinsic(s) listed in sfm_data: " << sfm_data_gt->GetSfMData().GetIntrinsics().size() << std::endl;
  return EXIT_SUCCESS;
}