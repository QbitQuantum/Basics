  TEUCHOS_UNIT_TEST(block_assembly, scatter_dirichlet_residual)
  {
    PHX::KokkosDeviceSession session;

#ifdef HAVE_MPI
    Teuchos::RCP<Epetra_Comm> eComm = Teuchos::rcp(new Epetra_MpiComm(MPI_COMM_WORLD));
#else
    Teuchos::RCP<Epetra_Comm> eComm = Teuchos::rcp(new Epetra_SerialComm());
#endif

    int myRank = eComm->MyPID();

    const std::size_t workset_size = 4;
    const std::string fieldName1_q1 = "U";
    const std::string fieldName2_q1 = "V";
    const std::string fieldName_qedge1 = "B";

    Teuchos::RCP<panzer_stk_classic::STK_Interface> mesh = buildMesh(2,2);

    // build input physics block
    Teuchos::RCP<panzer::PureBasis> basis_q1 = buildBasis(workset_size,"Q1");
    Teuchos::RCP<panzer::PureBasis> basis_qedge1 = buildBasis(workset_size,"QEdge1");

    Teuchos::RCP<Teuchos::ParameterList> ipb = Teuchos::parameterList();
    testInitialization(ipb);

    const int default_int_order = 1;
    std::string eBlockID = "eblock-0_0";    
    Teuchos::RCP<user_app::MyFactory> eqset_factory = Teuchos::rcp(new user_app::MyFactory);
    panzer::CellData cellData(workset_size,mesh->getCellTopology("eblock-0_0"));
    Teuchos::RCP<panzer::GlobalData> gd = panzer::createGlobalData();
    Teuchos::RCP<panzer::PhysicsBlock> physicsBlock = 
      Teuchos::rcp(new PhysicsBlock(ipb,eBlockID,default_int_order,cellData,eqset_factory,gd,false));

    Teuchos::RCP<std::vector<panzer::Workset> > work_sets = panzer_stk_classic::buildWorksets(*mesh,*physicsBlock); 
    TEST_EQUALITY(work_sets->size(),1);

    // build connection manager and field manager
    const Teuchos::RCP<panzer::ConnManager<int,int> > conn_manager = Teuchos::rcp(new panzer_stk_classic::STKConnManager<int>(mesh));
    RCP<panzer::BlockedDOFManager<int,int> > dofManager = Teuchos::rcp(new panzer::BlockedDOFManager<int,int>(conn_manager,MPI_COMM_WORLD));

    dofManager->addField(fieldName1_q1,Teuchos::rcp(new panzer::IntrepidFieldPattern(basis_q1->getIntrepidBasis())));
    dofManager->addField(fieldName2_q1,Teuchos::rcp(new panzer::IntrepidFieldPattern(basis_q1->getIntrepidBasis())));
    dofManager->addField(fieldName_qedge1,Teuchos::rcp(new panzer::IntrepidFieldPattern(basis_qedge1->getIntrepidBasis())));

    std::vector<std::vector<std::string> > fieldOrder(3);
    fieldOrder[0].push_back(fieldName1_q1);
    fieldOrder[1].push_back(fieldName_qedge1);
    fieldOrder[2].push_back(fieldName2_q1);
    dofManager->setFieldOrder(fieldOrder);

    // dofManager->setOrientationsRequired(true);
    dofManager->buildGlobalUnknowns();

    // setup linear object factory
    /////////////////////////////////////////////////////////////

    Teuchos::RCP<BlockedEpetraLinearObjFactory<panzer::Traits,int> > be_lof 
       = Teuchos::rcp(new BlockedEpetraLinearObjFactory<panzer::Traits,int>(eComm.getConst(),dofManager));
    Teuchos::RCP<LinearObjFactory<panzer::Traits> > lof = be_lof;
    Teuchos::RCP<LinearObjContainer> dd_loc = be_lof->buildGhostedLinearObjContainer();
    Teuchos::RCP<LinearObjContainer> loc = be_lof->buildGhostedLinearObjContainer();
    be_lof->initializeGhostedContainer(LinearObjContainer::F,*dd_loc);
    dd_loc->initialize();

    be_lof->initializeGhostedContainer(LinearObjContainer::X | LinearObjContainer::F,*loc);
    loc->initialize();

    Teuchos::RCP<BlockedEpetraLinearObjContainer> b_dd_loc = Teuchos::rcp_dynamic_cast<BlockedEpetraLinearObjContainer>(dd_loc);
    Teuchos::RCP<BlockedEpetraLinearObjContainer> b_loc = Teuchos::rcp_dynamic_cast<BlockedEpetraLinearObjContainer>(loc);
    Teuchos::RCP<Thyra::ProductVectorBase<double> > p_vec = Teuchos::rcp_dynamic_cast<Thyra::ProductVectorBase<double> >(b_loc->get_x());
    Thyra::assign(p_vec->getNonconstVectorBlock(0).ptr(),123.0+myRank);
    Thyra::assign(p_vec->getNonconstVectorBlock(1).ptr(),456.0+myRank);
    Thyra::assign(p_vec->getNonconstVectorBlock(2).ptr(),789.0+myRank);

    // setup field manager, add evaluator under test
    /////////////////////////////////////////////////////////////
 
    PHX::FieldManager<panzer::Traits> fm;

    std::string resName = "";
    Teuchos::RCP<std::map<std::string,std::string> > names_map =
       Teuchos::rcp(new std::map<std::string,std::string>);
    names_map->insert(std::make_pair(fieldName1_q1,resName+fieldName1_q1));
    names_map->insert(std::make_pair(fieldName2_q1,resName+fieldName2_q1));
    names_map->insert(std::make_pair(fieldName_qedge1,resName+fieldName_qedge1));

    // evaluators under test
    {
       using Teuchos::RCP;
       using Teuchos::rcp;
       RCP<std::vector<std::string> > names = rcp(new std::vector<std::string>);
       names->push_back(resName+fieldName1_q1);
       names->push_back(resName+fieldName2_q1);

       Teuchos::ParameterList pl; 
       pl.set("Scatter Name", "ScatterQ1");
       pl.set("Basis", basis_q1);
       pl.set("Dependent Names", names);
       pl.set("Dependent Map", names_map);
       pl.set("Side Subcell Dimension", 1);
       pl.set("Local Side ID", 2);
       pl.set("Check Apply BC", false);

       Teuchos::RCP<PHX::Evaluator<panzer::Traits> > evaluator = lof->buildScatterDirichlet<panzer::Traits::Residual>(pl);

       TEST_EQUALITY(evaluator->evaluatedFields().size(),1);

       fm.registerEvaluator<panzer::Traits::Residual>(evaluator);
       fm.requireField<panzer::Traits::Residual>(*evaluator->evaluatedFields()[0]);
    }
    {
       using Teuchos::RCP;
       using Teuchos::rcp;
       RCP<std::vector<std::string> > names = rcp(new std::vector<std::string>);
       names->push_back(resName+fieldName_qedge1);

       Teuchos::ParameterList pl; 
       pl.set("Scatter Name", "ScatterQEdge1");
       pl.set("Basis", basis_qedge1);
       pl.set("Dependent Names", names);
       pl.set("Dependent Map", names_map);
       pl.set("Side Subcell Dimension", 1);
       pl.set("Local Side ID", 2);
       pl.set("Check Apply BC", false);

       Teuchos::RCP<PHX::Evaluator<panzer::Traits> > evaluator = lof->buildScatterDirichlet<panzer::Traits::Residual>(pl);

       TEST_EQUALITY(evaluator->evaluatedFields().size(),1);

       fm.registerEvaluator<panzer::Traits::Residual>(evaluator);
       fm.requireField<panzer::Traits::Residual>(*evaluator->evaluatedFields()[0]);
    }

    // support evaluators
    {
       using Teuchos::RCP;
       using Teuchos::rcp;
       RCP<std::vector<std::string> > names = rcp(new std::vector<std::string>);
       names->push_back(fieldName1_q1);
       names->push_back(fieldName2_q1);

       Teuchos::ParameterList pl; 
       pl.set("Basis", basis_q1);
       pl.set("DOF Names",names);
       pl.set("Indexer Names",names);

       Teuchos::RCP<PHX::Evaluator<panzer::Traits> > evaluator = lof->buildGather<panzer::Traits::Residual>(pl);

       fm.registerEvaluator<panzer::Traits::Residual>(evaluator);
    }
    {
       using Teuchos::RCP;
       using Teuchos::rcp;
       RCP<std::vector<std::string> > names = rcp(new std::vector<std::string>);
       names->push_back(fieldName_qedge1);

       Teuchos::ParameterList pl; 
       pl.set("Basis", basis_qedge1);
       pl.set("DOF Names",names);
       pl.set("Indexer Names",names);

       Teuchos::RCP<PHX::Evaluator<panzer::Traits> > evaluator = lof->buildGather<panzer::Traits::Residual>(pl);

       fm.registerEvaluator<panzer::Traits::Residual>(evaluator);
    }

    std::vector<PHX::index_size_type> derivative_dimensions;
    derivative_dimensions.push_back(12);
    fm.setKokkosExtendedDataTypeDimensions<panzer::Traits::Jacobian>(derivative_dimensions);

    panzer::Traits::SetupData sd;
    fm.postRegistrationSetup(sd);

    // panzer::Traits::PED ped;
    // ped.dirichletData.ghostedCounter = dd_loc;
    // fm.preEvaluate<panzer::Traits::Residual>(ped);
    panzer::Traits::PreEvalData ped;
    ped.gedc.addDataObject("Dirichlet Counter",dd_loc);
    ped.gedc.addDataObject("Solution Gather Container",loc);
    ped.gedc.addDataObject("Residual Scatter Container",loc);
    fm.preEvaluate<panzer::Traits::Residual>(ped);


    // run tests
    /////////////////////////////////////////////////////////////

    panzer::Workset & workset = (*work_sets)[0];
    workset.alpha = 0.0;
    workset.beta = 2.0; // derivatives multiplied by 2
    workset.time = 0.0;
    workset.evaluate_transient_terms = false;

    fm.evaluateFields<panzer::Traits::Residual>(workset);

    // test Residual fields
    std::size_t dd_count = 0;
    Teuchos::ArrayRCP<const double> data, dd_data;
    Teuchos::RCP<const Thyra::ProductVectorBase<double> > f_vec = Teuchos::rcp_dynamic_cast<Thyra::ProductVectorBase<double> >(b_loc->get_f());
    Teuchos::RCP<const Thyra::ProductVectorBase<double> > dd_vec = Teuchos::rcp_dynamic_cast<Thyra::ProductVectorBase<double> >(b_dd_loc->get_f());

    // check all the residual values. This is kind of crappy test since it simply checks twice the target
    // value and the target. Its this way because you add two entries across elements.

    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(f_vec->getVectorBlock(0))->getLocalData(Teuchos::ptrFromRef(data));
    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(dd_vec->getVectorBlock(0))->getLocalData(Teuchos::ptrFromRef(dd_data));
    TEST_EQUALITY(data.size(),b_loc->getMapForBlock(0)->NumMyElements());
    TEST_EQUALITY(data.size(),dd_data.size());
    dd_count = 0;
    for(int i=0;i<data.size();i++) {
 
       double target = 123.0+myRank;
       if(dd_data[i]==0.0)
       {  TEST_EQUALITY(data[i],0.0); }
       else
       {  TEST_EQUALITY(data[i],target); dd_count++; }
    }
    TEST_EQUALITY(dd_count,2*workset.num_cells); // there are 2 nodes on the side and the sides are not shared

    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(f_vec->getVectorBlock(1))->getLocalData(Teuchos::ptrFromRef(data));
    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(dd_vec->getVectorBlock(1))->getLocalData(Teuchos::ptrFromRef(dd_data));
    TEST_EQUALITY(data.size(),b_loc->getMapForBlock(1)->NumMyElements());
    TEST_EQUALITY(data.size(),dd_data.size());
    dd_count = 0;
    for(int i=0;i<data.size();i++) {
 
       double target = 456.0+myRank;
       if(dd_data[i]==0.0)
       {  TEST_EQUALITY(data[i],0.0); }
       else
       {  TEST_EQUALITY(data[i],target); dd_count++; }
    }
    TEST_EQUALITY(dd_count,workset.num_cells); // there are 2 nodes on the side and the sides are not shared

    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(f_vec->getVectorBlock(2))->getLocalData(Teuchos::ptrFromRef(data));
    Teuchos::rcp_dynamic_cast<const Thyra::SpmdVectorBase<double> >(dd_vec->getVectorBlock(2))->getLocalData(Teuchos::ptrFromRef(dd_data));
    TEST_EQUALITY(data.size(),b_loc->getMapForBlock(2)->NumMyElements());
    TEST_EQUALITY(data.size(),dd_data.size());
    dd_count = 0;
    for(int i=0;i<data.size();i++) {
 
       double target = 789.0+myRank;
       if(dd_data[i]==0.0)
       {  TEST_EQUALITY(data[i],0.0); }
       else
       {  TEST_EQUALITY(data[i],target); dd_count++; }
    }
    TEST_EQUALITY(dd_count,2*workset.num_cells); // there are 2 nodes on the side and the sides are not shared

  }