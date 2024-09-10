void Ifpack2PreconditionerFactory<MatrixType>::initializePrec(
  const Teuchos::RCP<const LinearOpSourceBase<scalar_type> > &fwdOpSrc,
  PreconditionerBase<scalar_type> *prec,
  const ESupportSolveUse /* supportSolveUse */
  ) const
{
  // Check precondition

  TEUCHOS_ASSERT(Teuchos::nonnull(fwdOpSrc));
  TEUCHOS_ASSERT(this->isCompatible(*fwdOpSrc));
  TEUCHOS_ASSERT(prec);

  Teuchos::Time totalTimer(""), timer("");
  totalTimer.start(true);

  const Teuchos::RCP<Teuchos::FancyOStream> out = this->getOStream();
  const Teuchos::EVerbosityLevel verbLevel = this->getVerbLevel();
  Teuchos::OSTab tab(out);
  if (Teuchos::nonnull(out) && Teuchos::includesVerbLevel(verbLevel, Teuchos::VERB_MEDIUM)) {
    *out << "\nEntering Thyra::Ifpack2PreconditionerFactory::initializePrec(...) ...\n";
  }

  // Retrieve wrapped concrete Tpetra matrix from FwdOp

  const Teuchos::RCP<const LinearOpBase<scalar_type> > fwdOp = fwdOpSrc->getOp();
  TEUCHOS_TEST_FOR_EXCEPT(Teuchos::is_null(fwdOp));

  typedef typename MatrixType::local_ordinal_type local_ordinal_type;
  typedef typename MatrixType::global_ordinal_type global_ordinal_type;
  typedef typename MatrixType::node_type node_type;

  typedef Thyra::TpetraLinearOp<scalar_type, local_ordinal_type, global_ordinal_type, node_type> ThyraTpetraLinOp;
  const Teuchos::RCP<const ThyraTpetraLinOp> thyraTpetraFwdOp = Teuchos::rcp_dynamic_cast<const ThyraTpetraLinOp>(fwdOp);
  TEUCHOS_TEST_FOR_EXCEPT(Teuchos::is_null(thyraTpetraFwdOp));

  typedef Tpetra::Operator<scalar_type, local_ordinal_type, global_ordinal_type, node_type> TpetraLinOp;
  const Teuchos::RCP<const TpetraLinOp> tpetraFwdOp = thyraTpetraFwdOp->getConstTpetraOperator();
  TEUCHOS_TEST_FOR_EXCEPT(Teuchos::is_null(tpetraFwdOp));

  const Teuchos::RCP<const MatrixType> tpetraFwdMatrix = Teuchos::rcp_dynamic_cast<const MatrixType>(tpetraFwdOp);
  TEUCHOS_TEST_FOR_EXCEPT(Teuchos::is_null(tpetraFwdMatrix));

  // Retrieve concrete preconditioner object

  const Teuchos::Ptr<DefaultPreconditioner<scalar_type> > defaultPrec =
    Teuchos::ptr(dynamic_cast<DefaultPreconditioner<scalar_type> *>(prec));
  TEUCHOS_TEST_FOR_EXCEPT(Teuchos::is_null(defaultPrec));

  // Process parameter list

  Teuchos::RCP<const Teuchos::ParameterList> constParamList = paramList_;
  if (constParamList.is_null ()) {
    constParamList = getValidParameters ();
  }
  const std::string preconditionerType = Teuchos::getParameter<std::string>(*constParamList, "Prec Type");
  const Teuchos::RCP<const Teuchos::ParameterList> packageParamList = Teuchos::sublist(constParamList, "Ifpack2 Settings");

  // precTypeUpper is the upper-case version of preconditionerType.
  std::string precTypeUpper (preconditionerType);
  if (precTypeUpper.size () > 0) {
    std::locale locale;
    for (size_t k = 0; k < precTypeUpper.size (); ++k) {
      precTypeUpper[k] = std::toupper<char> (precTypeUpper[k], locale);
    }
  }
  
  // mfh 09 Nov 2013: If the Ifpack2 list doesn't already have the
  // "schwarz: overlap level" parameter, then override it with the
  // value of "Overlap".  This avoids use of the newly deprecated
  // three-argument version of Ifpack2::Factory::create() that takes
  // the overlap as an integer.
  if (constParamList->isType<int> ("Overlap") && ! packageParamList.is_null () && ! packageParamList->isType<int> ("schwarz: overlap level") &&
      precTypeUpper == "SCHWARZ") {
    const int overlap = constParamList->get<int> ("Overlap");
    Teuchos::RCP<Teuchos::ParameterList> nonconstPackageParamList =
      Teuchos::sublist (paramList_, "Ifpack2 Settings");
    nonconstPackageParamList->set ("schwarz: overlap level", overlap);
  }

  // Create the initial preconditioner

  if (Teuchos::nonnull(out) && Teuchos::includesVerbLevel(verbLevel, Teuchos::VERB_LOW)) {
    *out << "\nCreating a new Ifpack2::Preconditioner object...\n";
  }
  timer.start(true);

  typedef Ifpack2::Preconditioner<scalar_type, local_ordinal_type, global_ordinal_type, node_type> Ifpack2Prec;
  typedef Tpetra::RowMatrix<scalar_type, local_ordinal_type,
    global_ordinal_type, node_type> row_matrix_type;
  const Teuchos::RCP<Ifpack2Prec> concretePrecOp =
    Ifpack2::Factory::create<row_matrix_type> (preconditionerType, tpetraFwdMatrix);

  timer.stop();
  if (Teuchos::nonnull(out) && Teuchos::includesVerbLevel(verbLevel, Teuchos::VERB_LOW)) {
    Teuchos::OSTab(out).o() << "> Creation time = " << timer.totalElapsedTime() << " sec\n";
  }

  // Initialize and compute the initial preconditioner

  concretePrecOp->setParameters(*packageParamList);
  concretePrecOp->initialize();
  concretePrecOp->compute();

  // Wrap concrete preconditioner

  const Teuchos::RCP<LinearOpBase<scalar_type> > thyraPrecOp = Thyra::createLinearOp(Teuchos::RCP<TpetraLinOp>(concretePrecOp));
  defaultPrec->initializeUnspecified(thyraPrecOp);

  totalTimer.stop();
  if (Teuchos::nonnull(out) && Teuchos::includesVerbLevel(verbLevel, Teuchos::VERB_LOW)) {
    *out << "\nTotal time in Thyra::Ifpack2PreconditionerFactory::initializePrec(...) = " << totalTimer.totalElapsedTime() << " sec\n";
  }

  if (Teuchos::nonnull(out) && Teuchos::includesVerbLevel(verbLevel, Teuchos::VERB_MEDIUM)) {
    *out << "\nLeaving Thyra::Ifpack2PreconditionerFactory::initializePrec(...) ...\n";
  }
}