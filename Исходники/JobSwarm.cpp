  void ThreadWorker::threadMain(void)
  {
    while ( !mExit )
    {
      if ( mSwarmJob ) // if I have a job to do...
      {
        if ( !mSwarmJob->isCancelled() )
        {
          mSwarmJob->onExecute();              // execute the job.
        }
        mFinished.push(mSwarmJob);
      }

      if ( !mExit )
      {

        SwarmJob *job = 0;

        if ( !mFinished.isFull() )
        {
          job = mJobScheduler->getJob(); // get a new job to perform.
        }

        if (job )
        {
          mSwarmJob = job;
        }
        else
        {
          mSwarmJob = 0;
          mBusy->resetEvent();
          mBusy->waitForSingleObject(10);
        }
      }
    }
    mRunning = false;
  }