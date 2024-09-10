void 
evaluateInitialCondition(WorksetContainer & wkstContainer,
                         const std::map< std::string,Teuchos::RCP< PHX::FieldManager<panzer::Traits> > >& phx_ic_field_managers,
                         Teuchos::RCP<panzer::LinearObjContainer> loc,
                         const panzer::LinearObjFactory<panzer::Traits>& lo_factory,
                         const double time_stamp)
{
  typedef LinearObjContainer LOC;
  panzer::Traits::PreEvalData ped;

  // allocate a ghosted container for the initial condition
  Teuchos::RCP<LOC> ghostedloc = lo_factory.buildGhostedLinearObjContainer();
  lo_factory.initializeGhostedContainer(LOC::X,*ghostedloc);

  // allocate a counter to keep track of where this processor set initial conditions
  Teuchos::RCP<LOC> localCounter = lo_factory.buildPrimitiveGhostedLinearObjContainer();
  Teuchos::RCP<LOC> globalCounter = lo_factory.buildPrimitiveLinearObjContainer();
  Teuchos::RCP<LOC> summedGhostedCounter = lo_factory.buildPrimitiveGhostedLinearObjContainer();

  lo_factory.initializeGhostedContainer(LOC::F,*localCounter); // store counter in F
  localCounter->initialize();

  ped.gedc.addDataObject("Residual Scatter Container",ghostedloc);
  ped.gedc.addDataObject("Dirichlet Counter",localCounter);
  ped.first_sensitivities_name = "";

  for(std::map< std::string,Teuchos::RCP< PHX::FieldManager<panzer::Traits> > >::const_iterator itr=phx_ic_field_managers.begin();
      itr!=phx_ic_field_managers.end();++itr) {
    std::string blockId = itr->first;
    Teuchos::RCP< PHX::FieldManager<panzer::Traits> > fm = itr->second;

    fm->preEvaluate<panzer::Traits::Residual>(ped);

    // Loop over worksets in this element block
    std::vector<panzer::Workset>& w = *wkstContainer.getVolumeWorksets(blockId);
    for (std::size_t i = 0; i < w.size(); ++i) {
      panzer::Workset& workset = w[i];
      
      // Need to figure out how to get restart time from Rythmos.
      workset.time = time_stamp;
      
      fm->evaluateFields<panzer::Traits::Residual>(workset);
    }
  }

  lo_factory.initializeGhostedContainer(LOC::F,*summedGhostedCounter); // store counter in F
  summedGhostedCounter->initialize();

  // do communication to build summed ghosted counter for dirichlet conditions
  {
    lo_factory.initializeContainer(LOC::F,*globalCounter); // store counter in F
    globalCounter->initialize();
    lo_factory.ghostToGlobalContainer(*localCounter,*globalCounter,LOC::F);
        // Here we do the reduction across all processors so that the number of times
        // a dirichlet condition is applied is summed into the global counter

   lo_factory.globalToGhostContainer(*globalCounter,*summedGhostedCounter,LOC::F);
        // finally we move the summed global vector into a local ghosted vector
        // so that the dirichlet conditions can be applied to both the ghosted
        // right hand side and the ghosted matrix
  }

  panzer::GlobalEvaluationDataContainer gedc;
  gedc.addDataObject("Residual Scatter Container",ghostedloc);

  // adjust ghosted system for boundary conditions
  for(GlobalEvaluationDataContainer::iterator itr=gedc.begin();itr!=gedc.end();itr++) {
    Teuchos::RCP<LOC> loc2 = Teuchos::rcp_dynamic_cast<LOC>(itr->second);
    if(loc2!=Teuchos::null) {
      bool zeroVectorRows = false;
      bool adjustX = true;
      lo_factory.adjustForDirichletConditions(*localCounter,*summedGhostedCounter,*loc2, zeroVectorRows, adjustX);
    }
  }

  // gather the ghosted solution back into the global container, which performs the sum
  lo_factory.ghostToGlobalContainer(*ghostedloc,*loc,LOC::X);
}