  // In this hook, we check for the presence of a label, and if set
  // we return a failure, effectively failing the container creation.
  // Otherwise we add an environment variable to the executor and task.
  // Additionally, this hook creates a file named "foo" in the container
  // work directory (sandbox).
  Future<Option<DockerTaskExecutorPrepareInfo>>
    slavePreLaunchDockerTaskExecutorDecorator(
        const Option<TaskInfo>& taskInfo,
        const ExecutorInfo& executorInfo,
        const string& containerName,
        const string& containerWorkDirectory,
        const string& mappedSandboxDirectory,
        const Option<map<string, string>>& env) override
  {
    LOG(INFO) << "Executing 'slavePreLaunchDockerTaskExecutorDecorator' hook";

    if (taskInfo.isSome()) {
      foreach (const Label& label, taskInfo->labels().labels()) {
        if (label.key() == testErrorLabelKey) {
          return Failure("Spotted error label");
        }
      }
    }