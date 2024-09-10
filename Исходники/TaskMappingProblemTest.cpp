void test_distributed_input_adapter(int nx, int ny, int nz, Teuchos::RCP<const Teuchos::Comm<int> > global_tcomm){
  Teuchos::RCP<const Teuchos::Comm<int> > tcomm =  global_tcomm;//Teuchos::createSerialComm<int>();
  mytest_part_t numProcs = tcomm->getSize();
  Teuchos::ParameterList distributed_problemParams;
  //create mapping problem parameters
  distributed_problemParams.set("machine_coord_transformation", "EIGNORE");
  distributed_problemParams.set("mapping_algorithm", "geometric");
  distributed_problemParams.set("distributed_input_adapter", true);
  distributed_problemParams.set("mj_enable_rcb", true);
  distributed_problemParams.set("algorithm", "multijagged");
  distributed_problemParams.set("num_global_parts", numProcs);

  RCP<Zoltan2::Environment> env (new Zoltan2::Environment(distributed_problemParams, global_tcomm));
  RCP<Zoltan2::TimerManager> timer(new Zoltan2::TimerManager(global_tcomm, &std::cout, Zoltan2::MACRO_TIMERS));
  env->setTimer(timer);
  /////////////////////////CREATE DISTRIBUTED INPUT ADAPTER///////////////////////////////////////

  zscalar_t **partCenters;
  zgno_t myTasks ;
  //create tpetra input graph
  RCP<mytest_tcrsGraph_t> distributed_tpetra_graph = create_tpetra_input_matrix(nx, ny, nz, numProcs, tcomm, env, partCenters, myTasks);
  RCP<const mytest_map_t> distributed_map = distributed_tpetra_graph->getMap();
  global_tcomm->barrier();

  //create input adapter from tpetra graph
  env->timerStart(Zoltan2::MACRO_TIMERS, "AdapterCreate");
  RCP<const mytest_tcrsGraph_t> const_tpetra_graph = rcp_const_cast<const mytest_tcrsGraph_t>(distributed_tpetra_graph);
  RCP<mytest_adapter_t> ia (new mytest_adapter_t(const_tpetra_graph));

  //create multivector for coordinates and
  RCP <Zoltan2::XpetraMultiVectorAdapter<mytest_tMVector_t> > distributed_adapter = create_multi_vector_adapter(distributed_map, partCenters, myTasks);
  ia->setCoordinateInput(distributed_adapter.getRawPtr());
  env->timerStop(Zoltan2::MACRO_TIMERS, "AdapterCreate");
  global_tcomm->barrier();
  /////////////////////////DONE DISTRIBUTED INPUT ADAPTER IS CREATED///////////////////////////////////////


  //NOW we have 3 ways to create mapping problem.
  //First, run a partitioning algorithm on the input adapter. Then run task mapping at the result of this partitioning.
  //Second, run mapping algorithm directly. Mapping algorithm will assume that the tasks within the same processors
  //are in the same partition, such as they are migrated as a result of a partitioning.
  //Third, you can create your own partitioning solution without running a partitioning algorithm. This option can be used
  //to make the task mapping to perform partitioning as well. That is, create a partitioning solution where each element
  //is a part itself, then task mapping algorithm will map each of these tasks to a processor. As a result of this mapping,
  //it will perform partitioning as well.

  //FIRST CREATE A PARTITIONG PROBLEM.
  Zoltan2::PartitioningProblem<mytest_adapter_t> partitioning_problem (ia.getRawPtr(), &distributed_problemParams, global_tcomm);
  partitioning_problem.solve();
  Zoltan2::PartitioningSolution<mytest_adapter_t> partition_solution = partitioning_problem.getSolution();

  //FOR THE SECOND CASE WE DONT NEED a solution.

  //FOR the third case we create our own solution and set unique parts to each element.
  //Basically each element has its global id as part number.
  Zoltan2::PartitioningSolution<mytest_adapter_t> single_phase_mapping_solution(env, global_tcomm, 0);
  Teuchos::ArrayView< const zgno_t> gids = distributed_map->getNodeElementList();

  ArrayRCP<int> initial_part_ids(myTasks);
  for (zgno_t i = 0; i < myTasks; ++i){
    initial_part_ids[i] = gids[i];
  }
  single_phase_mapping_solution.setParts(initial_part_ids);


  env->timerStart(Zoltan2::MACRO_TIMERS, "Problem Create");
  //create mapping problem for the first case, provide the partition solution by MJ.
  Zoltan2::MappingProblem<mytest_adapter_t> distributed_map_problem_1(ia.getRawPtr(), &distributed_problemParams, global_tcomm, &partition_solution);

  //create mapping problem for the second case. We don't provide a solution in this case.
  //Mapping assumes that the elements in the current processor is attached together and are in the same part.
  Zoltan2::MappingProblem<mytest_adapter_t> distributed_map_problem_2(ia.getRawPtr(), &distributed_problemParams, global_tcomm);

  //create a mapping problem for the third case. We provide a solution in which all elements belong to unique part.
  Zoltan2::MappingProblem<mytest_adapter_t> distributed_map_problem_3(ia.getRawPtr(), &distributed_problemParams, global_tcomm, &single_phase_mapping_solution);

  env->timerStop(Zoltan2::MACRO_TIMERS, "Problem Create");
  //solve mapping problem.
  env->timerStart(Zoltan2::MACRO_TIMERS, "Problem Solve");
  distributed_map_problem_1.solve(true);
  distributed_map_problem_2.solve(true);
  distributed_map_problem_3.solve(true);
  env->timerStop(Zoltan2::MACRO_TIMERS, "Problem Solve");

  //get the solution.
  Zoltan2::MappingSolution<mytest_adapter_t> *msoln1 = distributed_map_problem_1.getSolution();
  Zoltan2::MappingSolution<mytest_adapter_t> *msoln2 = distributed_map_problem_2.getSolution();
  Zoltan2::MappingSolution<mytest_adapter_t> *msoln3 = distributed_map_problem_3.getSolution();

  timer->printAndResetToZero();

  //typedef Zoltan2::EvaluatePartition<my_adapter_t> quality_t;
  //typedef Zoltan2::EvaluatePartition<my_adapter_t> quality_t;
  typedef Zoltan2::EvaluateMapping<mytest_adapter_t> quality_t;

  RCP<quality_t> metricObject_1 = rcp(new quality_t(ia.getRawPtr(),&distributed_problemParams,global_tcomm,msoln1, distributed_map_problem_1.getMachine().getRawPtr()));
  //metricObject_1->evaluate();
  RCP<quality_t> metricObject_2 = rcp(new quality_t(ia.getRawPtr(),&distributed_problemParams,global_tcomm,msoln2, distributed_map_problem_2.getMachine().getRawPtr()));
  //metricObject_2->evaluate();
  RCP<quality_t> metricObject_3 = rcp(new quality_t(ia.getRawPtr(),&distributed_problemParams,global_tcomm,msoln3, distributed_map_problem_3.getMachine().getRawPtr()));
  //metricObject_3->evaluate();

  if (global_tcomm->getRank() == 0){
    std::cout << "METRICS FOR THE FIRST CASE - TWO PHASE MAPPING" << std::endl;
    metricObject_1->printMetrics(cout);
    std::cout << "METRICS FOR THE SECOND CASE - TWO PHASE MAPPING - INITIAL ASSIGNMENT ARE ASSUMED TO BE A PART" << std::endl;
    metricObject_2->printMetrics(cout);
    std::cout << "METRICS FOR THE THIRD CASE - ONE PHASE MAPPING - EACH ELEMENT IS ASSUMED TO BE IN UNIQUE PART AT  THE BEGINNING" << std::endl;
    metricObject_3->printMetrics(cout);
  }
}