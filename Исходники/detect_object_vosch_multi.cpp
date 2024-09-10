//********************************
//* main
int main(int argc, char* argv[]) {
  if( (argc != 13) && (argc != 15) ){
    std::cerr << "usage: " << argv[0] << " [path] <rank_num> <exist_voxel_num_threshold> [model_pca_filename] <dim_model> <size1> <size2> <size3> <detect_th> <distance_th> <model_num> /input:=/camera/rgb/points" << std::endl;
    exit( EXIT_FAILURE );
  }
  char tmpname[ 1000 ];
  ros::init (argc, argv, "detect_object_vosch_multi", ros::init_options::AnonymousName);

  // read the length of voxel side
  sprintf( tmpname, "%s/param/parameters.txt", argv[1] );
  voxel_size = Param::readVoxelSize( tmpname );

  detect_th = atof( argv[9] );
  distance_th = atof( argv[10] );
  model_num = atoi( argv[11] );
  rank_num = atoi( argv[2] );

  // set marker color
  const int marker_model_num = 6;
  if( model_num > marker_model_num ){
    std::cerr << "Please set more marker colors for detection of more than " << marker_model_num << " objects." << std::endl;
    exit( EXIT_FAILURE );
  }
  marker_color_r = new float[ marker_model_num ];
  marker_color_g = new float[ marker_model_num ];
  marker_color_b = new float[ marker_model_num ];
  marker_color_r[ 0 ] = 1.0; marker_color_g[ 0 ] = 0.0; marker_color_b[ 0 ] = 0.0;  // red
  marker_color_r[ 1 ] = 0.0; marker_color_g[ 1 ] = 1.0; marker_color_b[ 1 ] = 0.0;  // green
  marker_color_r[ 2 ] = 0.0; marker_color_g[ 2 ] = 0.0; marker_color_b[ 2 ] = 1.0;  // blue
  marker_color_r[ 3 ] = 1.0; marker_color_g[ 3 ] = 1.0; marker_color_b[ 3 ] = 0.0;  // yellow
  marker_color_r[ 4 ] = 0.0; marker_color_g[ 4 ] = 1.0; marker_color_b[ 4 ] = 1.0;  // cyan
  marker_color_r[ 5 ] = 1.0; marker_color_g[ 5 ] = 0.0; marker_color_b[ 5 ] = 1.0;  // magenta
  // marker_color_r[ 0 ] = 0.0; marker_color_g[ 0 ] = 1.0; marker_color_b[ 0 ] = 0.0; // green
  // marker_color_r[ 1 ] = 0.0; marker_color_g[ 1 ] = 0.0; marker_color_b[ 1 ] = 1.0; // blue
  // marker_color_r[ 2 ] = 0.0; marker_color_g[ 2 ] = 1.0; marker_color_b[ 2 ] = 1.0; // cyan
  // marker_color_r[ 3 ] = 1.0; marker_color_g[ 3 ] = 0.0; marker_color_b[ 3 ] = 0.0; // pink

  // read the number of voxels in each subdivision's side of scene
  box_size = Param::readBoxSizeScene( tmpname );

  // read the dimension of compressed feature vectors
  dim = Param::readDim( tmpname );
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
  search_obj.setModelNum( model_num );
#ifdef CCHLAC_TEST
  sprintf( tmpname, "%s/param/max_c.txt", argv[1] );
#else
  sprintf( tmpname, "%s/param/max_r.txt", argv[1] );
#endif
  search_obj.setNormalizeVal( tmpname );
  search_obj.setRange( size1, size2, size3 );
  search_obj.setRank( rank_num * model_num ); // for removeOverlap()
  search_obj.setThreshold( atoi(argv[3]) );

  // read projection axes of the target objects' subspace
  FILE *fp = fopen( argv[4], "r" );
  char **model_file_names = new char* [ model_num ];
  char line[ 1000 ];
  for( int i=0; i<model_num; i++ ){
    model_file_names[ i ] = new char [ 1000 ];
    if( fgets( line, sizeof(line), fp ) == NULL ) std::cerr<<"fgets err"<<std::endl;
    line[ strlen( line ) - 1 ] = '\0';
    //fscanf( fp, "%s\n", model_file_names + i );
    //model_file_names[ i ] = line;
    sprintf( model_file_names[ i ], "%s", line );
    //std::cout << model_file_names[ i ] << std::endl;
  }
  fclose(fp);
  search_obj.readAxis( model_file_names, dim, dim_model, ASCII_MODE_P, MULTIPLE_SIMILARITY );

  // read projection axis for feature compression
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