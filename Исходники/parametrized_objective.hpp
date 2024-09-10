    Real value(const ROL::Vector<Real> &u,
               const ROL::Vector<Real> &z,
               Real &tol) {
        Teuchos::RCP<const Tpetra::MultiVector<> > up
            = (Teuchos::dyn_cast<const ROL::TpetraMultiVector<Real> >(u)).getVector();

        Teuchos::Array<Real> dotvalU(1, 0);
        if ( useFU_ ) {
            data_->updateF(ROL::Objective_SimOpt<Real>::getParameter());
            up->dot(*(data_->getVecF()), dotvalU.view(0,1));
        }
        else {
            Teuchos::RCP<Tpetra::MultiVector<> > matvecp
                = Teuchos::rcp(new Tpetra::MultiVector<>(*up, Teuchos::Copy));
            data_->ApplyJacobian1ToVec(matvecp, up);
            up->dot(*matvecp, dotvalU.view(0,1));
        }

        return scale_*dotvalU[0];
    }