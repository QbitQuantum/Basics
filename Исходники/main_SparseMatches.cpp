int main(int argc, char **argv)
{
  CmdLine cmd;

  std::string sImaDirectory;
  std::string sOutDir = "";
  std::string sGeometricModel = "f";
  float fDistRatio = .6f;
  bool bOctMinus1 = false;
  float dPeakThreshold = 0.04f;
  int sequentialLimit = 0;

  cmd.add( make_option('i', sImaDirectory, "imadir") );
  cmd.add( make_option('o', sOutDir, "outdir") );
  cmd.add( make_option('r', fDistRatio, "distratio") );
  cmd.add( make_option('s', bOctMinus1, "octminus1") );
  cmd.add( make_option('p', dPeakThreshold, "peakThreshold") );
  cmd.add( make_option('g', sGeometricModel, "geometricModel") );
  cmd.add(make_option('l', sequentialLimit, "sequentialLimit"));//

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch(const std::string& s) {
      std::cerr << "Usage: " << argv[0] << '\n'
      << "[-i|--imadir path] \n"
      << "[-o|--outdir path] \n"
      << "\n[Optional]\n"
      << "[-r|--distratio 0.6] \n"
      << "[-s|--octminus1 0 or 1] \n"
      << "[-p|--peakThreshold 0.04 -> 0.01] \n"
      << "[-g|--geometricModel f, e or h] \n"
	  << "[-l|--sequentialLimit 1 or greater]"
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << " You called : " <<std::endl
            << argv[0] << std::endl
            << "--imadir " << sImaDirectory << std::endl
            << "--outdir " << sOutDir << std::endl
            << "--distratio " << fDistRatio << std::endl
            << "--octminus1 " << bOctMinus1 << std::endl
            << "--peakThreshold " << dPeakThreshold << std::endl
            << "--geometricModel " << sGeometricModel << std::endl
			<< "--sequentialLimit " << sequentialLimit << std::endl;

  if (sOutDir.empty())  {
    std::cerr << "\nIt is an invalid output directory" << std::endl;
    return EXIT_FAILURE;
  }

  eGeometricModel eGeometricModelToCompute = FUNDAMENTAL_MATRIX;
  std::string sGeometricMatchesFilename = "";
  switch(sGeometricModel[0])
  {
    case 'f': case 'F':
      eGeometricModelToCompute = FUNDAMENTAL_MATRIX;
      sGeometricMatchesFilename = "matches.f.txt";
    break;
    case 'e': case 'E':
      eGeometricModelToCompute = ESSENTIAL_MATRIX;
      sGeometricMatchesFilename = "matches.e.txt";
    break;
    case 'h': case 'H':
      eGeometricModelToCompute = HOMOGRAPHY_MATRIX;
      sGeometricMatchesFilename = "matches.h.txt";
    break;
    default:
      std::cerr << "Unknown geometric model" << std::endl;
      return EXIT_FAILURE;
  }


  // -----------------------------
  // a. List images
  // b. Compute features and descriptors
  // c. Compute putative descriptor matches
  // d. Geometric filtering of putative matches
  // e. Export some statistics
  // -----------------------------

  // Create output dir
  if (!stlplus::folder_exists(sOutDir))
    stlplus::folder_create( sOutDir );

  //---------------------------------------
  // a. List images
  //---------------------------------------
  std::string sListsFile = stlplus::create_filespec(sOutDir, "lists.txt" );
  if (!stlplus::is_file(sListsFile)) {
    std::cerr << std::endl
      << "The input file \""<< sListsFile << "\" is missing" << std::endl;
    return false;
  }

  std::vector<openMVG::SfMIO::CameraInfo> vec_camImageName;
  std::vector<openMVG::SfMIO::IntrinsicCameraInfo> vec_focalGroup;
//  if (!openMVG::SfMIO::loadImageList( vec_camImageName,
//                                      vec_focalGroup,
//                                      sListsFile) )
  if (!readImageList(vec_camImageName, vec_focalGroup, sListsFile))
  {
	  std::cerr << "\nEmpty image list." << std::endl;
	  return false;
  }

  if (eGeometricModelToCompute == ESSENTIAL_MATRIX)
  {
    //-- In the case of the essential matrix we check if only one K matrix is present.
    //-- Due to the fact that the generic framework allows only one K matrix for the
    // robust essential matrix estimation in image collection.
    std::vector<openMVG::SfMIO::IntrinsicCameraInfo>::iterator iterF =
    std::unique(vec_focalGroup.begin(), vec_focalGroup.end(), testIntrinsicsEquality);
    vec_focalGroup.resize( std::distance(vec_focalGroup.begin(), iterF) );
    if (vec_focalGroup.size() == 1) {
      // Set all the intrinsic ID to 0
      for (size_t i = 0; i < vec_camImageName.size(); ++i)
        vec_camImageName[i].m_intrinsicId = 0;
    }
    else  {
      std::cerr << "There is more than one focal group in the lists.txt file." << std::endl
        << "Only one focal group is supported for the image collection robust essential matrix estimation." << std::endl;
      return EXIT_FAILURE;
    }
  }

  //-- Two alias to ease access to image filenames and image sizes
  std::vector<std::string> vec_fileNames;
  std::vector<std::pair<size_t, size_t> > vec_imagesSize;
  for ( std::vector<openMVG::SfMIO::CameraInfo>::const_iterator
    iter_camInfo = vec_camImageName.begin();
    iter_camInfo != vec_camImageName.end();
    iter_camInfo++ )
  {
    vec_imagesSize.push_back( std::make_pair( vec_focalGroup[iter_camInfo->m_intrinsicId].m_w,
                                              vec_focalGroup[iter_camInfo->m_intrinsicId].m_h ) );
    vec_fileNames.push_back( stlplus::create_filespec( sImaDirectory, iter_camInfo->m_sImageName) );
  }

  //---------------------------------------
  // b. Compute features and descriptor
  //    - extract sift features and descriptor
  //    - if keypoints already computed, re-load them
  //    - else save features and descriptors on disk
  //---------------------------------------

	typedef Descriptor<unsigned char, 128> DescriptorT;
	typedef SIOPointFeature FeatureT;
	typedef std::vector<FeatureT> FeatsT;
	typedef vector<DescriptorT > DescsT;
	typedef KeypointSet<FeatsT, DescsT > KeypointSetT;

	{
		std::cout << "\n\nEXTRACT FEATURES" << std::endl;
		vec_imagesSize.resize(vec_fileNames.size());

		Image<unsigned char> imageGray;

		C_Progress_display my_progress_bar(vec_fileNames.size());
		for (size_t i = 0; i < vec_fileNames.size(); ++i)  {

			std::string sFeat = stlplus::create_filespec(sOutDir,
				stlplus::basename_part(vec_fileNames[i]), "feat");
			std::string sDesc = stlplus::create_filespec(sOutDir,
				stlplus::basename_part(vec_fileNames[i]), "desc");

			//If descriptors or features file are missing, compute them
			if (!stlplus::file_exists(sFeat) || !stlplus::file_exists(sDesc)) {

				if (!ReadImage(vec_fileNames[i].c_str(), &imageGray))
					continue;

				// Compute features and descriptors and export them to files
				KeypointSetT kpSet;
				SIFTDetector(imageGray,
					kpSet.features(), kpSet.descriptors(),
					bOctMinus1, true, dPeakThreshold);
				kpSet.saveToBinFile(sFeat, sDesc);
			}
			++my_progress_bar;
		}
	}

  //---------------------------------------
  // c. Compute putative descriptor matches
  //    - L2 descriptor matching
  //    - Keep correspondences only if NearestNeighbor ratio is ok
  //---------------------------------------
  PairWiseMatches map_PutativesMatches;
  // Define the matcher and the used metric (Squared L2)
  // ANN matcher could be defined as follow:
  typedef flann::L2<DescriptorT::bin_type> MetricT;
  typedef ArrayMatcher_Kdtree_Flann<DescriptorT::bin_type, MetricT> MatcherT;
  // Brute force matcher can be defined as following:
  //typedef L2_Vectorized<DescriptorT::bin_type> MetricT;
  //typedef ArrayMatcherBruteForce<DescriptorT::bin_type, MetricT> MatcherT;

  // If the matches already exists, reload them
  if (stlplus::file_exists(sOutDir + "/matches.putative.txt"))
  {
    PairedIndMatchImport(sOutDir + "/matches.putative.txt", map_PutativesMatches);
    std::cout << std::endl << "PUTATIVE MATCHES -- PREVIOUS RESULTS LOADED" << std::endl;
  }
  else // Compute the putatives matches
  {
	  //Matcher_AllInMemory<KeypointSetT, MatcherT> collectionMatcher(fDistRatio);
	  SparseMatcher<KeypointSetT, MatcherT> collectionMatcher(fDistRatio, sequentialLimit);

	  if (collectionMatcher.loadData(vec_fileNames, sOutDir))
	  {
		  std::cout << std::endl << "PUTATIVE MATCHES" << std::endl;
		  collectionMatcher.Match(vec_fileNames, map_PutativesMatches);
		  //---------------------------------------
		  //-- Export putative matches
		  //---------------------------------------
		  std::ofstream file(std::string(sOutDir + "/matches.putative.txt").c_str());
		  if (file.is_open())
			  PairedIndMatchToStream(map_PutativesMatches, file);
		  file.close();
	  }
  }
  //-- export putative matches Adjacency matrix
  PairWiseMatchingToAdjacencyMatrixSVG(vec_fileNames.size(),
	  map_PutativesMatches,
	  stlplus::create_filespec(sOutDir, "PutativeAdjacencyMatrix", "svg"));

  
  //---------------------------------------
  // d. Geometric filtering of putative matches
  //    - AContrario Estimation of the desired geometric model
  //    - Use an upper bound for the a contrario estimated threshold
  //---------------------------------------
  PairWiseMatches map_GeometricMatches;

  ImageCollectionGeometricFilter<FeatureT> collectionGeomFilter;
  const double maxResidualError = 4.0;
  size_t iterations = 8192;	// 4096
  if (collectionGeomFilter.loadData(vec_fileNames, sOutDir))
  {
    std::cout << std::endl << " - GEOMETRIC FILTERING - " << std::endl;
    switch (eGeometricModelToCompute)
    {
      case FUNDAMENTAL_MATRIX:
      {
       collectionGeomFilter.Filter(
		  GeometricFilter_FMatrix_AC(maxResidualError, iterations),
          map_PutativesMatches,
          map_GeometricMatches,
          vec_imagesSize);
      }
      break;
      case ESSENTIAL_MATRIX:
      {
        collectionGeomFilter.Filter(
          GeometricFilter_EMatrix_AC(vec_focalGroup[0].m_K, maxResidualError),
          map_PutativesMatches,
          map_GeometricMatches,
          vec_imagesSize);

        //-- Perform an additional check to remove pairs with poor overlap
        std::vector<PairWiseMatches::key_type> vec_toRemove;
        for (PairWiseMatches::const_iterator iterMap = map_GeometricMatches.begin();
          iterMap != map_GeometricMatches.end(); ++iterMap)
        {
          size_t putativePhotometricCount = map_PutativesMatches.find(iterMap->first)->second.size();
          size_t putativeGeometricCount = iterMap->second.size();
          float ratio = putativeGeometricCount / (float)putativePhotometricCount;
          if (putativeGeometricCount < 50 || ratio < .3f)  {
            // the pair will be removed
            vec_toRemove.push_back(iterMap->first);
          }
        }
        //-- remove discarded pairs
        for (std::vector<PairWiseMatches::key_type>::const_iterator
          iter =  vec_toRemove.begin(); iter != vec_toRemove.end(); ++iter)
        {
          map_GeometricMatches.erase(*iter);
        }
      }
      break;
      case HOMOGRAPHY_MATRIX:
      {

        collectionGeomFilter.Filter(
          GeometricFilter_HMatrix_AC(maxResidualError),
          map_PutativesMatches,
          map_GeometricMatches,
          vec_imagesSize);
      }
      break;
    }

    //---------------------------------------
    //-- Export geometric filtered matches
    //---------------------------------------
    std::ofstream file (string(sOutDir + "/" + sGeometricMatchesFilename).c_str());
    if (file.is_open())
      PairedIndMatchToStream(map_GeometricMatches, file);
    file.close();

    //-- export Adjacency matrix
    std::cout << "\n Export Adjacency Matrix of the pairwise's geometric matches"
      << std::endl;
    PairWiseMatchingToAdjacencyMatrixSVG(vec_fileNames.size(),
      map_GeometricMatches,
      stlplus::create_filespec(sOutDir, "GeometricAdjacencyMatrix", "svg"));
  }
  return EXIT_SUCCESS;
}