MatrixXf D3DCloudOrienter::orientCloud(const sensor_msgs::PointCloud& data,
				    const std::vector<int>& interest_region_indices)
{
  // -- Put cluster points into matrix form.
  MatrixXf points(interest_region_indices.size(), 3);
  for(size_t i=0; i<interest_region_indices.size(); ++i) {
    points(i, 0) = data.points[interest_region_indices[i]].x;
    points(i, 1) = data.points[interest_region_indices[i]].y;
    points(i, 2) = data.points[interest_region_indices[i]].z;
  }

  // -- Subtract off the mean of the points.
  VectorXf pt_mean = points.colwise().sum() / (float)points.rows();
  for(int i=0; i<points.rows(); ++i)
    points.row(i) -= pt_mean.transpose();

  // -- Flatten to z == 0.
  MatrixXf X = points;
  X.col(2) = VectorXf::Zero(X.rows());
  MatrixXf Xt = X.transpose();
  
  // -- Find the long axis.
  // Start with a random vector.
  VectorXf pc = VectorXf::Zero(3);
  pc(0) = 1; //Chosen by fair dice roll.
  pc(1) = 1;
  pc.normalize();
  
  // Power method.
  VectorXf prev = pc;
  double thresh = 1e-4;
  int ctr = 0;
  while(true) { 
    prev = pc;
    pc =  Xt * (X * pc);
    pc.normalize();
    ctr++;
    if((pc - prev).norm() < thresh)
      break;
  }
  assert(abs(pc(2)) < 1e-4);
  
  // -- Find the short axis.
  VectorXf shrt = VectorXf::Zero(3);
  shrt(1) = -pc(0);
  shrt(0) = pc(1);
  assert(abs(shrt.norm() - 1) < 1e-4);
  assert(abs(shrt.dot(pc)) < 1e-4);
  
  // -- Build the basis of normalized coordinates.
  MatrixXf basis = MatrixXf::Zero(3,3);
  basis.col(0) = pc;
  basis.col(1) = shrt;
  basis(2,2) = 1.0;
  assert(abs(basis.col(0).dot(basis.col(1))) < 1e-4);
  assert(abs(basis.col(0).norm() - 1) < 1e-4);
  assert(abs(basis.col(1).norm() - 1) < 1e-4);
  assert(abs(basis.col(2).norm() - 1) < 1e-4);

  // -- Rotate and return.
  MatrixXf oriented = points * basis;
  return oriented;
}