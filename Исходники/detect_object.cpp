//********************************
//* main
int main(int argc, char* argv[]) {
  if( (argc != 12) && (argc != 14) ){
    std::cerr << "usage: " << argv[0] << " [path] <rank_num> <exist_voxel_num_threshold> [model_pca_filename] <dim_model> <size1> <size2> <size3> <detect_th> <distance_th> /input:=/camera/rgb/points" << std::endl;
    exit( EXIT_FAILURE );
  }
  char tmpname[ 1000 ];
  ros::init (argc, argv, "detectObj", ros::init_options::AnonymousName);

  // read the length of voxel side
  sprintf( tmpname, "%s/param/parameters.txt", argv[1] );
  voxel_size = Param::readVoxelSize( tmpname );

  detect_th = atof( argv[9] );
  distance_th = atof( argv[10] );
  rank_num = atoi( argv[2] );

  // read the number of voxels in each subdivision's side of scene
  box_size = Param::readBoxSizeScene( tmpname );

  // read the dimension of compressed feature vectors
  dim = Param::readDim( tmpname );

  // set the dimension of the target object's subspace
  const int dim_model = atoi(argv[5]);
  if( dim <= dim_model ){
    std::cerr << "ERR: dim_model should be less than dim(in dim.txt)" << std::endl;
    exit( EXIT_FAILURE );
  }

  // read the threshold for RGB binalize
  sprintf( tmpname, "%s/param/color_threshold.txt", argv[1] );
  Param::readColorThreshold( color_threshold_r, color_threshold_g, color_threshold_b, tmpname );

  // determine the size of sliding box
  region_size = box_size * voxel_size;
  float tmp_val = atof(argv[6]) / region_size;
  int size1 = (int)tmp_val;
  if( ( ( tmp_val - size1 ) >= 0.5 ) || ( size1 == 0 ) ) size1++;
  tmp_val = atof(argv[7]) / region_size;
  int size2 = (int)tmp_val;
  if( ( ( tmp_val - size2 ) >= 0.5 ) || ( size2 == 0 ) ) size2++;
  tmp_val = atof(argv[8]) / region_size;
  int size3 = (int)tmp_val;
  if( ( ( tmp_val - size3 ) >= 0.5 ) || ( size3 == 0 ) ) size3++;
  sliding_box_size_x = size1 * region_size;
  sliding_box_size_y = size2 * region_size;
  sliding_box_size_z = size3 * region_size;

  // set variables
  search_obj.setRange( size1, size2, size3 );
  search_obj.setRank( rank_num );
  search_obj.setThreshold( atoi(argv[3]) );
  search_obj.readAxis( argv[4], dim, dim_model, ASCII_MODE_P, MULTIPLE_SIMILARITY );

  // read projection axis of the target object's subspace
  PCA pca;
  sprintf( tmpname, "%s/models/compress_axis", argv[1] );
  pca.read( tmpname, ASCII_MODE_P );
  Eigen::MatrixXf tmpaxis = pca.getAxis();
  Eigen::MatrixXf axis = tmpaxis.block( 0,0,tmpaxis.rows(),dim );
  Eigen::MatrixXf axis_t = axis.transpose();
  Eigen::VectorXf variance = pca.getVariance();
  if( WHITENING )
    search_obj.setSceneAxis( axis_t, variance, dim );
  else
    search_obj.setSceneAxis( axis_t );

  // object detection
  VoxelizeAndDetect vad;
  vad.loop();
  ros::spin();

  return 0;
}