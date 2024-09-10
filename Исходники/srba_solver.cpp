SRBASolver::SRBASolver()
{
  rba_.setVerbosityLevel( 2 );   // 0: None; 1:Important only; 2:Verbose
  
// =========== Topology parameters ===========
  rba_.parameters.srba.max_tree_depth       = 3;
  rba_.parameters.srba.max_optimize_depth   = 3; 
  rba_.parameters.ecp.min_obs_to_loop_closure = 1; // This is a VERY IMPORTANT PARAM, if it is set to 1 everything goes to shit

  rba_.parameters.srba.use_robust_kernel = false;
  rba_.parameters.srba.optimize_new_edges_alone = true;
  rba_.parameters.srba.dumpToConsole();

  first_keyframe_ = true;
  curr_kf_id_ = 0;

  marker_count_ = 0;

  relative_map_frame_ = "relative_map";
  global_map_frame_ = "global_map";
  loop_closed_ = false;

  // Information matrix for relative pose observations:
  {
    Eigen::Matrix3d ObsL;
  ObsL.setZero();
  ObsL(0,0) = 1/(STD_NOISE_XY*STD_NOISE_XY); // x
  ObsL(1,1) = 1/(STD_NOISE_XY*STD_NOISE_XY); // y
  ObsL(2,2) = 1/(STD_NOISE_YAW*STD_NOISE_YAW); // phi
  // Set:
  rba_.parameters.obs_noise.lambda = ObsL;
  }
}