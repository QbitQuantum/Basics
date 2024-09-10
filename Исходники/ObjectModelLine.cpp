bool ObjectModelLine::doSamplesVerifyModel (const std::set<int> &indices, const Eigen::VectorXd &model_coefficients,
		double threshold){

	assert (model_coefficients.size () == 6);

     // Obtain the line point and direction
     Eigen::Vector4d line_pt  (model_coefficients[0], model_coefficients[1], model_coefficients[2], 0);
     Eigen::Vector4d line_dir (model_coefficients[3], model_coefficients[4], model_coefficients[5], 0);
     Eigen::Vector4d line_p2 = line_pt + line_dir;

     double sqr_threshold = threshold * threshold;
     // Iterate through the 3d points and calculate the distances from them to the line
     for (std::set<int>::iterator it = indices.begin (); it != indices.end (); ++it)
     {
       // Calculate the distance from the point to the line
       // D = ||(P2-P1) x (P1-P0)|| / ||P2-P1|| = norm (cross (p2-p1, p2-p0)) / norm(p2-p1)
       Eigen::Vector4d pt ((*inputPointCloud->getPointCloud())[*it].getX(), (*inputPointCloud->getPointCloud())[*it].getY(),
    		   (*inputPointCloud->getPointCloud())[*it].getZ(), 0);
       Eigen::Vector4d pp = line_p2 - pt;

#ifdef EIGEN3
		Eigen::Vector3d c = pp.head<3> ().cross (line_dir.head<3> ());
#else
		Eigen::Vector3d c = pp.start<3> ().cross (line_dir.start<3> ());
#endif
       double sqr_distance = c.dot (c) / line_dir.dot (line_dir);

       if (sqr_distance > sqr_threshold)
         return (false);
     }

     return (true);
}