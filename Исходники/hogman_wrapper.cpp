void add_edge(GraphOptimizer3D* optimizer, int id1, int id2, tf::Transform pose,
		double sigma_position, double sigma_orientation) {
	Vector6 p;
	double roll, pitch, yaw;
	MAT_to_RPY(pose.getBasis(), roll, pitch, yaw);
	p[0] = pose.getOrigin().x();
	p[1] = pose.getOrigin().y();
	p[2] = pose.getOrigin().z();
	p[3] = roll;
	p[4] = pitch;
	p[5] = yaw;

	Matrix6 m = Matrix6::eye(1.0);
	double ip = 1 / SQR(sigma_position);
	double io = 1 / SQR(sigma_orientation);
	m[0][0] = ip;
	m[1][1] = ip;
	m[2][2] = ip;
	m[3][3] = io;
	m[4][4] = io;
	m[5][5] = io;
	GraphOptimizer3D::Vertex* v1 = optimizer->vertex(id1);
	GraphOptimizer3D::Vertex* v2 = optimizer->vertex(id2);
	if (!v1) {
		cerr << "adding edge, id1=" << id1 << " not found" << endl;
	}
	if (!v2) {
		cerr << "adding edge, id2=" << id2 << " not found" << endl;
	}
	Transformation3 t = Transformation3::fromVector(p);
	GraphOptimizer3D::Edge* e = optimizer->addEdge(v1, v2, t, m);
	if (!e) {
		cerr << "adding edge failed" << endl;
	}
}