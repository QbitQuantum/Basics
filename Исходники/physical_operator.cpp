ThreadContext* PhysicalOperator::CreateOrReuseContext(context_reuse_mode crm) {
  ThreadContext* target = GetFreeContext(crm);
  if (target != NULL) {
    return target;
  }

  target = CreateContext();
  target->set_locality_(GetCurrentCpuAffinity());
  InitContext(target);
  return target;
}