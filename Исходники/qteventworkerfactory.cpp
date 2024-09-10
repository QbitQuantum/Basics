void QtEventWorkerFactory::
        test()
{
    std::string name = "QtEventWorkers";
    int argc = 1;
    char * argv = &name[0];
    QApplication a(argc,&argv); // takes 0.4 s if this is the first instantiation of QApplication

    Workers::test ([](ISchedule::ptr schedule){
        Bedroom::ptr bedroom(new Bedroom);
        return IWorkerFactory::ptr(new QtEventWorkerFactory(schedule, bedroom));
    });

    {
        UNITTEST_STEPS TaskInfo("It should terminate all threads when it's closed");

        ISchedule::ptr schedule[] = {
            ISchedule::ptr(new SleepScheduleMock),
            ISchedule::ptr(new LockScheduleMock),
            ISchedule::ptr(new BusyScheduleMock)
        };

        for (unsigned i=0; i<sizeof(schedule)/sizeof(schedule[0]); i++) {
            Timer t;
            {
                ISchedule::ptr s = schedule[i];
                //TaskInfo ti(boost::format("%s") % vartype(*s));
                Bedroom::ptr bedroom(new Bedroom);

                Processing::Workers workers(IWorkerFactory::ptr(new QtEventWorkerFactory(s, bedroom)));
                Bedroom::Bed bed = dynamic_cast<BlockScheduleMock*>(s.get ())->bedroom.getBed();

                workers.addComputingEngine(Signal::ComputingEngine::ptr());

                // Wait until the schedule has been called (Bedroom supports
                // that the wakeup in schedule is called even before this sleep call
                // as long as 'bed' is allocated before the wakeup call)
                bed.sleep ();

                EXCEPTION_ASSERT_EQUALS(false, workers.remove_all_engines (10));
                EXCEPTION_ASSERT_EQUALS(true, QtEventWorkerFactory::terminate_workers (workers, 0));

                EXCEPTION_ASSERT_EQUALS(workers.n_workers(), 0u);
                EXPECT_EXCEPTION(QtEventWorker::TerminatedException, workers.rethrow_any_worker_exception ());
                workers.clean_dead_workers ();
            }
            float elapsed = t.elapsed ();
            float n = (i+1)*0.00001;
            EXCEPTION_ASSERT_LESS(0.01+n, elapsed);
            EXCEPTION_ASSERT_LESS(elapsed, 0.04+n); // +n makes it possible to see in the test log which iteration that failed
        }
    }

    // It should wake up sleeping workers when any work is done to see if they can
    // help out on what's left.
    {

    }
}