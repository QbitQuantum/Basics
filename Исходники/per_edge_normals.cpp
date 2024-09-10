IGL_INLINE void igl::per_edge_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const PerEdgeNormalsWeightingType weighting,
  const Eigen::PlainObjectBase<DerivedFN>& FN,
  Eigen::PlainObjectBase<DerivedN> & N,
  Eigen::PlainObjectBase<DerivedE> & E,
  Eigen::PlainObjectBase<DerivedEMAP> & EMAP)

{
  using namespace Eigen;
  using namespace std;
  assert(F.cols() == 3 && "Faces must be triangles");
  // number of faces
  const int m = F.rows();
  // All occurances of directed edges
  MatrixXi allE;
  all_edges(F,allE);
  // Find unique undirected edges and mapping
  VectorXi _;
  unique_simplices(allE,E,_,EMAP);
  // now sort(allE,2) == E(EMAP,:), that is, if EMAP(i) = j, then E.row(j) is
  // the undirected edge corresponding to the directed edge allE.row(i).

  Eigen::VectorXd W;
  switch(weighting)
  {
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM:
      // Do nothing
      break;
    default:
      assert(false && "Unknown weighting type");
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT:
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA:
    {
      doublearea(V,F,W);
      break;
    }
  }

  N.setZero(E.rows(),3);
  for(int f = 0;f<m;f++)
  {
    for(int c = 0;c<3;c++)
    {
      if(weighting == PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM)
      {
        N.row(EMAP(f+c*m)) += FN.row(f);
      }else
      {
        N.row(EMAP(f+c*m)) += W(f) * FN.row(f);
      }
    }
  }
}