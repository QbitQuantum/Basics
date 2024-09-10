GraphAndValues Masseuse::LoadPoseGraphAndLCC(
    const string& pose_graph_file, bool read_lcc) {


  FILE *fp = (FILE *)fopen(pose_graph_file.c_str(), "rb");

  if (fp == NULL) {
    fprintf(stderr, "Could not open file %s\n",
            pose_graph_file.c_str());
  }


  if (fread(&origin, sizeof(Eigen::Vector6d), 1, fp) != 1) {
    throw invalid_argument("LoadPoseGraphAndLCC:  Cannot load the origin!");
  }

  //  std::cerr << "read origin: " << origin.transpose() << std::endl;

  unsigned numRelPoses = 0;
  unsigned numLCC = 0;

  if (fread(&numRelPoses, sizeof(unsigned), 1, fp) != 1) {
    printf("error! Cannot load num of relative poses.\n");
    throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
  }

  if(read_lcc){
    if (fread(&numLCC, sizeof(unsigned), 1, fp) != 1) {
      printf("error! Cannot load num of loop closure constraints.\n");
      throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
    }
  }

  std::cerr << "Will load " << numRelPoses << " rel poses, "
            << numLCC << " loop closure constranits." << std::endl;

  relative_poses.clear();
  // save all rel poses
  for (unsigned i = 0; i != numRelPoses; i++) {
    RelPose rPos;
    if (fread(&rPos.ref_id, sizeof(unsigned), 1, fp) != 1) {
      throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
    }
    if (fread(&rPos.live_id, sizeof(unsigned), 1, fp) != 1) {
      throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
    }
    if (fread(&rPos.rel_pose, sizeof(Eigen::Vector6d), 1, fp) != 1) {
      throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
    }
    if (fread(&rPos.cov, sizeof(Eigen::Matrix6d), 1, fp) != 1) {
      throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
    }

    relative_poses.push_back(rPos);
  }

  if(read_lcc){
    loop_closure_constraints.clear();
    // save all lcc here
    for (unsigned i = 0; i != numLCC; i++) {
      RelPose rPos;
      if (fread(&rPos.ref_id, sizeof(unsigned), 1, fp) != 1) {
        throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
      }
      if (fread(&rPos.live_id, sizeof(unsigned), 1, fp) != 1) {
        throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
      }
      if (fread(&rPos.rel_pose, sizeof(Eigen::Vector6d), 1, fp) != 1) {
        throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
      }
      if (fread(&rPos.cov, sizeof(Eigen::Matrix6d), 1, fp) != 1) {
        throw invalid_argument("LoadPoseGraphAndLCC:  error loading file");
      }

      loop_closure_constraints.push_back(rPos);
    }
  }
  fclose(fp);

  std::cerr << "Finished loading Pose Graph from  " << pose_graph_file
            << std::endl;

  std::shared_ptr<Values> initial(new Values);
  std::shared_ptr<Graph> graph(new Graph);
  Pose3 prev_pose;

  unsigned numICPfailed = 0;
  for (size_t ii = 0; ii < relative_poses.size(); ++ii){
    RelPose curr_pose = relative_poses[ii];
    if(ii == 0){
      // first relative pose, initialize graph at origin
      unsigned id = curr_pose.ref_id;
      Rot3 R(origin[3], origin[4], origin[5]);
      Point3 t = origin.head<3>();
      Pose3 orig(R, t);
      (*initial)[id] = orig;
      prev_pose = orig;

      //            std::cerr << "inserting origin: Rot: " << orig.rotationMatrix().eulerAngles
      //                         (0,1,2).transpose() << " Trans: " << orig.translation().transpose() <<
      //                         " at index:  " << id <<
      //                         std::endl;
    }

    // Build the next vertex using the relative contstraint
    Rot3 R(curr_pose.rel_pose[3], curr_pose.rel_pose[4],
        curr_pose.rel_pose[5]);
    Point3 t = curr_pose.rel_pose.head<3>();
    Pose3 rel(R, t);

    Pose3 new_pose = prev_pose*rel;
    (*initial)[curr_pose.live_id] = new_pose;

    //    std::cerr << "inserting pose: Rot: " << new_pose.rotationMatrix().eulerAngles
    //                 (0,1,2).transpose() << " Trans: " << new_pose.translation().transpose() <<
    //                 " at index:  " << curr_pose.live_id <<
    //                 std::endl;

    prev_pose = new_pose;

    // Also insert a factor for the binary pose constraint
    unsigned id1 = curr_pose.ref_id;
    unsigned id2 = curr_pose.live_id;

    Matrix m = curr_pose.cov;
    if(m.sum() == 0 || m.determinant() <= 0 || std::isnan(m.determinant())
       /*|| m.determinant() > options.cov_det_thresh*/){
      //      std::cerr << "ICP failed for rel pose between " << id1 << " and " << id2 <<
      //                   "Setting fixed covaraince..." <<
      //                   std::endl;
      Eigen::Vector6d cov_vec;
      // TODO: Improve handling of cases where the frame-to-frame ICP failed
      cov_vec << 7e-8, 7e-8, 7e-8, 8e-11, 8e-11, 8e-11;
      m = cov_vec.asDiagonal();
      numICPfailed++;
    }

    //        std::cerr <<  "Adding binary constraint between id: " << id1 << " and " <<
    //                      id2 << std::endl << "with cov: \n" << m << std::endl;

    // Create a new factor between poses
    if(options.use_identity_covariance){
      m.setIdentity();
    }

    m = m * options.rel_covariance_mult;

    Factor factor(id1, id2, rel, m);
    graph->push_back(factor);

  }

  std::cerr << std::setprecision(3) << std::fixed <<"ICP failed " << numICPfailed << " times " <<
               "out of " << relative_poses.size() << " ( " << (double)numICPfailed/(double)relative_poses.size() * 100 <<
               "% )" << std::endl;


  if( read_lcc ){
    std::cerr << "Reading LLC." << std::endl;

    int discarded_lcc = 0;
    for(size_t ii = 0; ii < loop_closure_constraints.size(); ++ii){
      RelPose curr_lcc = loop_closure_constraints[ii];
      unsigned id1 = curr_lcc.ref_id;
      unsigned id2 = curr_lcc.live_id;

      Rot3 R(curr_lcc.rel_pose[3], curr_lcc.rel_pose[4],
          curr_lcc.rel_pose[5]);
      Point3 t = curr_lcc.rel_pose.head<3>();
      Pose3 lcc(R, t);

      Matrix m = curr_lcc.cov;

      if(m.sum() == 0 ||
         m.determinant() > options.cov_det_thresh ||
         m.determinant() <= 0 ||
         std::isnan(m.determinant()))
      {
        // ICP failed or something went wrong for this loop closure, ignoring
        // The determinant of the cov. matrix may also be larger than the
        // specified threshold.
        discarded_lcc++;
        continue;
      }

      // check if the lcc is between far away poses. If so, downweight it's
      // covariance.

      //      const Pose3* lcc_0 = dynamic_cast<const Pose3*>(&initial->at(id1));
      //      const Pose3* lcc_1 = dynamic_cast<const Pose3*>(&initial->at(id2));

      //      Pose3 lcc_diff = lcc_0->compose(lcc).inverse().compose(*lcc_1);
      //            std::cerr << "distance between poses for lcc: " << ii <<
      //                         " between poses " <<  id1 << " and " << id2 << ": "
      //                      << lcc_diff.translation().norm() << std::endl;
      //      Pose3 diff = (*lcc_0).inverse().compose(*lcc_1);
      //      std::cerr << "distance between poses for lcc: " << ii <<
      //                   " between poses " <<  id1 << " and " << id2 << ": "
      //                << lcc.translation().norm() << std::endl;

      // Create a new factor between poses
      if(options.use_identity_covariance){
        m.setIdentity();
      }

      Factor lcc_factor(id1, id2, lcc, m);
      lcc_factor.isLCC = true;

      graph->push_back(lcc_factor);
      curr_lcc.ext_id = graph->size()-1;


      //      std::cerr << std::scientific <<
      //                   "Adding lcc between id: " << id1 << " and " <<
      //                    id2 << std::endl << "with cov: \n" << lcc_factor.cov << std::endl;

      //m_addedLCC[keyFromId(id2)] = curr_lcc;

      /*

      // If we already have a constraint between poses i and j, only use the one
      // with the highest degree of certainty (lowest cov. determinant)
      if(m_addedLCC.count(keyFromId(id2)) == 0){
        // LCC has not been added yet, just add
        graph->push_back(factor);
        curr_lcc.m_nExtId = graph->size()-1;
        m_addedLCC[keyFromId(id2)] = curr_lcc;
      }else{
        // Check if the covariance of the new lcc for poses i and j
        // is smaller than what we are currently using
        EstPose old_lcc = m_addedLCC[keyFromId(id2)];
        if(old_lcc.m_Cov.determinant() > curr_lcc.m_Cov.determinant()){
          // new det is smaller, replace
          curr_lcc.m_nExtId = old_lcc.m_nExtId;
          graph->replace(old_lcc.m_nExtId, factor);
          m_addedLCC[keyFromId(id2)] = curr_lcc;
//          std::cerr << "determinant for new lcc between " << id1 << " and " <<
//                       id2 << " is: " << curr_lcc.m_Cov.determinant() << " < "
//                    << old_lcc.m_Cov.determinant() << std::endl;

        }else{
          // Determinant for new constraint is larger, skip it
          continue;
        }

      }
      */

    }

    //    //ZZZZZZZZZZZZZ Temp, add wrong LCC to test switchable constraints
    //    unsigned id1 = 480;
    //    unsigned id2 = 870;
    //    Pose3& T2 = initial->at(id2);

    //    Pose3& T1 = initial->at(id1);

    //    Pose3 T12 = T1.inverse() * T2;


    //    // Add random values to the translation
    //    T12.translation()[0] += 5;
    //    T12.translation()[1] -= 2;
    //    T12.translation()[3] += 7;

    //    // Rotate the pose by an arbitrary amount
    //    Sophus::SO3d rot(0.5, 0.7, 0.1);

    //    T12.rotationMatrix() *= rot.matrix();
    //    Factor wrong_lcc(id1, id2, T12, Eigen::Matrix6d::Identity());
    //    wrong_lcc.isLCC = true;
    //    // now add the wrong LCC to the graph
    //    graph->push_back(wrong_lcc);


    std::cerr << std::setprecision(3) << std::fixed <<"Did not use " << discarded_lcc << " LCC " <<
                 "out of " << numLCC << " ( " << (double)discarded_lcc/(double)numLCC * 100 <<
                 "% )" << std::endl;

  }

  return make_pair(graph, initial);
}