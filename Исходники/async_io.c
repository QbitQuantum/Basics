static int
addFunctionMonitor (void *item, void *data) {
  const FunctionEntry *function = item;
  MonitorGroup *monitors = data;
  OperationEntry *operation = getActiveOperation(function);

  if (operation) {
    operation->monitor = NULL;

    if (!operation->active) {
      if (operation->finished) return 1;

      operation->monitor = &monitors->array[monitors->count++];
      initializeMonitor(operation->monitor, function, operation);
    }
  }

  return 0;
}