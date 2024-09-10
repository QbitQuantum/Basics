// This test checks that a failed over scheduler gets the retried status update
// when the original instance dies without acknowledging the update.
TEST_F(HttpFaultToleranceTest, SchedulerFailoverStatusUpdate)
{
  master::Flags flags = CreateMasterFlags();
  flags.authenticate_frameworks = false;

  Try<Owned<cluster::Master>> master = StartMaster(flags);
  ASSERT_SOME(master);

  auto scheduler = std::make_shared<v1::MockHTTPScheduler>();
  auto executor = std::make_shared<v1::MockHTTPExecutor>();

  ExecutorID executorId = DEFAULT_EXECUTOR_ID;
  TestContainerizer containerizer(executorId, executor);

  Owned<MasterDetector> detector = master.get()->createDetector();

  Try<Owned<cluster::Slave>> slave = StartSlave(detector.get(), &containerizer);
  ASSERT_SOME(slave);

  Future<Nothing> connected;
  EXPECT_CALL(*scheduler, connected(_))
    .WillOnce(FutureSatisfy(&connected))
    .WillRepeatedly(Return()); // Ignore future invocations.

  ContentType contentType = ContentType::PROTOBUF;

  v1::scheduler::TestMesos schedulerLibrary(
      master.get()->pid,
      contentType,
      scheduler);

  AWAIT_READY(connected);

  Future<Event::Subscribed> subscribed;
  EXPECT_CALL(*scheduler, subscribed(_, _))
    .WillOnce(FutureArg<1>(&subscribed));

  EXPECT_CALL(*scheduler, heartbeat(_))
    .WillRepeatedly(Return()); // Ignore heartbeats.

  Future<Event::Offers> offers;
  EXPECT_CALL(*scheduler, offers(_, _))
    .WillOnce(FutureArg<1>(&offers));

  {
    Call call;
    call.set_type(Call::SUBSCRIBE);

    Call::Subscribe* subscribe = call.mutable_subscribe();
    subscribe->mutable_framework_info()->CopyFrom(v1::DEFAULT_FRAMEWORK_INFO);

    schedulerLibrary.send(call);
  }

  AWAIT_READY(subscribed);

  v1::FrameworkID frameworkId(subscribed->framework_id());

  AWAIT_READY(offers);
  EXPECT_NE(0, offers->offers().size());

  EXPECT_CALL(*executor, connected(_))
    .WillOnce(v1::executor::SendSubscribe(frameworkId, evolve(executorId)));

  EXPECT_CALL(*executor, subscribed(_, _));

  EXPECT_CALL(*executor, launch(_, _))
    .WillOnce(v1::executor::SendUpdateFromTask(
        frameworkId, evolve(executorId), v1::TASK_RUNNING));

  Future<Nothing> acknowledged;
  EXPECT_CALL(*executor, acknowledged(_, _))
    .WillOnce(FutureSatisfy(&acknowledged));

  Future<Event::Update> update;
  EXPECT_CALL(*scheduler, update(_, _))
    .WillOnce(FutureArg<1>(&update));

  const v1::Offer& offer = offers->offers(0);

  v1::TaskInfo taskInfo =
    evolve(createTask(devolve(offer), "", executorId));

  {
    Call call;
    call.mutable_framework_id()->CopyFrom(frameworkId);
    call.set_type(Call::ACCEPT);

    Call::Accept* accept = call.mutable_accept();
    accept->add_offer_ids()->CopyFrom(offer.id());

    v1::Offer::Operation* operation = accept->add_operations();
    operation->set_type(v1::Offer::Operation::LAUNCH);
    operation->mutable_launch()->add_task_infos()->CopyFrom(taskInfo);

    schedulerLibrary.send(call);
  }

  AWAIT_READY(acknowledged);
  AWAIT_READY(update);

  EXPECT_EQ(v1::TASK_RUNNING, update->status().state());
  EXPECT_EQ(executorId, devolve(update->status().executor_id()));

  EXPECT_TRUE(update->status().has_executor_id());
  EXPECT_TRUE(update->status().has_uuid());

  // Failover the scheduler without acknowledging the status update.

  auto scheduler2 = std::make_shared<v1::MockHTTPScheduler>();

  Future<Nothing> connected2;
  EXPECT_CALL(*scheduler2, connected(_))
    .WillOnce(FutureSatisfy(&connected2));

  // Failover to another scheduler instance.
  v1::scheduler::TestMesos schedulerLibrary2(
      master.get()->pid,
      contentType,
      scheduler2);

  AWAIT_READY(connected2);

  // The previously connected scheduler instance should receive an
  // error/disconnected event.
  Future<Nothing> error;
  EXPECT_CALL(*scheduler, error(_, _))
    .WillOnce(FutureSatisfy(&error));

  Future<Nothing> disconnected;
  EXPECT_CALL(*scheduler, disconnected(_))
    .WillOnce(FutureSatisfy(&disconnected));

  EXPECT_CALL(*scheduler2, subscribed(_, _))
    .WillOnce(FutureArg<1>(&subscribed));

  EXPECT_CALL(*scheduler2, heartbeat(_))
    .WillRepeatedly(Return()); // Ignore heartbeats.

  // Scheduler2 should receive the retried status update.
  Future<Nothing> update2;
  EXPECT_CALL(*scheduler2, update(_, _))
    .WillOnce(FutureSatisfy(&update2))
    .WillRepeatedly(Return()); // Ignore subsequent updates.

  {
    Call call;
    call.mutable_framework_id()->CopyFrom(frameworkId);
    call.set_type(Call::SUBSCRIBE);

    Call::Subscribe* subscribe = call.mutable_subscribe();
    subscribe->mutable_framework_info()->CopyFrom(v1::DEFAULT_FRAMEWORK_INFO);
    subscribe->mutable_framework_info()->mutable_id()->CopyFrom(frameworkId);

    schedulerLibrary2.send(call);
  }

  AWAIT_READY(error);
  AWAIT_READY(disconnected);
  AWAIT_READY(subscribed);

  EXPECT_EQ(frameworkId, subscribed->framework_id());

  Clock::pause();

  // Now advance time enough for the reliable timeout to kick in and
  // another status update to be sent.
  Clock::advance(slave::STATUS_UPDATE_RETRY_INTERVAL_MIN);

  AWAIT_READY(update2);

  EXPECT_CALL(*executor, shutdown(_))
    .Times(AtMost(1));

  EXPECT_CALL(*executor, disconnected(_))
    .Times(AtMost(1));
}