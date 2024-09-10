IGL_INLINE void igl::fit_rotations(
  const Eigen::PlainObjectBase<DerivedS> & S,
  const bool single_precision,
  Eigen::PlainObjectBase<DerivedD> & R)
{
  using namespace std;
  const int dim = S.cols();
  const int nr = S.rows()/dim;
  assert(nr * dim == S.rows());
  assert(dim == 3);

  // resize output
  R.resize(dim,dim*nr); // hopefully no op (should be already allocated)

  //std::cout<<"S=["<<std::endl<<S<<std::endl<<"];"<<std::endl;
  //MatrixXd si(dim,dim);
  Eigen::Matrix<typename DerivedS::Scalar,3,3> si;// = Eigen::Matrix3d::Identity();
  // loop over number of rotations we're computing
  for(int r = 0;r<nr;r++)
  {
    // build this covariance matrix
    for(int i = 0;i<dim;i++)
    {
      for(int j = 0;j<dim;j++)
      {
        si(i,j) = S(i*nr+r,j);
      }
    }
    typedef Eigen::Matrix<typename DerivedD::Scalar,3,3> Mat3;
    typedef Eigen::Matrix<typename DerivedD::Scalar,3,1> Vec3;
    Mat3 ri;
    if(single_precision)
    {
      polar_svd3x3(si, ri);
    }else
    {
      Mat3 ti,ui,vi;
      Vec3 _;
      igl::polar_svd(si,ri,ti,ui,_,vi);
    }
    assert(ri.determinant() >= 0);
    R.block(0,r*dim,dim,dim) = ri.block(0,0,dim,dim).transpose();
    //cout<<matlab_format(si,C_STR("si_"<<r))<<endl;
    //cout<<matlab_format(ri.transpose().eval(),C_STR("ri_"<<r))<<endl;
  }
}