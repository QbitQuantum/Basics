SchedulerDriverStatus scheduler_abort(SchedulerPtrPair state)
{
    assert(state.driver != NULL);

    MesosSchedulerDriver* driver = reinterpret_cast<MesosSchedulerDriver*> (state.driver);
    return driver->abort();
}