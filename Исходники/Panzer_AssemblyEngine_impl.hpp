Teuchos::RCP<panzer::LinearObjContainer> panzer::AssemblyEngine<EvalT>::
evaluateDirichletBCs(const panzer::AssemblyEngineInArgs& in)
{
  typedef LinearObjContainer LOC;

  if(!countersInitialized_) {
    localCounter_ = m_lin_obj_factory->buildPrimitiveGhostedLinearObjContainer();
    // globalCounter_ = m_lin_obj_factory->buildPrimitiveGhostedLinearObjContainer();
    globalCounter_ = m_lin_obj_factory->buildPrimitiveLinearObjContainer();
    summedGhostedCounter_ = m_lin_obj_factory->buildPrimitiveGhostedLinearObjContainer();
    countersInitialized_ = true;
  }

  // allocate a counter to keep track of where this processor set dirichlet boundary conditions
  Teuchos::RCP<LinearObjContainer> localCounter = localCounter_;
  m_lin_obj_factory->initializeGhostedContainer(LinearObjContainer::F,*localCounter); // store counter in F
  localCounter->initialize();
     // this has only an X vector. The evaluate BCs will add a one to each row
     // that has been set as a dirichlet condition on this processor

  // apply dirichlet conditions, make sure to keep track of the local counter
  this->evaluateBCs(panzer::BCT_Dirichlet, in,localCounter);

  Teuchos::RCP<LinearObjContainer> summedGhostedCounter = summedGhostedCounter_;
  m_lin_obj_factory->initializeGhostedContainer(LinearObjContainer::F,*summedGhostedCounter); // store counter in X
  summedGhostedCounter->initialize();

  // do communication to build summed ghosted counter for dirichlet conditions
  Teuchos::RCP<LinearObjContainer> globalCounter = globalCounter_;
  {
     m_lin_obj_factory->initializeContainer(LinearObjContainer::F,*globalCounter); // store counter in X
     globalCounter->initialize();
     m_lin_obj_factory->ghostToGlobalContainer(*localCounter,*globalCounter,LOC::F);
        // Here we do the reduction across all processors so that the number of times
        // a dirichlet condition is applied is summed into the global counter

     m_lin_obj_factory->globalToGhostContainer(*globalCounter,*summedGhostedCounter,LOC::F);
        // finally we move the summed global vector into a local ghosted vector
        // so that the dirichlet conditions can be applied to both the ghosted
        // right hand side and the ghosted matrix
  }

  panzer::GlobalEvaluationDataContainer gedc;
  gedc.addDataObject("Residual Scatter Container",in.ghostedContainer_);
  in.fillGlobalEvaluationDataContainer(gedc);

  // adjust ghosted system for boundary conditions
  for(GlobalEvaluationDataContainer::iterator itr=gedc.begin();itr!=gedc.end();itr++) {
    if(itr->second->requiresDirichletAdjustment()) {
      Teuchos::RCP<LinearObjContainer> loc = Teuchos::rcp_dynamic_cast<LinearObjContainer>(itr->second);
      if(loc!=Teuchos::null) {
        m_lin_obj_factory->adjustForDirichletConditions(*localCounter,*summedGhostedCounter,*loc);
      }
      else {
        // it was not a linear object container, so if you want an adjustment it better be a GED_BCAdjustment object
        Teuchos::RCP<GlobalEvaluationData_BCAdjustment> bc_adjust = Teuchos::rcp_dynamic_cast<GlobalEvaluationData_BCAdjustment>(itr->second,true);
        bc_adjust->adjustForDirichletConditions(*localCounter,*summedGhostedCounter);
      }
    }
  }

  return globalCounter;
}