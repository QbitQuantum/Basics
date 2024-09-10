Future<bool> RegistrarProcess::_apply(Owned<Operation> operation)
{
  if (error.isSome()) {
    return Failure(error.get());
  }

  CHECK_SOME(variable);

  operations.push_back(operation);
  Future<bool> future = operation->future();
  if (!updating) {
    update();
  }
  return future;
}