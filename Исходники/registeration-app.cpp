void RegApp::featuresReferenceHandler(const lcm::ReceiveBuffer* rbuf, const std::string& channel, const  reg::features_t* msg){
  
  if (registeration_mode_ != 1){ // ignore features if we havent just been asked to track to them
    return;
  }

  cout << "\n\ngot reference features @ "<< msg->utime<<"\n";

  // now find the corresponding image and pair it
  bool feat_image_matched_ = false;
  for(int i=0; i < image_queue_->size(); i++){
    //cout << image_queue_->at(i).utime << " " << i << "\n";
    if (msg->utime == image_queue_->at(i).utime){
      cur_features_ = getFeaturesFromLCM(msg,cur_pose_);
      cur_image_ = image_queue_->at(i);
      cout << "image and features matched: " << i << " " << image_queue_->at(i).utime << " ("<< cur_features_.size()<<"f)\n"; 
      feat_image_matched_ = true;

      break;
    }
  }
  
  if (!feat_image_matched_){
     cout <<"didn't find a matching reference image - make image deque bigger\n";
     exit(-1);
  } 

  ref_features_ = cur_features_;
  ref_image_ = cur_image_;
  ref_pose_ = cur_pose_;

  // set the reference image
  cout << "Will now register to " << ref_features_.size() << " features\n";
  
  // Send the pose we will try to register back to:
  Isometry3dTime ref_poseT = Isometry3dTime(ref_image_.utime, ref_pose_);
  pc_vis_->pose_to_lcm_from_list(70000, ref_poseT);

  deque_to_cloud(laser_queue_, botframes_, accum_cloud);

  Isometry3dTime null_poseT = Isometry3dTime(ref_image_.utime, Eigen::Isometry3d::Identity()  );
  pc_vis_->pose_to_lcm_from_list(70001, null_poseT);
  pc_vis_->ptcld_to_lcm_from_list(70002, *accum_cloud, ref_image_.utime, ref_image_.utime);

  std::stringstream ss2;
  print_Isometry3d(ref_pose_, ss2);
  std::cout << "Received refpose: " << ss2.str() << "\n";

  Eigen::Isometry3f pose_f = ref_pose_.inverse().cast<float>();
  Eigen::Quaternionf pose_quat(pose_f.rotation());
  pcl::transformPointCloud (*accum_cloud, *accum_cloud,
      pose_f.translation(), pose_quat); // !! modifies accum_cloud
  pc_vis_->ptcld_to_lcm_from_list(70003, *accum_cloud, ref_image_.utime, ref_image_.utime);

  registeration_mode_ = 2;
}