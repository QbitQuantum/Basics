// This test verifies that when the slave re-registers, the master
// does not send TASK_LOST update for a task that has reached terminal
// state but is waiting for an acknowledgement.
TEST_F(MasterSlaveReconciliationTest, SlaveReregisterTerminalTask)
{
  Try<PID<Master> > master = StartMaster();
  ASSERT_SOME(master);

  MockExecutor exec(DEFAULT_EXECUTOR_ID);

  StandaloneMasterDetector detector(master.get());

  Try<PID<Slave> > slave = StartSlave(&exec, &detector);
  ASSERT_SOME(slave);

  MockScheduler sched;
  MesosSchedulerDriver driver(
      &sched, DEFAULT_FRAMEWORK_INFO, master.get(), DEFAULT_CREDENTIAL);

  EXPECT_CALL(sched, registered(&driver, _, _));

  Future<vector<Offer> > offers;
  EXPECT_CALL(sched, resourceOffers(&driver, _))
    .WillOnce(FutureArg<1>(&offers))
    .WillRepeatedly(Return()); // Ignore subsequent offers.

  driver.start();

  AWAIT_READY(offers);
  EXPECT_NE(0u, offers.get().size());

  TaskInfo task;
  task.set_name("test task");
  task.mutable_task_id()->set_value("1");
  task.mutable_slave_id()->MergeFrom(offers.get()[0].slave_id());
  task.mutable_resources()->MergeFrom(offers.get()[0].resources());
  task.mutable_executor()->MergeFrom(DEFAULT_EXECUTOR_INFO);

  EXPECT_CALL(exec, registered(_, _, _, _));

  // Send a terminal update right away.
  EXPECT_CALL(exec, launchTask(_, _))
    .WillOnce(SendStatusUpdateFromTask(TASK_FINISHED));

  // Drop the status update from slave to the master, so that
  // the slave has a pending terminal update when it re-registers.
  DROP_PROTOBUF(StatusUpdateMessage(), _, master.get());

  Future<Nothing> _statusUpdate = FUTURE_DISPATCH(_, &Slave::_statusUpdate);

  Future<TaskStatus> status;
  EXPECT_CALL(sched, statusUpdate(&driver, _))
    .WillOnce(FutureArg<1>(&status))
    .WillRepeatedly(Return()); // Ignore retried update due to update framework.

  driver.launchTasks(offers.get()[0].id(), {task});

  AWAIT_READY(_statusUpdate);

  Future<SlaveReregisteredMessage> slaveReregisteredMessage =
    FUTURE_PROTOBUF(SlaveReregisteredMessage(), _, _);

  // Simulate a spurious master change event (e.g., due to ZooKeeper
  // expiration) at the slave to force re-registration.
  detector.appoint(master.get());

  AWAIT_READY(slaveReregisteredMessage);

  // The master should not send a TASK_LOST after the slave
  // re-registers. We check this by calling Clock::settle() so that
  // the only update the scheduler receives is the retried
  // TASK_FINISHED update.
  // NOTE: The status update manager resends the status update when
  // it detects a new master.
  Clock::pause();
  Clock::settle();

  AWAIT_READY(status);
  ASSERT_EQ(TASK_FINISHED, status.get().state());

  EXPECT_CALL(exec, shutdown(_))
    .Times(AtMost(1));

  driver.stop();
  driver.join();

  Shutdown();
}