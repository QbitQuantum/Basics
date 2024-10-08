IGL_INLINE void igl::find_cross_field_singularities(const Eigen::PlainObjectBase<DerivedV> &V,
                                                    const Eigen::PlainObjectBase<DerivedF> &F,
                                                    const Eigen::PlainObjectBase<DerivedM> &Handle_MMatch,
                                                    Eigen::PlainObjectBase<DerivedO> &isSingularity,
                                                    Eigen::PlainObjectBase<DerivedO> &singularityIndex)
{
  std::vector<bool> V_border = igl::is_border_vertex(V,F);

  std::vector<std::vector<int> > VF;
  std::vector<std::vector<int> > VFi;
  igl::vertex_triangle_adjacency(V,F,VF,VFi);


  isSingularity.setZero(V.rows(),1);
  singularityIndex.setZero(V.rows(),1);
  for (unsigned int vid=0;vid<V.rows();vid++)
  {
    ///check that is on border..
    if (V_border[vid])
      continue;

    int missmatch=0;
    for (unsigned int i=0;i<VF[vid].size();i++)
    {
      // look for the vertex
      int j=-1;
      for (unsigned z=0; z<3; ++z)
        if (F(VF[vid][i],z) == vid)
          j=z;
      assert(j!=-1);

      missmatch+=Handle_MMatch(VF[vid][i],j);
    }
    missmatch=missmatch%4;

    isSingularity(vid)=(missmatch!=0);
    singularityIndex(vid)=missmatch;
  }


}