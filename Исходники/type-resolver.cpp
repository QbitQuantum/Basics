bool
TypeResolver::analyze()
{
  printf("queue size: %d\n", int(work_queue_.length()));
  while (!work_queue_.empty()) {
    AstNode *node = work_queue_.popFrontCopy();
    node->accept(this);

    if (!cc_.canContinueProcessing())
      return false;
  }

  return true;
}