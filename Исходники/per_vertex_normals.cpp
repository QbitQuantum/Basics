IGL_INLINE void igl::per_vertex_normals(
  const Eigen::MatrixBase<DerivedV>& V,
  const Eigen::MatrixBase<DerivedF>& F,
  const igl::PerVertexNormalsWeightingType weighting,
  const Eigen::MatrixBase<DerivedFN>& FN,
  Eigen::PlainObjectBase<DerivedN> & N)
{
  using namespace std;
  // Resize for output
  N.setZero(V.rows(),3);

  Eigen::Matrix<typename DerivedN::Scalar,DerivedF::RowsAtCompileTime,3>
    W(F.rows(),3);
  switch(weighting)
  {
    case PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM:
      W.setConstant(1.);
      break;
    default:
      assert(false && "Unknown weighting type");
    case PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT:
    case PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA:
    {
      Eigen::Matrix<typename DerivedN::Scalar,DerivedF::RowsAtCompileTime,1> A;
      doublearea(V,F,A);
      W = A.replicate(1,3);
      break;
    }
    case PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE:
      internal_angles(V,F,W);
      break;
  }

  // loop over faces
  for(int i = 0;i<F.rows();i++)
  {
    // throw normal at each corner
    for(int j = 0; j < 3;j++)
    {
      N.row(F(i,j)) += W(i,j) * FN.row(i);
    }
  }

  //// loop over faces
  //std::mutex critical;
  //std::vector<DerivedN> NN;
  //parallel_for(
  //  F.rows(),
  //  [&NN,&N](const size_t n){ NN.resize(n,DerivedN::Zero(N.rows(),3));},
  //  [&F,&W,&FN,&NN,&critical](const int i, const size_t t)
  //  {
  //    // throw normal at each corner
  //    for(int j = 0; j < 3;j++)
  //    {
  //      // Q: Does this need to be critical?
  //      // A: Yes. Different (i,j)'s could produce the same F(i,j)
  //      NN[t].row(F(i,j)) += W(i,j) * FN.row(i);
  //    }
  //  },
  //  [&N,&NN](const size_t t){ N += NN[t]; },
  //  1000l);

  // take average via normalization
  N.rowwise().normalize();
}