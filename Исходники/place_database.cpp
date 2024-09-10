int64_t PlaceDatabase::add(ros::Time stamp, const tf::Pose& pose_in_map, const tf::Transform& optical_transform,
                           const frame_common::Frame& frame, int64_t id)
{
  assert((int)frame.kpts.size() == frame.dtors.rows);

  // Add quantized image descriptor to document database
  vt::Document words(frame.dtors.rows);
  for (int i = 0; i < frame.dtors.rows; ++i)
    words[i] = voctree_.quantize(frame.dtors.row(i));
  vt::DocId doc_id = document_db_.insert(words);

  // Record doc id -> place id mapping
  if (id == AUTO_ID)
    id = doc_id;
  doc_to_place_id_[doc_id] = id;
  
  /// @todo Move persistent db stuff to separate function
  checkErr(sqlite3_bind_int64(insert_stmt_, 1, id), "Couldn't bind row id");
  
  // Bind time stamp encoded as 64-bit integer
  sqlite3_int64 time = stamp.toNSec();
  checkErr(sqlite3_bind_int64(insert_stmt_, 2, time), "Couldn't bind stamp");

  // Bind current map pose and camera transform
  bindTransform(pose_in_map, map_pose_param_index_);
  bindTransform(optical_transform, optical_transform_param_index_);

  // Bind camera parameters
  bindCameraParams(frame.cam);

  // Bind disparities and "good points" list
  int disp_index = disparities_param_index_;
  bindVector(insert_stmt_, disp_index, frame.disps);
  bindVector(insert_stmt_, disp_index + 1, frame.goodPts);
  
  // Bind keypoint data
  int keypt_index = keypoints_param_index_;
  checkErr(sqlite3_bind_int(insert_stmt_, keypt_index, frame.kpts.size()), "Couldn't bind num_keypoints");
  bindVector(insert_stmt_, keypt_index + 1, frame.kpts);

  // Bind descriptor data. step of cv::Mat is implicit, blob length / num keypoints.
  checkErr(sqlite3_bind_int(insert_stmt_, keypt_index + 2, frame.dtors.cols), "Couldn't bind descriptor_length");
  checkErr(sqlite3_bind_blob(insert_stmt_, keypt_index + 3, frame.dtors.data,
                             frame.dtors.rows * frame.dtors.step, SQLITE_TRANSIENT),
           "Couldn't bind descriptor data");

  // Bind document vector data
  bindVector(insert_stmt_, keypt_index + 4, words);

  // Save images if present
  bindImage(keypt_index + 5, frame.img);
  bindImage(keypt_index + 6, frame.imgRight);

  // Execute INSERT statement
  checkErr(sqlite3_step(insert_stmt_), "INSERT statement not done", SQLITE_DONE);
  
  // Reset prepared statement to reuse on next call
  checkErr(sqlite3_reset(insert_stmt_), "Couldn't reset INSERT statement");
  checkErr(sqlite3_clear_bindings(insert_stmt_), "Couldn't clear bindings on INSERT statement");

  // Return row id of newly-added place
  return id;
}