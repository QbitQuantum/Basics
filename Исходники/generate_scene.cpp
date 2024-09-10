bool CGEOM::generate_scene_trans
( const SceneGeneratorOptions& sc_opts,
  Eigen::MatrixXd& mP3D,
  Eigen::MatrixXd& mMeasT,
  Eigen::MatrixXd& mMeasN,
  Eigen::Matrix3d& mR,
  Eigen::Vector3d& mt
) {
    if( !generate_scene( sc_opts,
                         mP3D, mMeasT, mMeasN
                       ) ) {
        return false;
    }

    // Create random transform
    mt = mP3D.rowwise().mean();
    const double drotx = rand_range_d( -45., 45. )*3.14159/180.;
    const double droty = rand_range_d( -45., 45. )*3.14159/180.;
    const double drotz = rand_range_d( -45., 45. )*3.14159/180.;
#if 1
    mR =
        ( CEIGEN::skew_rot<Eigen::Matrix3d,double>( drotx, 0., 0. ) +
          CEIGEN::skew_rot<Eigen::Matrix3d,double>( 0., droty , 0.) +
          CEIGEN::skew_rot<Eigen::Matrix3d,double>( 0., 0., drotz ) ).exp();
#else
    mR = Eigen::Matrix3d::Identity();
#endif

    mP3D.colwise() -= mt;
    mP3D = mR.transpose() * mP3D;

    return true;
}