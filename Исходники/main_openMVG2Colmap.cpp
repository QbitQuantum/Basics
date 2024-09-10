bool CreateImageFile( const SfM_Data & sfm_data,
                      const std::string & sImagesFilename)
{
 /* images.txt
      # Image list with two lines of data per image:
      #   IMAGE_ID, QW, QX, QY, QZ, TX, TY, TZ, CAMERA_ID, NAME
      #   POINTS2D[] as (X, Y, POINT3D_ID)
      # Number of images: X, mean observations per image: Y
  */

  // Header
  std::ofstream images_file( sImagesFilename );

  if ( ! images_file )
  {
    std::cerr << "Cannot write file" << sImagesFilename << std::endl;
    return false;
  }
  images_file << "# Image list with two lines of data per image:\n";
  images_file << "#   IMAGE_ID, QW, QX, QY, QZ, TX, TY, TZ, CAMERA_ID, NAME\n";
  images_file << "#   POINTS2D[] as (X, Y, POINT3D_ID)\n";
  images_file << "# Number of images: X, mean observations per image: Y\n";

  std::map< IndexT, std::vector< std::tuple<double, double, IndexT> > > viewIdToPoints2D;
  const Landmarks & landmarks = sfm_data.GetLandmarks();
  {
    for ( Landmarks::const_iterator iterLandmarks = landmarks.begin();
          iterLandmarks != landmarks.end(); ++iterLandmarks)
    {
      const IndexT point3d_id = iterLandmarks->first;

      // Tally set of feature observations
      const Observations & obs = iterLandmarks->second.obs;
      for ( Observations::const_iterator itObs = obs.begin(); itObs != obs.end(); ++itObs )
      {
        const IndexT currentViewId = itObs->first;
        const Observation & ob = itObs->second;
        viewIdToPoints2D[currentViewId].push_back(std::make_tuple(ob.x( 0 ), ob.x( 1 ), point3d_id));
      }
    }
  }

  {
    C_Progress_display my_progress_bar( sfm_data.GetViews().size(), std::cout, "\n- CREATE IMAGE FILE -\n" );

    for (Views::const_iterator iter = sfm_data.GetViews().begin();
         iter != sfm_data.GetViews().end(); ++iter, ++my_progress_bar)
    {
      const View * view = iter->second.get();

      if ( !sfm_data.IsPoseAndIntrinsicDefined( view ) )
      {
        continue;
      }

      const Pose3 pose = sfm_data.GetPoseOrDie( view );
      const Mat3 rotation = pose.rotation();
      const Vec3 translation = pose.translation();

      const double Tx = translation[0];
      const double Ty = translation[1];
      const double Tz = translation[2];
      Eigen::Quaterniond q( rotation );
      const double Qx = q.x();
      const double Qy = q.y();
      const double Qz = q.z();
      const double Qw = q.w();

      const IndexT image_id = view->id_view;
      // Colmap's camera_ids correspond to openMVG's intrinsic ids
      const IndexT camera_id = view->id_intrinsic;                           
      const std::string image_name = view->s_Img_path;

      // first line per image
      //IMAGE_ID, QW, QX, QY, QZ, TX, TY, TZ, CAMERA_ID, NAME
      images_file << image_id << " "
         << Qw << " "
         << Qx << " "
         << Qy << " "
         << Qz << " "
         << Tx << " "
         << Ty << " "
         << Tz << " "
         << camera_id << " "
         << image_name << " "     
         << "\n";

      // second line per image 
      //POINTS2D[] as (X, Y, POINT3D_ID)
      for (auto point2D: viewIdToPoints2D[image_id]) 
      {
        images_file << std::get<0>(point2D) << " " << 
        std::get<1>(point2D) << " " <<
        std::get<2>(point2D) << " ";
      }
      images_file << "\n";
    }
  }
  return true;
}