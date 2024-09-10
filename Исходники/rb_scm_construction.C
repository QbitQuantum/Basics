Number RBSCMConstruction::Aq_inner_product(unsigned int q,
                                           const NumericVector<Number>& v,
                                           const NumericVector<Number>& w)
{
  if(q >= get_rb_theta_expansion().get_n_A_terms())
    libmesh_error_msg("Error: We must have q < Q_a in Aq_inner_product.");

  matrix_A->zero();
  add_scaled_symm_Aq(q, 1.);
  matrix_A->vector_mult(*inner_product_storage_vector, w);

  return v.dot(*inner_product_storage_vector);
}