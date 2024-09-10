IGL_INLINE void igl::polyvector_field_singularities_from_matchings(
                                                                   const Eigen::PlainObjectBase<DerivedV> &V,
                                                                   const Eigen::PlainObjectBase<DerivedF> &F,
                                                                   const std::vector<bool> &V_border,
                                                                   const std::vector<std::vector<VFType> > &VF,
                                                                   const Eigen::MatrixXi &TT,
                                                                   const Eigen::MatrixXi &E2F,
                                                                   const Eigen::MatrixXi &F2E,
                                                                   const Eigen::PlainObjectBase<DerivedM> &match_ab,
                                                                   const Eigen::PlainObjectBase<DerivedM> &match_ba,
                                                                   Eigen::PlainObjectBase<DerivedS> &singularities,
                                                                   Eigen::PlainObjectBase<DerivedS> &singularity_indices)
{
  igl::polyvector_field_singularities_from_matchings(V, F, V_border, VF, TT, E2F, F2E, match_ab, match_ba, singularities);

  singularity_indices.setZero(singularities.size(), 1);

  //get index from first vector only
  int vector_to_match = 0;
  for (int i =0; i<singularities.size(); ++i)
  {
    int vi = singularities[i];

    // Eigen::VectorXi mvi,fi;
    // igl::polyvector_field_one_ring_matchings(V, F, VF, E2F, F2E, TT, match_ab, match_ba, vi, vector_to_match, mvi, fi);
    Eigen::VectorXi fi;
    Eigen::MatrixXi mvi;
    igl::polyvector_field_one_ring_matchings(V, F, VF, E2F, F2E, TT, match_ab, match_ba, vi, mvi, fi);

    singularity_indices[i] = (mvi(mvi.rows()-1,vector_to_match) - vector_to_match);
  }

}