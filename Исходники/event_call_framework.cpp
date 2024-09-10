  void resourceOffers(const vector<Offer>& offers)
  {
    foreach (const Offer& offer, offers) {
      cout << "Received offer " << offer.id() << " with "
           << Resources(offer.resources())
           << endl;

      static const Resources TASK_RESOURCES = Resources::parse(
          "cpus:" + stringify(CPUS_PER_TASK) +
          ";mem:" + stringify(MEM_PER_TASK)).get();

      Resources remaining = offer.resources();

      // Launch tasks.
      vector<TaskInfo> tasks;
      while (tasksLaunched < totalTasks &&
             remaining.flatten().contains(TASK_RESOURCES)) {
        int taskId = tasksLaunched++;

        cout << "Launching task " << taskId << " using offer "
             << offer.id() << endl;

        TaskInfo task;
        task.set_name("Task " + lexical_cast<string>(taskId));
        task.mutable_task_id()->set_value(
            lexical_cast<string>(taskId));
        task.mutable_agent_id()->MergeFrom(offer.agent_id());
        task.mutable_executor()->MergeFrom(executor);

        Option<Resources> resources =
          remaining.find(TASK_RESOURCES.flatten(framework.role()));

        CHECK_SOME(resources);

        task.mutable_resources()->CopyFrom(resources.get());

        remaining -= resources.get();

        tasks.push_back(task);
      }

      Call call;
      CHECK(framework.has_id());
      call.mutable_framework_id()->CopyFrom(framework.id());
      call.set_type(Call::ACCEPT);

      Call::Accept* accept = call.mutable_accept();
      accept->add_offer_ids()->CopyFrom(offer.id());

      Offer::Operation* operation = accept->add_operations();
      operation->set_type(Offer::Operation::LAUNCH);
      foreach (const TaskInfo& taskInfo, tasks) {
        operation->mutable_launch()->add_task_infos()->CopyFrom(taskInfo);
      }