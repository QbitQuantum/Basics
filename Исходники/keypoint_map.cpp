void keypoint_map::optimize() {

	g2o::SparseOptimizer optimizer;
	optimizer.setVerbose(true);
	g2o::BlockSolver_6_3::LinearSolverType * linearSolver;

	linearSolver = new g2o::LinearSolverCholmod<
			g2o::BlockSolver_6_3::PoseMatrixType>();

	g2o::BlockSolver_6_3 * solver_ptr = new g2o::BlockSolver_6_3(linearSolver);
	g2o::OptimizationAlgorithmLevenberg* solver =
			new g2o::OptimizationAlgorithmLevenberg(solver_ptr);
	optimizer.setAlgorithm(solver);

	double focal_length = intrinsics[0];
	Eigen::Vector2d principal_point(intrinsics[2], intrinsics[3]);

	g2o::CameraParameters * cam_params = new g2o::CameraParameters(focal_length,
			principal_point, 0.);
	cam_params->setId(0);

	if (!optimizer.addParameter(cam_params)) {
		assert(false);
	}

	std::cerr << camera_positions.size() << " " << keypoints3d.size() << " "
			<< observations.size() << std::endl;

	int vertex_id = 0, point_id = 0;

	for (size_t i = 0; i < camera_positions.size(); i++) {
		Eigen::Affine3f cam_world = camera_positions[i].inverse();
		Eigen::Vector3d trans(cam_world.translation().cast<double>());
		Eigen::Quaterniond q(cam_world.rotation().cast<double>());

		g2o::SE3Quat pose(q, trans);
		g2o::VertexSE3Expmap * v_se3 = new g2o::VertexSE3Expmap();
		v_se3->setId(vertex_id);
		if (i < 1) {
			v_se3->setFixed(true);
		}
		v_se3->setEstimate(pose);
		optimizer.addVertex(v_se3);
		vertex_id++;
	}

	for (size_t i = 0; i < keypoints3d.size(); i++) {
		g2o::VertexSBAPointXYZ * v_p = new g2o::VertexSBAPointXYZ();
		v_p->setId(vertex_id + point_id);
		v_p->setMarginalized(true);
		v_p->setEstimate(keypoints3d[i].getVector3fMap().cast<double>());
		optimizer.addVertex(v_p);
		point_id++;
	}

	for (size_t i = 0; i < observations.size(); i++) {
		g2o::EdgeProjectXYZ2UV * e = new g2o::EdgeProjectXYZ2UV();
		e->setVertex(0,
				dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertices().find(
						vertex_id + observations[i].point_id)->second));
		e->setVertex(1,
				dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertices().find(
						observations[i].cam_id)->second));
		e->setMeasurement(observations[i].coord.cast<double>());
		e->information() = Eigen::Matrix2d::Identity();

		g2o::RobustKernelHuber* rk = new g2o::RobustKernelHuber;
		e->setRobustKernel(rk);

		e->setParameterId(0, 0);
		optimizer.addEdge(e);

	}

	//optimizer.save("debug.txt");

	optimizer.initializeOptimization();
	optimizer.setVerbose(true);

	std::cout << std::endl;
	std::cout << "Performing full BA:" << std::endl;
	optimizer.optimize(1);
	std::cout << std::endl;

	for (int i = 0; i < vertex_id; i++) {
		g2o::HyperGraph::VertexIDMap::iterator v_it = optimizer.vertices().find(
				i);
		if (v_it == optimizer.vertices().end()) {
			std::cerr << "Vertex " << i << " not in graph!" << std::endl;
			exit(-1);
		}

		g2o::VertexSE3Expmap * v_c =
				dynamic_cast<g2o::VertexSE3Expmap *>(v_it->second);
		if (v_c == 0) {
			std::cerr << "Vertex " << i << "is not a VertexSE3Expmap!"
					<< std::endl;
			exit(-1);
		}

		Eigen::Affine3f pos;
		pos.fromPositionOrientationScale(
				v_c->estimate().translation().cast<float>(),
				v_c->estimate().rotation().cast<float>(),
				Eigen::Vector3f(1, 1, 1));
		camera_positions[i] = pos.inverse();
	}

	for (int i = 0; i < point_id; i++) {
		g2o::HyperGraph::VertexIDMap::iterator v_it = optimizer.vertices().find(
				vertex_id + i);
		if (v_it == optimizer.vertices().end()) {
			std::cerr << "Vertex " << vertex_id + i << " not in graph!"
					<< std::endl;
			exit(-1);
		}

		g2o::VertexSBAPointXYZ * v_p =
				dynamic_cast<g2o::VertexSBAPointXYZ *>(v_it->second);
		if (v_p == 0) {
			std::cerr << "Vertex " << vertex_id + i
					<< "is not a VertexSE3Expmap!" << std::endl;
			exit(-1);
		}

		keypoints3d[i].getVector3fMap() = v_p->estimate().cast<float>();
	}

}