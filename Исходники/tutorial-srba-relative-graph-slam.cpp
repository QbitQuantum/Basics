int main(int argc, char**argv)
{
	my_srba_t rba;     //  Create an empty RBA problem

	// --------------------------------------------------------------------------------
	// Set parameters
	// --------------------------------------------------------------------------------
	rba.setVerbosityLevel( 1 );   // 0: None; 1:Important only; 2:Verbose

	rba.parameters.srba.use_robust_kernel = false;
	//rba.parameters.srba.optimize_new_edges_alone  = false;  // skip optimizing new edges one by one? Relative graph-slam without landmarks should be robust enough, but just to make sure we can leave this to "true" (default)

	// Information matrix for relative pose observations:
	{
		Eigen::Matrix3d ObsL;
		ObsL.setZero();
		ObsL(0,0) = 1/square(STD_NOISE_XY); // x
		ObsL(1,1) = 1/square(STD_NOISE_XY); // y
		ObsL(2,2) = 1/square(STD_NOISE_YAW); // phi

		// Set:
		rba.parameters.obs_noise.lambda = ObsL;
	}

	// =========== Topology parameters ===========
	rba.parameters.srba.edge_creation_policy = mrpt::srba::ecpICRA2013;
	rba.parameters.srba.max_tree_depth       = 3;
	rba.parameters.srba.max_optimize_depth   = 3;
	rba.parameters.srba.submap_size          = 5;
	rba.parameters.srba.min_obs_to_loop_closure = 1;
	// ===========================================

	// --------------------------------------------------------------------------------
	// Dump parameters to console (for checking/debugging only)
	// --------------------------------------------------------------------------------
	cout << "RBA parameters:\n-----------------\n";
	rba.parameters.srba.dumpToConsole();

#if MRPT_HAS_WXWIDGETS
	mrpt::gui::CDisplayWindow3D win("RBA results",640,480);
#endif

	// --------------------------------------------------------------------------------
	// Process the dataset:
	// --------------------------------------------------------------------------------
	const size_t nObs = sizeof(dataset)/sizeof(dataset[0]);
	size_t cur_kf = 0; // Start at keyframe #0 in the dataset

	for (size_t obsIdx = 0; obsIdx<nObs;  cur_kf++ /* move to next KF */  )
	{
		// Create list of observations for keyframe: "cur_kf"
		my_srba_t::new_kf_observations_t  list_obs;

		// To emulate graph-SLAM, each keyframe MUST have exactly ONE fixed "fake landmark", representing its pose:
		// ------------------------------------------------------------------------------------------------------------
		{
			my_srba_t::new_kf_observation_t obs_field;
			obs_field.is_fixed = true;
			obs_field.obs.feat_id = cur_kf; // Feature ID == keyframe ID
			obs_field.obs.obs_data.x = 0;   // Landmark values are actually ignored.
			obs_field.obs.obs_data.y = 0;
			obs_field.obs.obs_data.yaw = 0;
			list_obs.push_back( obs_field );
		}

		// The rest "observations" are real observations of relative poses:
		// -----------------------------------------------------------------
		while ( dataset[obsIdx].current_kf == cur_kf && obsIdx<nObs )
		{
			my_srba_t::new_kf_observation_t obs_field;
			obs_field.is_fixed = false;   // "Landmarks" (relative poses) have unknown relative positions (i.e. treat them as unknowns to be estimated)
			obs_field.is_unknown_with_init_val = false; // Ignored, since all observed "fake landmarks" already have an initialized value.

			obs_field.obs.feat_id      = dataset[obsIdx].observed_kf;
			obs_field.obs.obs_data.x   = dataset[obsIdx].x + mrpt::random::randomGenerator.drawGaussian1D(0,STD_NOISE_XY);
			obs_field.obs.obs_data.y   = dataset[obsIdx].y + mrpt::random::randomGenerator.drawGaussian1D(0,STD_NOISE_XY);
			obs_field.obs.obs_data.yaw = dataset[obsIdx].yaw  + mrpt::random::randomGenerator.drawGaussian1D(0,STD_NOISE_YAW);

			list_obs.push_back( obs_field );
			obsIdx++; // Next dataset entry
		}

		//  Here happens the main stuff: create Key-frames, build structures, run optimization, etc.
		//  ============================================================================================
		my_srba_t::TNewKeyFrameInfo new_kf_info;
		rba.define_new_keyframe(
			list_obs,      // Input observations for the new KF
			new_kf_info,   // Output info
			true           // Also run local optimization?
			);

		cout << "Created KF #" << new_kf_info.kf_id
			<< " | # kf-to-kf edges created:" <<  new_kf_info.created_edge_ids.size()  << endl
			<< "Optimization error: " << new_kf_info.optimize_results.total_sqr_error_init << " -> " << new_kf_info.optimize_results.total_sqr_error_final << endl
			<< "-------------------------------------------------------" << endl;

	// Display:
#if MRPT_HAS_WXWIDGETS
		// --------------------------------------------------------------------------------
		// Show 3D view of the resulting map:
		// --------------------------------------------------------------------------------
		my_srba_t::TOpenGLRepresentationOptions  opengl_options;
		mrpt::opengl::CSetOfObjectsPtr rba_3d = mrpt::opengl::CSetOfObjects::Create();

		rba.build_opengl_representation(
			new_kf_info.kf_id ,  // Root KF: the current (latest) KF
			opengl_options, // Rendering options
			rba_3d  // Output scene
			);

		{
			mrpt::opengl::COpenGLScenePtr &scene = win.get3DSceneAndLock();
			scene->clear();
			scene->insert(rba_3d);
			win.unlockAccess3DScene();
		}
		win.repaint();

		cout << "Press any key to continue.\n";
		win.waitForKey();
#endif

	} // end-for each dataset entry


	// --------------------------------------------------------------------------------
	// Saving RBA graph as a DOT file:
	// --------------------------------------------------------------------------------
	const string sFil = "graph.dot";
	cout << "Saving final graph of KFs and LMs to: " << sFil << endl;
	rba.save_graph_as_dot(sFil, true /* LMs=save */);
	cout << "Done.\n";


	return 0; // All ok
}