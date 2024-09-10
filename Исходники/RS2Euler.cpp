/** 
 * reconstruct the displacements u in Euler space with RS coordinates y
 * provided.
 * 
 * @param y the RS coordinates.
 * @param u the constructed Euler coordinates represents the displacements.
 * 
 * @return true if construction is success.
 */
bool RS2Euler::reconstruct(const VectorXd &y, VectorXd &u){

  assert (tetmesh != NULL);
  const int node_numx3 = tetmesh->nodes().size()*3;
  bool succ = true;

  // assemble the right_side
  VectorXd b;
  assemble_b(y,b);
  assert_eq(VG_t.cols(),b.size());
  assert_eq(VG_t.rows(),node_numx3);

  VectorXd right_side(node_numx3 + numFixedDofs());
  right_side.segment(0, node_numx3) = VG_t*b;
  right_side.segment(node_numx3,numFixedDofs()).setZero();
  right_side.segment(node_numx3,barycenter_uc.size()) = barycenter_uc;

  // solve A*u = right_side
  assert_eq (right_side.size(), A_solver.rows());
  u = A_solver.solve(right_side);

  // get the result 
  if(A_solver.info()!=Eigen::Success) {
	
  	succ = false;
  	u.resize(node_numx3);
  	u.setZero();
  	ERROR_LOG("failed to solve for A X = P.");
  }else{
	assert_gt(u.size(), node_numx3);
	const VectorXd x = u.head(node_numx3);
	u = x;
  }
  return succ;
}