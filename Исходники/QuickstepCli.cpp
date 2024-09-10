int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  // Detect the hardware concurrency level.
  const std::size_t num_hw_threads =
      DefaultsConfigurator::GetNumHardwareThreads();

  // Use the command-line value if that was supplied, else use the value
  // that we computed above, provided it did return a valid value.
  // TODO(jmp): May need to change this at some point to keep one thread
  //            available for the OS if the hardware concurrency level is high.
  const unsigned int real_num_workers = quickstep::FLAGS_num_workers != 0
                                      ? quickstep::FLAGS_num_workers
                                      : (num_hw_threads != 0 ?
                                         num_hw_threads
                                         : 1);

  if (real_num_workers > 0) {
    printf("Starting Quickstep with %d worker thread(s) and a %.2f GB buffer pool\n",
           real_num_workers,
           (static_cast<double>(quickstep::FLAGS_buffer_pool_slots) * quickstep::kSlotSizeBytes)/quickstep::kAGigaByte);
  } else {
    LOG(FATAL) << "Quickstep needs at least one worker thread to run";
  }

#ifdef QUICKSTEP_HAVE_FILE_MANAGER_HDFS
  if (quickstep::FLAGS_use_hdfs) {
    LOG(INFO) << "Using HDFS as the default persistent storage, with namenode at "
              << quickstep::FLAGS_hdfs_namenode_host << ":"
              << quickstep::FLAGS_hdfs_namenode_port << " and block replication factor "
              << quickstep::FLAGS_hdfs_num_replications << "\n";
  }
