void
TimeoutManager::RunTimeout(const TimeStamp& aNow, const TimeStamp& aTargetDeadline)
{
  MOZ_DIAGNOSTIC_ASSERT(!aNow.IsNull());
  MOZ_DIAGNOSTIC_ASSERT(!aTargetDeadline.IsNull());

  MOZ_ASSERT_IF(mWindow.IsFrozen(), mWindow.IsSuspended());
  if (mWindow.IsSuspended()) {
    return;
  }

  // Limit the overall time spent in RunTimeout() to reduce jank.
  uint32_t totalTimeLimitMS = std::max(1u, gMaxConsecutiveCallbacksMilliseconds);
  const TimeDuration totalTimeLimit =
    TimeDuration::Min(TimeDuration::FromMilliseconds(totalTimeLimitMS),
                      TimeDuration::Max(TimeDuration(), mExecutionBudget));

  // Allow up to 25% of our total time budget to be used figuring out which
  // timers need to run.  This is the initial loop in this method.
  const TimeDuration initialTimeLimit =
    TimeDuration::FromMilliseconds(totalTimeLimit.ToMilliseconds() / 4);

  // Ammortize overhead from from calling TimeStamp::Now() in the initial
  // loop, though, by only checking for an elapsed limit every N timeouts.
  const uint32_t kNumTimersPerInitialElapsedCheck = 100;

  // Start measuring elapsed time immediately.  We won't potentially expire
  // the time budget until at least one Timeout has run, though.
  TimeStamp now(aNow);
  TimeStamp start = now;

  uint32_t firingId = CreateFiringId();
  auto guard = MakeScopeExit([&] {
    DestroyFiringId(firingId);
  });

  // Make sure that the window and the script context don't go away as
  // a result of running timeouts
  nsCOMPtr<nsIScriptGlobalObject> windowKungFuDeathGrip(&mWindow);
  // Silence the static analysis error about windowKungFuDeathGrip.  Accessing
  // members of mWindow here is safe, because the lifetime of TimeoutManager is
  // the same as the lifetime of the containing nsGlobalWindow.
  Unused << windowKungFuDeathGrip;

  // A native timer has gone off. See which of our timeouts need
  // servicing
  TimeStamp deadline;

  if (aTargetDeadline > now) {
    // The OS timer fired early (which can happen due to the timers
    // having lower precision than TimeStamp does).  Set |deadline| to
    // be the time when the OS timer *should* have fired so that any
    // timers that *should* have fired *will* be fired now.

    deadline = aTargetDeadline;
  } else {
    deadline = now;
  }

  TimeStamp nextDeadline;
  uint32_t numTimersToRun = 0;

  // The timeout list is kept in deadline order. Discover the latest timeout
  // whose deadline has expired. On some platforms, native timeout events fire
  // "early", but we handled that above by setting deadline to aTargetDeadline
  // if the timer fired early.  So we can stop walking if we get to timeouts
  // whose When() is greater than deadline, since once that happens we know
  // nothing past that point is expired.
  {
    // Use a nested scope in order to make sure the strong references held by
    // the iterator are freed after the loop.
    OrderedTimeoutIterator expiredIter(mNormalTimeouts, mTrackingTimeouts);

    while (true) {
      Timeout* timeout = expiredIter.Next();
      if (!timeout || totalTimeLimit.IsZero() || timeout->When() > deadline) {
        if (timeout) {
          nextDeadline = timeout->When();
        }
        break;
      }

      if (IsInvalidFiringId(timeout->mFiringId)) {
        // Mark any timeouts that are on the list to be fired with the
        // firing depth so that we can reentrantly run timeouts
        timeout->mFiringId = firingId;

        numTimersToRun += 1;

        // Run only a limited number of timers based on the configured maximum.
        if (numTimersToRun % kNumTimersPerInitialElapsedCheck == 0) {
          now = TimeStamp::Now();
          TimeDuration elapsed(now - start);
          if (elapsed >= initialTimeLimit) {
            nextDeadline = timeout->When();
            break;
          }
        }
      }

      expiredIter.UpdateIterator();
    }
  }

  now = TimeStamp::Now();

  // Wherever we stopped in the timer list, schedule the executor to
  // run for the next unexpired deadline.  Note, this *must* be done
  // before we start executing any content script handlers.  If one
  // of them spins the event loop the executor must already be scheduled
  // in order for timeouts to fire properly.
  if (!nextDeadline.IsNull()) {
    // Note, we verified the window is not suspended at the top of
    // method and the window should not have been suspended while
    // executing the loop above since it doesn't call out to js.
    MOZ_DIAGNOSTIC_ASSERT(!mWindow.IsSuspended());
    MOZ_ALWAYS_SUCCEEDS(MaybeSchedule(nextDeadline, now));
  }

  // Maybe the timeout that the event was fired for has been deleted
  // and there are no others timeouts with deadlines that make them
  // eligible for execution yet. Go away.
  if (!numTimersToRun) {
    return;
  }

  // Now we need to search the normal and tracking timer list at the same
  // time to run the timers in the scheduled order.

  // We stop iterating each list when we go past the last expired timeout from
  // that list that we have observed above.  That timeout will either be the
  // next item after the last timeout we looked at or nullptr if we have
  // exhausted the entire list while looking for the last expired timeout.
  {
    // Use a nested scope in order to make sure the strong references held by
    // the iterator are freed after the loop.
    OrderedTimeoutIterator runIter(mNormalTimeouts, mTrackingTimeouts);
    while (true) {
      RefPtr<Timeout> timeout = runIter.Next();
      if (!timeout) {
        // We have run out of timeouts!
        break;
      }
      runIter.UpdateIterator();

      // We should only execute callbacks for the set of expired Timeout
      // objects we computed above.
      if (timeout->mFiringId != firingId) {
        // If the FiringId does not match, but is still valid, then this is
        // a TImeout for another RunTimeout() on the call stack.  Just
        // skip it.
        if (IsValidFiringId(timeout->mFiringId)) {
          continue;
        }

        // If, however, the FiringId is invalid then we have reached Timeout
        // objects beyond the list we calculated above.  This can happen
        // if the Timeout just beyond our last expired Timeout is cancelled
        // by one of the callbacks we've just executed.  In this case we
        // should just stop iterating.  We're done.
        else {
          break;
        }
      }

      MOZ_ASSERT_IF(mWindow.IsFrozen(), mWindow.IsSuspended());
      if (mWindow.IsSuspended()) {
        break;
      }

      // The timeout is on the list to run at this depth, go ahead and
      // process it.

      // Get the script context (a strong ref to prevent it going away)
      // for this timeout and ensure the script language is enabled.
      nsCOMPtr<nsIScriptContext> scx = mWindow.GetContextInternal();

      if (!scx) {
        // No context means this window was closed or never properly
        // initialized for this language.  This timer will never fire
        // so just remove it.
        timeout->remove();
        continue;
      }

      // This timeout is good to run
      bool timeout_was_cleared = mWindow.RunTimeoutHandler(timeout, scx);

      MOZ_LOG(gLog, LogLevel::Debug,
              ("Run%s(TimeoutManager=%p, timeout=%p, tracking=%d) returned %d\n", timeout->mIsInterval ? "Interval" : "Timeout",
               this, timeout.get(),
               int(timeout->mIsTracking),
               !!timeout_was_cleared));

      if (timeout_was_cleared) {
        // Make sure the iterator isn't holding any Timeout objects alive.
        runIter.Clear();

        // Since ClearAllTimeouts() was called the lists should be empty.
        MOZ_DIAGNOSTIC_ASSERT(!HasTimeouts());

        return;
      }

      // If we need to reschedule a setInterval() the delay should be
      // calculated based on when its callback started to execute.  So
      // save off the last time before updating our "now" timestamp to
      // account for its callback execution time.
      TimeStamp lastCallbackTime = now;
      now = TimeStamp::Now();

      // If we have a regular interval timer, we re-schedule the
      // timeout, accounting for clock drift.
      bool needsReinsertion = RescheduleTimeout(timeout, lastCallbackTime, now);

      // Running a timeout can cause another timeout to be deleted, so
      // we need to reset the pointer to the following timeout.
      runIter.UpdateIterator();

      timeout->remove();

      if (needsReinsertion) {
        // Insert interval timeout onto the corresponding list sorted in
        // deadline order. AddRefs timeout.
        if (runIter.PickedTrackingIter()) {
          mTrackingTimeouts.Insert(timeout,
                                   mWindow.IsFrozen() ? Timeouts::SortBy::TimeRemaining
                                                      : Timeouts::SortBy::TimeWhen);
        } else {
          mNormalTimeouts.Insert(timeout,
                                 mWindow.IsFrozen() ? Timeouts::SortBy::TimeRemaining
                                                    : Timeouts::SortBy::TimeWhen);
        }
      }

      // Check to see if we have run out of time to execute timeout handlers.
      // If we've exceeded our time budget then terminate the loop immediately.
      TimeDuration elapsed = now - start;
      if (elapsed >= totalTimeLimit) {
        // We ran out of time.  Make sure to schedule the executor to
        // run immediately for the next timer, if it exists.  Its possible,
        // however, that the last timeout handler suspended the window.  If
        // that happened then we must skip this step.
        if (!mWindow.IsSuspended()) {
          RefPtr<Timeout> timeout = runIter.Next();
          if (timeout) {
            // If we ran out of execution budget we need to force a
            // reschedule. By cancelling the executor we will not run
            // immediately, but instead reschedule to the minimum
            // scheduling delay.
            if (mExecutionBudget < TimeDuration()) {
              mExecutor->Cancel();
            }

            MOZ_ALWAYS_SUCCEEDS(MaybeSchedule(timeout->When(), now));
          }
        }
        break;
      }
    }
  }
}