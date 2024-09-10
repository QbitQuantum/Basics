void results(const mat& Q, const vec& c,
	     const mat& A, const vec& b, 
	     const vec& x,
	     vec reference = vec()) {
  // std::cout << "solution: " << x.transpose() << std::endl; 

  using namespace std;
  
  const math::natural m = c.rows();
  const math::natural n = b.rows();

  cout << "violation: " << (A * x - b).cwiseMin( vec::Zero(n) ).squaredNorm() / m << endl;
  cout << "obj: " << x.dot( 0.5 * (Q * x) + c ) << endl;

  if(!reference.empty()) {
    core::log("error:", (x - reference).norm() );
  }
  
  cout << endl;

}