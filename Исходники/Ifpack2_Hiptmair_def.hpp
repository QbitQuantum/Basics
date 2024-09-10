void Hiptmair<MatrixType>::
apply (const Tpetra::MultiVector<typename MatrixType::scalar_type,
       typename MatrixType::local_ordinal_type,
       typename MatrixType::global_ordinal_type,
       typename MatrixType::node_type>& X,
       Tpetra::MultiVector<typename MatrixType::scalar_type,
                           typename MatrixType::local_ordinal_type,
                           typename MatrixType::global_ordinal_type,
                           typename MatrixType::node_type>& Y,
       Teuchos::ETransp mode,
       typename MatrixType::scalar_type alpha,
       typename MatrixType::scalar_type beta) const
{
  using Teuchos::RCP;
  using Teuchos::rcp;
  using Teuchos::rcpFromRef;
  typedef Tpetra::MultiVector<scalar_type, local_ordinal_type,
                              global_ordinal_type, node_type> MV;
  TEUCHOS_TEST_FOR_EXCEPTION(
    ! isComputed (), std::runtime_error,
    "Ifpack2::Hiptmair::apply: You must call compute() before you may call apply().");
  TEUCHOS_TEST_FOR_EXCEPTION(
    X.getNumVectors () != Y.getNumVectors (), std::invalid_argument,
    "Ifpack2::Hiptmair::apply: The MultiVector inputs X and Y do not have the "
    "same number of columns.  X.getNumVectors() = " << X.getNumVectors ()
    << " != Y.getNumVectors() = " << Y.getNumVectors () << ".");

  // Catch unimplemented cases: alpha != 1, beta != 0, mode != NO_TRANS.
  TEUCHOS_TEST_FOR_EXCEPTION(
    alpha != STS::one (), std::logic_error,
    "Ifpack2::Hiptmair::apply: alpha != 1 has not been implemented.");
  TEUCHOS_TEST_FOR_EXCEPTION(
    beta != STS::zero (), std::logic_error,
    "Ifpack2::Hiptmair::apply: zero != 0 has not been implemented.");
  TEUCHOS_TEST_FOR_EXCEPTION(
    mode != Teuchos::NO_TRANS, std::logic_error,
    "Ifpack2::Hiptmair::apply: mode != Teuchos::NO_TRANS has not been implemented.");

  Teuchos::Time timer ("apply");
  { // The body of code to time
    Teuchos::TimeMonitor timeMon (timer);

    // If X and Y are pointing to the same memory location,
    // we need to create an auxiliary vector, Xcopy
    RCP<const MV> Xcopy;
    {
      auto X_lcl_host = X.template getLocalView<Kokkos::HostSpace> ();
      auto Y_lcl_host = Y.template getLocalView<Kokkos::HostSpace> ();
      if (X_lcl_host.ptr_on_device () == Y_lcl_host.ptr_on_device ()) {
        Xcopy = rcp (new MV (X, Teuchos::Copy));
      } else {
        Xcopy = rcpFromRef (X);
      }
    }

    RCP<MV> Ycopy = rcpFromRef (Y);
    if (ZeroStartingSolution_) {
      Ycopy->putScalar (STS::zero ());
    }

    // apply Hiptmair Smoothing
    applyHiptmairSmoother (*Xcopy, *Ycopy);

  }
  ++NumApply_;
  ApplyTime_ += timer.totalElapsedTime ();
}