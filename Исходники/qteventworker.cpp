void QtEventWorker::
        test()
{
    std::string name = "Worker";
    int argc = 1;
    char * argv = &name[0];
    QApplication a(argc,&argv);

    // It should start and stop automatically
    {
        UNITTEST_STEPS TaskTimer tt("It should start and stop automatically");

        ISchedule::ptr gettask(new GetTaskMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        QThread::yieldCurrentThread ();
        EXCEPTION_ASSERT( worker.isRunning () );
    }

    // It should run tasks as given by the scheduler
    {
        UNITTEST_STEPS TaskTimer tt("It should run tasks as given by the scheduler");

        ISchedule::ptr gettask(new GetTaskMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        worker.wait (1);

        EXCEPTION_ASSERT_EQUALS( 1, dynamic_cast<GetTaskMock*>(&*gettask)->get_task_count );
        // Verify that tasks execute properly in Task::test.

        EXCEPTION_ASSERT( worker.isRunning () );
        worker.abort ();
        EXCEPTION_ASSERT( worker.wait (2) );
        EXCEPTION_ASSERT( !worker.isRunning () );
    }

    // It should wait to be awaken if there are no tasks
    {
        UNITTEST_STEPS TaskTimer tt("It should run tasks as given by the scheduler");

        ISchedule::ptr gettask(new GetTaskMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        EXCEPTION_ASSERT( !worker.wait (1) );
        EXCEPTION_ASSERT_EQUALS( 1, dynamic_cast<GetTaskMock*>(&*gettask)->get_task_count );
        QThread::msleep (1);
        EXCEPTION_ASSERT_EQUALS( 1, dynamic_cast<GetTaskMock*>(&*gettask)->get_task_count );

        worker.wakeup ();
        worker.wait (1);
        EXCEPTION_ASSERT_EQUALS( 2, dynamic_cast<GetTaskMock*>(&*gettask)->get_task_count );
    }

    // It should store information about a crashed task (segfault) and stop execution.
    if (!DetectGdb::is_running_through_gdb() && !DetectGdb::was_started_through_gdb ())
    {
        UNITTEST_STEPS TaskTimer tt("It should store information about a crashed task (segfault) and stop execution");

        PrettifySegfault::EnableDirectPrint (false);

        ISchedule::ptr gettask(new GetTaskSegFaultMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        worker.wait (1);
        worker.abort ();
        EXCEPTION_ASSERT( worker.wait (1) );
        EXCEPTION_ASSERT( worker.caught_exception () );

        EXPECT_EXCEPTION(segfault_sigill_exception, rethrow_exception(worker.caught_exception ()));

        PrettifySegfault::EnableDirectPrint (true);
    }

    // It should store information about a crashed task (std::exception) and stop execution. (1)
    {
        UNITTEST_STEPS TaskTimer tt("It should store information about a crashed task (std::exception) and stop execution (1)");

        ISchedule::ptr gettask(new GetTaskExceptionMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        QThread::yieldCurrentThread ();
    }

    // It should store information about a crashed task (std::exception) and stop execution. (2)
    {
        UNITTEST_STEPS TaskTimer tt("It should store information about a crashed task (std::exception) and stop execution (2)");

        ISchedule::ptr gettask(new GetTaskExceptionMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        worker.wait (1);
        worker.abort ();
        worker.wait (1);
        worker.abort ();

        EXCEPTION_ASSERT( worker.caught_exception () );

        try {
            rethrow_exception(worker.caught_exception ());
            BOOST_THROW_EXCEPTION(boost::unknown_exception());
        } catch (const ExceptionAssert& x) {
            const std::string* message = boost::get_error_info<ExceptionAssert::ExceptionAssert_message>(x);
            EXCEPTION_ASSERT_EQUALS( "testing that worker catches exceptions from a scheduler", message?*message:"" );
        }
    }

#if !defined SHARED_STATE_NO_TIMEOUT
    // It should store information about a crashed task (LockFailed) and stop execution.
    {
        UNITTEST_STEPS TaskTimer tt("It should store information about a crashed task (LockFailed) and stop execution.");

        ISchedule::ptr gettask(new ImmediateDeadLockMock());

        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        worker.wait (2);
        worker.abort ();
        EXCEPTION_ASSERT( worker.wait (10) );
        EXCEPTION_ASSERT( worker.caught_exception () );
        EXPECT_EXCEPTION(lock_failed, rethrow_exception(worker.caught_exception ()));

        EXCEPTION_ASSERT_EQUALS( 1, dynamic_cast<GetTaskMock*>(&*gettask)->get_task_count );
    }
#endif

    // It should not hang if it causes a deadlock (1)
    {
        UNITTEST_STEPS TaskTimer tt("It should not hang if it causes a deadlock (1)");

        ISchedule::ptr gettask(new DeadLockMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        EXCEPTION_ASSERT( worker.isRunning () );
        worker.terminate ();
        worker.terminate ();
        worker.terminate ();
        worker.terminate ();
        worker.abort ();
        worker.abort ();
        worker.abort ();
        worker.abort ();
        EXCEPTION_ASSERT( worker.wait (1) );
    }

    // It should not hang if it causes a deadlock (2)
    {
        UNITTEST_STEPS TaskTimer tt("It should not hang if it causes a deadlock (2)");

        ISchedule::ptr gettask(new DeadLockMock());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask);

        EXCEPTION_ASSERT( !worker.wait (1) );
        worker.terminate ();
        EXCEPTION_ASSERT( worker.wait (2) ); // Finish within 2 ms after terminate
        EXPECT_EXCEPTION( TerminatedException, rethrow_exception(worker.caught_exception ()) );
    }

    // It should announce when tasks are finished.
    {
        UNITTEST_STEPS TaskTimer tt("It should announce when tasks are finished.");

        ISchedule::ptr gettask(new DummySchedule());
        QtEventWorker worker(Signal::ComputingEngine::ptr(), gettask, false);

        QTimer t;
        t.setSingleShot( true );
        t.setInterval( 100 );

        QEventLoop e;
        connect (&t, SIGNAL(timeout()), &e, SLOT(quit()));
        connect (&worker, SIGNAL(oneTaskDone()), &e, SLOT(quit()), Qt::DirectConnection);

        worker.wakeup ();
        t.start();

        e.exec ();

        bool aborted_from_timeout = !t.isActive();
        EXCEPTION_ASSERT(!aborted_from_timeout);
   }
}