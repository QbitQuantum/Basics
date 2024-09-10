void WorkerCrashLogger::
        worker_quit(std::exception_ptr e, Signal::ComputingEngine::ptr ce)
{
    DEBUG TaskInfo ti(boost::format("WorkerCrashLogger::worker_quit %s") % (e?"normally":"with exception"));
    if (consume_exceptions_)
      {
        workers_.write ()->removeComputingEngine(ce);
      }

    try
      {
        if (e)
          {
            rethrow_exception(e);
          }

      }
    catch ( const boost::exception& x)
      {
        x << Workers::crashed_engine(ce) << Workers::crashed_engine_typename(ce?vartype(*ce):"(null)");

        log(x);
      }
}