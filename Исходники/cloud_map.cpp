double MapOptimizer::compute_relentropy_gpu (MatrixXf & dH) const
{
  initialize_P_gpu();

  const MatrixXf & H = m_conditional;

  MatrixXf PHt = H.transpose();
  MatrixXf PtHt = PHt;

  //TODO run cusparse in two different cuda streams
  m_P->left_imul(PtHt, true);
  m_Pt->left_imul(PHt, true);

  MatrixXf HPHt(H.rows(), H.rows());
#ifdef HACK_TO_LIMIT_GPU_POWER_USAGE
  HPHt.noalias() = H * PHt;
#else // HACK_TO_LIMIT_GPU_POWER_USAGE
  Gpu::matrix_multiply(H, false, PHt, false, HPHt);
#endif // HACK_TO_LIMIT_GPU_POWER_USAGE

  const float sum_P = m_dom_flow_sum;
  const float sum_Q = m_cod_flow_sum;
  const float dQ_scale = sum_P / sum_Q;

  const MatrixSf & Q = cod_flow.joint;
  MatrixSf & dQ = m_temp_dQ;
  MatrixSf & dQt = m_temp_dQt;

  double relentropy = 0;
  for (int i = 0; i < Q.outerSize(); ++i) {
    for (MatrixSf::InnerIterator iter(Q,i); iter; ++iter) {

      const float Q_yy = iter.value();
      const float HPH_yy = HPHt(iter.row(), iter.col());
      const float dQ_yy = dQ_scale * Q_yy / HPH_yy;

      relentropy += Q_yy * log(dQ_yy);

      dQ.coeffRef(iter.row(), iter.col()) = dQ_yy;
      dQt.coeffRef(iter.col(), iter.row()) = dQ_yy;
    }
  }
  relentropy /= sum_Q;
  ASSERT_LE(0, relentropy);

  MatrixXf HP(H.rows(), H.cols());
  MatrixXf HPt(H.rows(), H.cols());

  #pragma omp sections
  {
    #pragma omp section
    HP = PtHt.transpose();

    #pragma omp section
    HPt = PHt.transpose();
  }

  //TODO run cusparse in two different cuda streams
  Gpu::SparseMultiplier(dQ).left_mul(HP, dH, true);
  Gpu::SparseMultiplier(dQt).left_fma(HPt, dH, true);

  return relentropy;
}