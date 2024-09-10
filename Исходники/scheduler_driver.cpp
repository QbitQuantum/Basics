SchedulerDriverStatus scheduler_abort(SchedulerDriverPtr driver)
{
  TRACE("scheduler_abort()\n");
  assert(driver != NULL);

  MesosSchedulerDriver* mdriver =
      reinterpret_cast<MesosSchedulerDriver*>(driver);

  return mdriver->abort();
}