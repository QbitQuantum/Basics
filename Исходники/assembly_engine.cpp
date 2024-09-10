  TEUCHOS_UNIT_TEST(assembly_engine, basic_tpetra)
  {
    using Teuchos::RCP;

    PHX::InitializeKokkosDevice();

    // build global communicator
    Teuchos::RCP<Teuchos::Comm<int> > comm = Teuchos::rcp(new Teuchos::MpiComm<int>(Teuchos::opaqueWrapper(MPI_COMM_WORLD)));
  
    RCP<Teuchos::ParameterList> pl = rcp(new Teuchos::ParameterList);
    pl->set("X Blocks",2);
    pl->set("Y Blocks",1);
    pl->set("X Elements",6);
    pl->set("Y Elements",4);
    
    panzer_stk_classic::SquareQuadMeshFactory factory;
    factory.setParameterList(pl);
    RCP<panzer_stk_classic::STK_Interface> mesh = factory.buildMesh(MPI_COMM_WORLD);

    Teuchos::RCP<Teuchos::ParameterList> ipb = Teuchos::parameterList("Physics Blocks");
    std::vector<panzer::BC> bcs;
    testInitialzation(ipb, bcs);

    Teuchos::RCP<panzer::FieldManagerBuilder> fmb = 
      Teuchos::rcp(new panzer::FieldManagerBuilder);

    // build physics blocks
    //////////////////////////////////////////////////////////////
    const std::size_t workset_size = 20;
    Teuchos::RCP<user_app::MyFactory> eqset_factory = Teuchos::rcp(new user_app::MyFactory);
    user_app::BCFactory bc_factory;
    std::vector<Teuchos::RCP<panzer::PhysicsBlock> > physicsBlocks;
    {
      const int default_integration_order = 1;

      std::map<std::string,std::string> block_ids_to_physics_ids;
      block_ids_to_physics_ids["eblock-0_0"] = "test physics";
      block_ids_to_physics_ids["eblock-1_0"] = "test physics";

      std::map<std::string,Teuchos::RCP<const shards::CellTopology> > block_ids_to_cell_topo;
      block_ids_to_cell_topo["eblock-0_0"] = mesh->getCellTopology("eblock-0_0");
      block_ids_to_cell_topo["eblock-1_0"] = mesh->getCellTopology("eblock-1_0");
      
      Teuchos::RCP<panzer::GlobalData> gd = panzer::createGlobalData();

      panzer::buildPhysicsBlocks(block_ids_to_physics_ids,
				 block_ids_to_cell_topo,
				 ipb,
				 default_integration_order,
				 workset_size,
				 eqset_factory,
				 gd,
				 false,
				 physicsBlocks);
    }

    // build worksets
    //////////////////////////////////////////////////////////////
    Teuchos::RCP<panzer_stk_classic::WorksetFactory> wkstFactory
       = Teuchos::rcp(new panzer_stk_classic::WorksetFactory(mesh)); // build STK workset factory
    Teuchos::RCP<panzer::WorksetContainer> wkstContainer     // attach it to a workset container (uses lazy evaluation)
       = Teuchos::rcp(new panzer::WorksetContainer(wkstFactory,physicsBlocks,workset_size));

    // build DOF Manager
    /////////////////////////////////////////////////////////////

    // build the connection manager 
    const Teuchos::RCP<panzer::ConnManager<int,panzer::Ordinal64> > 
      conn_manager = Teuchos::rcp(new panzer_stk_classic::STKConnManager<panzer::Ordinal64>(mesh));

    panzer::DOFManagerFactory<int,panzer::Ordinal64> globalIndexerFactory;
    RCP<panzer::UniqueGlobalIndexer<int,panzer::Ordinal64> > dofManager 
         = globalIndexerFactory.buildUniqueGlobalIndexer(Teuchos::opaqueWrapper(MPI_COMM_WORLD),physicsBlocks,conn_manager);
 
    Teuchos::RCP<panzer::LinearObjFactory<panzer::Traits> > linObjFactory 
          = Teuchos::rcp(new panzer::TpetraLinearObjFactory<panzer::Traits,double,int,panzer::Ordinal64>(comm,dofManager));

    // setup field manager build
    /////////////////////////////////////////////////////////////
 
    // Add in the application specific closure model factory
    panzer::ClosureModelFactory_TemplateManager<panzer::Traits> cm_factory;
    user_app::MyModelFactory_TemplateBuilder cm_builder;
    cm_factory.buildObjects(cm_builder);

    Teuchos::ParameterList closure_models("Closure Models");
    closure_models.sublist("solid").sublist("SOURCE_TEMPERATURE").set<double>("Value",1.0);
    closure_models.sublist("ion solid").sublist("SOURCE_ION_TEMPERATURE").set<double>("Value",1.0);

    Teuchos::ParameterList user_data("User Data");

    fmb->setWorksetContainer(wkstContainer);
    fmb->setupVolumeFieldManagers(physicsBlocks,cm_factory,closure_models,*linObjFactory,user_data);
    fmb->setupBCFieldManagers(bcs,physicsBlocks,*eqset_factory,cm_factory,bc_factory,closure_models,*linObjFactory,user_data);

    panzer::AssemblyEngine_TemplateManager<panzer::Traits> ae_tm;
    panzer::AssemblyEngine_TemplateBuilder builder(fmb,linObjFactory);
    ae_tm.buildObjects(builder);

    RCP<panzer::LinearObjContainer> tGhosted = linObjFactory->buildGhostedLinearObjContainer();
    RCP<panzer::LinearObjContainer> tGlobal = linObjFactory->buildLinearObjContainer();
    linObjFactory->initializeGhostedContainer(panzer::LinearObjContainer::X |
                                              panzer::LinearObjContainer::DxDt |
                                              panzer::LinearObjContainer::F |
                                              panzer::LinearObjContainer::Mat,*tGhosted);
    linObjFactory->initializeContainer(panzer::EpetraLinearObjContainer::X |
                                       panzer::EpetraLinearObjContainer::DxDt |
                                       panzer::EpetraLinearObjContainer::F |
                                       panzer::EpetraLinearObjContainer::Mat,*tGlobal);

    // panzer::pauseToAttach();
    tGhosted->initialize();
    tGlobal->initialize();

    panzer::AssemblyEngineInArgs input(tGhosted,tGlobal);
    input.alpha = 0.0;
    input.beta = 1.0;

    ae_tm.getAsObject<panzer::Traits::Residual>()->evaluate(input);
    ae_tm.getAsObject<panzer::Traits::Jacobian>()->evaluate(input);

    RCP<panzer::TpetraLinearObjContainer<double,int,panzer::Ordinal64> > globalCont 
       = Teuchos::rcp_dynamic_cast<panzer::TpetraLinearObjContainer<double,int,panzer::Ordinal64> >(tGlobal);

    Teuchos::RCP<const Tpetra::Operator<double,int,panzer::Ordinal64> > baseOp = globalCont->get_A();
    Teuchos::RCP<const Thyra::VectorSpaceBase<double> > rangeSpace = Thyra::createVectorSpace<double>(baseOp->getRangeMap());
    Teuchos::RCP<const Thyra::VectorSpaceBase<double> > domainSpace = Thyra::createVectorSpace<double>(baseOp->getDomainMap());

    tLinearOp = Thyra::constTpetraLinearOp<double,int,panzer::Ordinal64>(rangeSpace, domainSpace, baseOp);
    tVector = Thyra::constTpetraVector<double,int,panzer::Ordinal64>(Thyra::tpetraVectorSpace<double,int,panzer::Ordinal64>(baseOp->getRangeMap()).getConst(),
                                                       globalCont->get_f().getConst());

    PHX::FinalizeKokkosDevice();
  }