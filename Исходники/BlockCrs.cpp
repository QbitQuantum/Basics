  void solve_system_ifpack2(
      RCP<Xpetra::Matrix<Scalar,LocalOrdinal,GlobalOrdinal,Node> > & A,
      RCP<Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> > & X,
      RCP<Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> > & B,
      const std::string & ifpack2_solver,
      Teuchos::ParameterList & Ifpack2List) {
    using Teuchos::RCP;
    using Teuchos::rcp;
    typedef Tpetra::Operator<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_Operator;
    typedef Ifpack2::Preconditioner<Scalar,LocalOrdinal,GlobalOrdinal,Node> Ifpack2_Preconditioner;
    typedef Tpetra::CrsMatrix<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_CrsMatrix;
    typedef Tpetra::RowMatrix<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_RowMatrix;
    typedef Tpetra::Experimental::BlockCrsMatrix<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_BlockCrsMatrix;
    typedef Xpetra::TpetraBlockCrsMatrix<Scalar,LocalOrdinal,GlobalOrdinal,Node> Xpetra_TpetraBlockCrsMatrix;
    typedef Tpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_Vector;
    typedef Tpetra::MultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> Tpetra_MultiVector;

    RCP<Tpetra_RowMatrix>    At = MueLu::Utilities<Scalar,LocalOrdinal,GlobalOrdinal,Node>::Op2NonConstTpetraRow(A);
    RCP<Tpetra_MultiVector> Xt = Xpetra::toTpetra(*X);
    RCP<Tpetra_MultiVector> Bt = Xpetra::toTpetra(*B);

    RCP<Ifpack2_Preconditioner> Solver = Ifpack2::Factory::create<Tpetra_RowMatrix>(ifpack2_solver,At);
    Solver->setParameters(Ifpack2List);
    Solver->initialize();
    Solver->compute();

    Solver->apply(*Bt,*Xt);
  }