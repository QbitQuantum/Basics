MatrixNonsing::mat_mns_mut_ptr_t
DirectSparseSolverImp::BasisMatrixImp::clone_mns()
{
  namespace rcp = MemMngPack;
  Teuchos::RCP<BasisMatrixImp> bm = this->create_matrix();
  // A shallow copy is okay if the educated client DirectSparseSolverImp is careful!
  bm->initialize(dim_,fact_struc_,fact_nonzeros_);
  return bm;
}