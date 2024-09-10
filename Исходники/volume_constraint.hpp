 void applyJacobian(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v,
                    const ROL::Vector<Real> &z, Real &tol) 
 {
   Teuchos::RCP<std::vector<Real> > jvp = (Teuchos::dyn_cast<ROL::StdVector<Real> >(jv)).getVector();
   Teuchos::RCP<const Tpetra::MultiVector<> > vp = (Teuchos::dyn_cast<const ROL::TpetraMultiVector<Real> >(v)).getVector();
   Teuchos::RCP<Tpetra::MultiVector<> > unit = Teuchos::rcp(new Tpetra::MultiVector<>(vp->getMap(), 1, true));
   unit->putScalar(1.0);
   Teuchos::Array<Real> sumV(1, 0);
   vp->dot(*unit, sumV);
   (*jvp)[0] = sumV[0];  
 }