inline bool 
pcl::gpu::kinfuLS::KinfuTracker::performICP(const Intr& cam_intrinsics, Matrix3frm& previous_global_rotation, Vector3f& previous_global_translation, Matrix3frm& current_global_rotation , Vector3f& current_global_translation)
{
  
  if(disable_icp_)
  {
    lost_=false;
    return (true);
  }
  
  // Compute inverse rotation
  Matrix3frm previous_global_rotation_inv = previous_global_rotation.inverse ();  // Rprev.t();  
 
 ///////////////////////////////////////////////
  // Convert pose to device type
  Mat33  device_cam_rot_local_prev_inv; 
  float3 device_cam_trans_local_prev;
  convertTransforms(previous_global_rotation_inv, previous_global_translation, device_cam_rot_local_prev_inv, device_cam_trans_local_prev);  
  device_cam_trans_local_prev -= getCyclicalBufferStructure ()->origin_metric; ;
 
  // Use temporary pose, so that we modify the current global pose only if ICP converged
  Matrix3frm resulting_rotation;
  Vector3f resulting_translation;
  
  // Initialize output pose to current pose
  current_global_rotation = previous_global_rotation;
  current_global_translation = previous_global_translation;
 
  ///////////////////////////////////////////////
  // Run ICP
  {
    //ScopeTime time("icp-all");
    for (int level_index = LEVELS-1; level_index>=0; --level_index)
    {
      int iter_num = icp_iterations_[level_index];
      
      // current vertex and normal maps
      MapArr& vmap_curr = vmaps_curr_[level_index];
      MapArr& nmap_curr = nmaps_curr_[level_index];   
      
      // previous vertex and normal maps
      MapArr& vmap_g_prev = vmaps_g_prev_[level_index];
      MapArr& nmap_g_prev = nmaps_g_prev_[level_index];
      
      // We need to transform the maps from global to local coordinates
      Mat33&  rotation_id = device_cast<Mat33> (rmats_[0]); // Identity Rotation Matrix. Because we only need translation
      float3 cube_origin = (getCyclicalBufferStructure ())->origin_metric;
      cube_origin = -cube_origin;
      
      MapArr& vmap_temp = vmap_g_prev;
      MapArr& nmap_temp = nmap_g_prev;
      transformMaps (vmap_temp, nmap_temp, rotation_id, cube_origin, vmap_g_prev, nmap_g_prev); 
      
      // run ICP for iter_num iterations (return false when lost)
      for (int iter = 0; iter < iter_num; ++iter)
      {
        //CONVERT POSES TO DEVICE TYPES
        // CURRENT LOCAL POSE
        Mat33    device_current_rotation = device_cast<Mat33> (current_global_rotation); // We do not deal with changes in rotations        
        float3 device_current_translation_local = device_cast<float3> (current_global_translation);
        device_current_translation_local -= getCyclicalBufferStructure ()->origin_metric; 
                
        Eigen::Matrix<double, 6, 6, Eigen::RowMajor> A;
        Eigen::Matrix<double, 6, 1> b;

        // call the ICP function (see paper by Kok-Lim Low "Linear Least-squares Optimization for Point-to-Plane ICP Surface Registration")
        estimateCombined (device_current_rotation, device_current_translation_local, vmap_curr, nmap_curr, device_cam_rot_local_prev_inv, device_cam_trans_local_prev, cam_intrinsics (level_index), 
                          vmap_g_prev, nmap_g_prev, distThres_, angleThres_, gbuf_, sumbuf_, A.data (), b.data ());

        // checking nullspace 
        double det = A.determinant ();
    
        if ( fabs (det) < 1e-15 /*100000 */ || pcl_isnan (det) ) //TODO find a threshold that makes ICP track well, but prevents it from generating wrong transforms
        {
          if (pcl_isnan (det)) cout << "qnan" << endl;
          if(lost_ == false)
            PCL_ERROR ("ICP LOST... PLEASE COME BACK TO THE LAST VALID POSE (green)\n");
          //reset (); //GUI will now show the user that ICP is lost. User needs to press "R" to reset the volume
          lost_ = true;
          return (false);
        }

        Eigen::Matrix<float, 6, 1> result = A.llt ().solve (b).cast<float>();
        float alpha = result (0);
        float beta  = result (1);
        float gamma = result (2);

        // deduce incremental rotation and translation from ICP's results
        Eigen::Matrix3f cam_rot_incremental = (Eigen::Matrix3f)AngleAxisf (gamma, Vector3f::UnitZ ()) * AngleAxisf (beta, Vector3f::UnitY ()) * AngleAxisf (alpha, Vector3f::UnitX ());
        Vector3f cam_trans_incremental = result.tail<3> ();

        //compose global pose
        current_global_translation = cam_rot_incremental * current_global_translation + cam_trans_incremental;
        current_global_rotation = cam_rot_incremental * current_global_rotation;
      }
    }
  }
  // ICP has converged
  lost_ = false;
  return (true);
}