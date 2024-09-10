void ProcessImage(std::vector<cv::Mat>& images)
{
#ifdef CHECK_NANS
    _MM_SET_EXCEPTION_MASK(_MM_GET_EXCEPTION_MASK() &
                           ~(_MM_MASK_INVALID | _MM_MASK_OVERFLOW |
                             _MM_MASK_DIV_ZERO));
#endif

    frame_count++;
//  if (poses.size() > 100) {
//    exit(EXIT_SUCCESS);
//  }

    // If this is a keyframe, set it as one on the tracker.
    prev_delta_t_ba = tracker.t_ba() * prev_t_ba.inverse();

    if (is_prev_keyframe) {
        prev_t_ba = Sophus::SE3d();
    } else {
        prev_t_ba = tracker.t_ba();
    }

    // Add a pose to the poses array
    if (is_prev_keyframe) {
        std::shared_ptr<sdtrack::TrackerPose> new_pose(new sdtrack::TrackerPose);
        if (poses.size() > 0) {
            new_pose->t_wp = poses.back()->t_wp * last_t_ba.inverse();
        }
        poses.push_back(new_pose);
        axes.push_back(std::unique_ptr<SceneGraph::GLAxis>(
                           new SceneGraph::GLAxis(0.05)));
        gui_vars.scene_graph.AddChild(axes.back().get());
    }

    if (((double)tracker.num_successful_tracks() / (double)num_features) > 0.3) {
        guess = prev_delta_t_ba * prev_t_ba;
    } else {
        guess = Sophus::SE3d();
    }

    if(guess.translation() == Eigen::Vector3d(0,0,0) &&
            poses.size() > 1) {
        guess.translation() = Eigen::Vector3d(0,0,0.001);
    }

    std::cerr << "Guess: " << guess.matrix3x4() << std::endl;

    tracker.AddImage(images, guess);
    tracker.EvaluateTrackResiduals(0, tracker.GetImagePyramid(),
                                   tracker.GetCurrentTracks());

    if (!is_manual_mode) {
        sdtrack::OptimizationOptions options;
        options.optimize_landmarks = optimize_landmarks;
        options.optimize_pose = optimize_pose;
        tracker.OptimizeTracks(options);
        tracker.PruneTracks();
    }

    if (tracker.num_successful_tracks() < 10) {
        std::cerr << "Tracking failed. using guess." << std::endl;
        tracker.set_t_ba(guess);
        poses.back()->tracks.clear();
    }

    // Update the pose t_ab based on the result from the tracker.
    UpdateCurrentPose();

    if (do_keyframing) {
        const double track_ratio = (double)tracker.num_successful_tracks() /
                                   (double)keyframe_tracks;
        const double total_trans = tracker.t_ba().translation().norm();
        const double total_rot = tracker.t_ba().so3().log().norm();

        bool keyframe_condition = track_ratio < 0.8 || total_trans > 0.2 ||
                                  total_rot > 0.1;

        std::cerr << "\tRatio: " << track_ratio << " trans: " << total_trans <<
                  " rot: " << total_rot << std::endl;

        if (keyframe_tracks != 0) {
            if (keyframe_condition) {
                is_keyframe = true;
            } else {
                is_keyframe = false;
            }
        }

        // If this is a keyframe, set it as one on the tracker.
        prev_delta_t_ba = tracker.t_ba() * prev_t_ba.inverse();

        if (is_keyframe) {
            tracker.AddKeyframe();
        }
        is_prev_keyframe = is_keyframe;
    } else {
        tracker.AddKeyframe();
    }

    std::cerr << "Num successful : " << tracker.num_successful_tracks() <<
              " keyframe tracks: " << keyframe_tracks << std::endl;

    if (!is_manual_mode) {
        BaAndStartNewLandmarks();
    }

    if (is_keyframe) {
        std::cerr << "KEYFRAME." << std::endl;
        keyframe_tracks = tracker.GetCurrentTracks().size();
        std::cerr << "New keyframe tracks: " << keyframe_tracks << std::endl;
    } else {
        std::cerr << "NOT KEYFRAME." << std::endl;
    }

    current_tracks = &tracker.GetCurrentTracks();

#ifdef CHECK_NANS
    _MM_SET_EXCEPTION_MASK(_MM_GET_EXCEPTION_MASK() |
                           (_MM_MASK_INVALID | _MM_MASK_OVERFLOW |
                            _MM_MASK_DIV_ZERO));
#endif

    std::cerr << "FRAME : " << frame_count << " KEYFRAME: " << poses.size() <<
              std::endl;
}