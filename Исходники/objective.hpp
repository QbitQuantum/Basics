  Real value(const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<const Tpetra::MultiVector<> > up =
      (Teuchos::dyn_cast<const ROL::TpetraMultiVector<Real> >(u)).getVector();
    Teuchos::RCP<const Tpetra::MultiVector<> > zp =
      (Teuchos::dyn_cast<const ROL::TpetraMultiVector<Real> >(z)).getVector();

    Teuchos::Array<Real> dotvalU(1, 0);
    Teuchos::Array<Real> dotvalZ(1, 0);

    // Set difference vector diffp to up.
    Teuchos::RCP<Tpetra::MultiVector<> > diffp =
      Teuchos::rcp(new Tpetra::MultiVector<>(*up, Teuchos::Copy));
    // Temporary matvec vector.
    Teuchos::RCP<Tpetra::MultiVector<> > matvecp =
      Teuchos::rcp(new Tpetra::MultiVector<>(*up, Teuchos::Copy));

    // (u-ud)
    diffp->update(-1.0, *(data_->getVecUd()), 1.0);
    // M*(u-ud)
    data_->getMatM()->apply(*diffp, *matvecp);
    // (u-ud)'*M*(u-ud)
    diffp->dot(*matvecp, dotvalU);

    // R*z
    data_->getMatR()->apply(*zp, *matvecp);
    // z'*R*z
    zp->dot(*matvecp, dotvalZ);

    // 1/2 * (u-ud)'*M*(u-ud) + alpha/2 * z'*R*z
    return(0.5*dotvalU[0] + 0.5*alpha_*dotvalZ[0]);
  }