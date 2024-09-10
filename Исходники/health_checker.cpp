Future<Nothing> HealthCheckerProcess::healthCheck()
{
  VLOG(1) << "Health check starting in "
          << Seconds(static_cast<int64_t>(check.delay_seconds()))
          << ", grace period "
          << Seconds(static_cast<int64_t>(check.grace_period_seconds()));

  startTime = Clock::now();

  delay(Seconds(static_cast<int64_t>(check.delay_seconds())),
        self(),
        &Self::_healthCheck);
  return promise.future();
}