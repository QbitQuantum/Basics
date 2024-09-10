IGL_INLINE void igl::cut_mesh(
                                                                  const Eigen::PlainObjectBase<DerivedV> &V,
                                                                  const Eigen::PlainObjectBase<DerivedF> &F,
                                                                  const std::vector<std::vector<VFType> >& VF,
                                                                  const std::vector<std::vector<VFType> >& VFi,
                                                                  const Eigen::PlainObjectBase<DerivedTT>& TT,
                                                                  const Eigen::PlainObjectBase<DerivedTT>& TTi,
                                                                  const std::vector<bool> &V_border,
                                                                  const Eigen::PlainObjectBase<DerivedC> &cuts,
                                                                  Eigen::PlainObjectBase<DerivedV> &Vcut,
                                                                  Eigen::PlainObjectBase<DerivedF> &Fcut)
{
  //finding the cuts is done, now we need to actually generate a cut mesh
  igl::MeshCutterMini<DerivedV, DerivedF, VFType, DerivedTT, DerivedC> mc(V, F, TT, TTi, VF, VFi, V_border, cuts);
  mc.InitMappingSeam();

  Fcut = mc.HandleS_Index;
  //we have the faces, we need the vertices;
  int newNumV = Fcut.maxCoeff()+1;
  Vcut.setZero(newNumV,3);
  for (int vi=0; vi<V.rows(); ++vi)
    for (int i=0; i<mc.HandleV_Integer[vi].size();++i)
      Vcut.row(mc.HandleV_Integer[vi][i]) = V.row(vi);

  //ugly hack to fix some problematic cases (border vertex that is also on the boundary of the hole
  for (int fi =0; fi<Fcut.rows(); ++fi)
    for (int k=0; k<3; ++k)
      if (Fcut(fi,k)==-1)
      {
        //we need to add a vertex
        Fcut(fi,k) = newNumV;
        newNumV ++;
        Vcut.conservativeResize(newNumV, Eigen::NoChange);
        Vcut.row(newNumV-1) = V.row(F(fi,k));
      }


}