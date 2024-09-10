  Teuchos::RCP<Thyra::ModelEvaluator<ScalarT> > 
  buildModelEvaluator() const
  { 
    Teuchos::RCP<Thyra::ModelEvaluator<ScalarT> > me;
    
    std::string type = getMyParamList.get<std::string>("Model Evaluator Type");
    
    if (type == "Epetra") {
      
      Teuchos::RCP<EpetraExt::ModelEvaluator> epetraModel = 
	Teuchos::rcp(new panzer::ModelEvaluator_Epetra(fmb, linObjFactory));
    
      Teuchos::RCP<Thyra::EpetraModelEvaluator>
	epetraThyraModel = rcp(new ::Thyra::EpetraModelEvaluator());
      epetraThyraModel->initialize(epetraModel,lowsFactory);
      Teuchos::RCP< ::Thyra::ModelEvaluator<double> > thyraModel = 
	epetraThyraModel;

    }
    else if (type == "Tpetra") {
      TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, 
			 "Tpetra version not supported yet, use Epetra!");
    }
    


  }