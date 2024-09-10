static void worker_fsync(struct job_fsync *job)
{
  if (!FlushFileBuffers(job->handle))
    job->error_code = GetLastError();
}