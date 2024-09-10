void 
addnode(SysSPA &spa, int n, 
	// node translation
	std::vector< Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > ntrans,
	// node rotation
	std::vector< Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > nqrot,
	// constraint indices
	std::vector< Eigen::Vector2i, Eigen::aligned_allocator<Eigen::Vector2i> > cind,
	// constraint local translation 
	std::vector< Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > ctrans,
	// constraint local rotation as quaternion
	std::vector< Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > cqrot,
	// constraint covariance
	std::vector< Eigen::Matrix<double,6,6>, Eigen::aligned_allocator<Eigen::Matrix<double,6,6> > > cvar)

{
  Node nd;

  // rotation
  Quaternion<double> frq;
  frq.coeffs() = nqrot[n];
  frq.normalize();
  if (frq.w() <= 0.0) frq.coeffs() = -frq.coeffs();
  nd.qrot = frq.coeffs();

  // translation
  Vector4d v;
  v.head(3) = ntrans[n];
  v(3) = 1.0;
  nd.trans = v;
  nd.setTransform();        // set up world2node transform
  nd.setDr(true);

  // add to system
  spa.nodes.push_back(nd);

  // add in constraints
  for (int i=0; i<(int)ctrans.size(); ++i)
    {
      ConP2 con;
      con.ndr = cind[i].x();
      con.nd1 = cind[i].y();

      if ((con.ndr == n && con.nd1 <= n-1) ||
          (con.nd1 == n && con.ndr <= n-1))
        {
	  con.tmean = ctrans[i];
	  Quaternion<double> qr;
	  qr.coeffs() = cqrot[i];
	  qr.normalize();
	  con.qpmean = qr.inverse(); // inverse of the rotation measurement
	  con.prec = cvar[i];       // ??? should this be inverted ???

	  // need a boost for noise-offset system
	  //con.prec.block<3,3>(3,3) *= 10.0;
	  spa.p2cons.push_back(con);
	}
    }
}