#endif

  // Initialize the thread ID based map here before the Foreman and workers are
  // constructed because the initialization isn't thread safe.
  quickstep::ClientIDMap::Instance();

  MessageBusImpl bus;
  bus.Initialize();

  // The TMB client id for the main thread, used to kill workers at the end.
  const client_id main_thread_client_id = bus.Connect();
  bus.RegisterClientAsSender(main_thread_client_id, kPoisonMessage);

  // Setup the paths used by StorageManager.
  string fixed_storage_path(quickstep::FLAGS_storage_path);
  if (!fixed_storage_path.empty()
      && (fixed_storage_path.back() != quickstep::kPathSeparator)) {
    fixed_storage_path.push_back(quickstep::kPathSeparator);
  }

  string catalog_path(fixed_storage_path);
  catalog_path.append("catalog.pb.bin");
  if (quickstep::FLAGS_initialize_db) {  // Initialize the database
    // TODO(jmp): Refactor the code in this file!
    LOG(INFO) << "Initializing the database, creating a new catalog file and storage directory\n";

    // Create the directory
    // TODO(jmp): At some point, likely in C++-17, we will just have the
    //            filesystem path, and we can clean this up
#ifdef QUICKSTEP_OS_WINDOWS
    std::filesystem::create_directories(fixed_storage_path);
    LOG(FATAL) << "Failed when attempting to create the directory: " << fixed_storage_path << "\n";
    LOG(FATAL) << "Check if the directory already exists. If so, delete it or move it before initializing \n";
#else
    {
      string path_name = "mkdir " + fixed_storage_path;
      if (std::system(path_name.c_str())) {
        LOG(FATAL) << "Failed when attempting to create the directory: " << fixed_storage_path << "\n";
      }
    }
#endif

    // Create the default catalog file.
    std::ofstream catalog_file(catalog_path);
    if (!catalog_file.good()) {
      LOG(FATAL) << "ERROR: Unable to open catalog.pb.bin for writing.\n";
    }

    quickstep::Catalog catalog;
    catalog.addDatabase(new quickstep::CatalogDatabase(nullptr, "default"));

    if (!catalog.getProto().SerializeToOstream(&catalog_file)) {
      LOG(FATAL) << "ERROR: Unable to serialize catalog proto to file catalog.pb.bin\n";
      return 1;
    }

    // Close the catalog file - it will be reopened below by the QueryProcessor.
    catalog_file.close();
  }

  // Setup QueryProcessor, including CatalogDatabase and StorageManager.
  std::unique_ptr<QueryProcessor> query_processor;
  try {
    query_processor.reset(new QueryProcessor(catalog_path, fixed_storage_path));
  } catch (const std::exception &e) {
    LOG(FATAL) << "FATAL ERROR DURING STARTUP: "
               << e.what()
               << "\nIf you intended to create a new database, "
               << "please use the \"-initialize_db=true\" command line option.";
  } catch (...) {
    LOG(FATAL) << "NON-STANDARD EXCEPTION DURING STARTUP";
  }

  // Parse the CPU affinities for workers and the preloader thread, if enabled
  // to warm up the buffer pool.
  const vector<int> worker_cpu_affinities =
      InputParserUtil::ParseWorkerAffinities(real_num_workers,
                                             quickstep::FLAGS_worker_affinities);

  const std::size_t num_numa_nodes_covered =
      DefaultsConfigurator::GetNumNUMANodesCoveredByWorkers(worker_cpu_affinities);

  if (quickstep::FLAGS_preload_buffer_pool) {
    std::chrono::time_point<std::chrono::steady_clock> preload_start, preload_end;
    preload_start = std::chrono::steady_clock::now();
    printf("Preloading the buffer pool ... ");
    fflush(stdout);
    quickstep::PreloaderThread preloader(*query_processor->getDefaultDatabase(),
                                         query_processor->getStorageManager(),
                                         worker_cpu_affinities.front());

    preloader.start();
    preloader.join();
    preload_end = std::chrono::steady_clock::now();
    printf("in %g seconds\n",
           std::chrono::duration<double>(preload_end - preload_start).count());
  }

  Foreman foreman(&bus,
                  query_processor->getDefaultDatabase(),
                  query_processor->getStorageManager(),
                  num_numa_nodes_covered);

  // Get the NUMA affinities for workers.
  vector<int> cpu_numa_nodes = InputParserUtil::GetNUMANodesForCPUs();
  if (cpu_numa_nodes.empty()) {
    // libnuma is not present. Assign -1 as the NUMA node for every worker.
    cpu_numa_nodes.assign(worker_cpu_affinities.size(), -1);
  }

  vector<int> worker_numa_nodes;
  PtrVector<Worker> workers;
  vector<client_id> worker_client_ids;

  // Initialize the worker threads.
  DCHECK_EQ(static_cast<std::size_t>(real_num_workers),
            worker_cpu_affinities.size());
  for (std::size_t worker_thread_index = 0;
       worker_thread_index < worker_cpu_affinities.size();
       ++worker_thread_index) {
    int numa_node_id = -1;
    if (worker_cpu_affinities[worker_thread_index] >= 0) {
      // This worker can be NUMA affinitized.
      numa_node_id = cpu_numa_nodes[worker_cpu_affinities[worker_thread_index]];
    }
    worker_numa_nodes.push_back(numa_node_id);

    workers.push_back(
        new Worker(worker_thread_index, &bus, worker_cpu_affinities[worker_thread_index]));
    worker_client_ids.push_back(workers.back().getBusClientID());
  }

  // TODO(zuyu): Move WorkerDirectory within Shiftboss once the latter is added.
  WorkerDirectory worker_directory(worker_cpu_affinities.size(),
                                   worker_client_ids,
                                   worker_numa_nodes);

  foreman.setWorkerDirectory(&worker_directory);

  // Start the worker threads.
  for (Worker &worker : workers) {
    worker.start();
  }

  LineReaderImpl line_reader("quickstep> ",
                             "      ...> ");
  std::unique_ptr<SqlParserWrapper> parser_wrapper(new SqlParserWrapper());
  std::chrono::time_point<std::chrono::steady_clock> start, end;

  for (;;) {
    string *command_string = new string();
    *command_string = line_reader.getNextCommand();
    if (command_string->size() == 0) {
      delete command_string;
      break;
    }

    parser_wrapper->feedNextBuffer(command_string);

    bool quitting = false;
    // A parse error should reset the parser. This is because the thrown quickstep
    // SqlError does not do the proper reset work of the YYABORT macro.
    bool reset_parser = false;
    for (;;) {
      ParseResult result = parser_wrapper->getNextStatement();
      if (result.condition == ParseResult::kSuccess) {
        if (result.parsed_statement->getStatementType() == ParseStatement::kQuit) {
          quitting = true;
          break;
        }

        if (result.parsed_statement->getStatementType() == ParseStatement::kCommand) {
          try {
            quickstep::cli::executeCommand(
                *result.parsed_statement,
                *(query_processor->getDefaultDatabase()), stdout);
          } catch (const quickstep::SqlError &sql_error) {
            fprintf(stderr, "%s",
                    sql_error.formatMessage(*command_string).c_str());
            reset_parser = true;
            break;
          }
        continue;
        }

        std::unique_ptr<QueryHandle> query_handle;
        try {
          query_handle.reset(query_processor->generateQueryHandle(*result.parsed_statement));
        } catch (const quickstep::SqlError &sql_error) {
          fprintf(stderr, "%s", sql_error.formatMessage(*command_string).c_str());
          reset_parser = true;
          break;
        }

        DCHECK(query_handle->getQueryPlanMutable() != nullptr);
        foreman.setQueryPlan(query_handle->getQueryPlanMutable()->getQueryPlanDAGMutable());

        foreman.reconstructQueryContextFromProto(query_handle->getQueryContextProto());

        try {
          start = std::chrono::steady_clock::now();
          foreman.start();
          foreman.join();
          end = std::chrono::steady_clock::now();

          const CatalogRelation *query_result_relation = query_handle->getQueryResultRelation();
          if (query_result_relation) {
            PrintToScreen::PrintRelation(*query_result_relation,
                                         query_processor->getStorageManager(),
                                         stdout);

            DropRelation::Drop(*query_result_relation,
                               query_processor->getDefaultDatabase(),
                               query_processor->getStorageManager());
          }

          query_processor->saveCatalog();
          printf("Execution time: %g seconds\n",
                 std::chrono::duration<double>(end - start).count());
        } catch (const std::exception &e) {
          fprintf(stderr, "QUERY EXECUTION ERROR: %s\n", e.what());
          break;
        }
        printf("Query Complete\n");
      } else {
        if (result.condition == ParseResult::kError) {
          fprintf(stderr, "%s", result.error_message.c_str());
        }
        reset_parser = true;
        break;
      }
    }

    if (quitting) {
      break;
    } else if (reset_parser) {
      parser_wrapper.reset(new SqlParserWrapper());
      reset_parser = false;
    }
  }

  // Terminate all workers before exiting.
  // The main thread broadcasts poison message to the workers. Each worker dies
  // after receiving poison message. The order of workers' death is irrelavant.
  MessageStyle style;
  style.Broadcast(true);
  Address address;
  address.All(true);
  std::unique_ptr<WorkerMessage> poison_message(WorkerMessage::PoisonMessage());
  TaggedMessage poison_tagged_message(poison_message.get(),
                                      sizeof(*poison_message),
                                      kPoisonMessage);

  const tmb::MessageBus::SendStatus send_status =
      bus.Send(main_thread_client_id,
               address,
               style,
               std::move(poison_tagged_message));
  CHECK(send_status == tmb::MessageBus::SendStatus::kOK) <<
     "Broadcast message from Foreman to workers failed";

  for (Worker &worker : workers) {
    worker.join();
  }

  return 0;
}