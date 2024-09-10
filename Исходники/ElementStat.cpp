void
ElementStat::SetTimes(const fixed until_start_s, const fixed ts,
                      const fixed time)
{
  time_started = ts;

  if (negative(time_started) || negative(time))
    /* not yet started */
    time_elapsed = fixed(0);
  else
    time_elapsed = fdim(time, ts);

  if (solution_remaining.IsOk()) {
    time_remaining_now = solution_remaining.time_elapsed;
    time_remaining_start = fdim(time_remaining_now, until_start_s);
    time_planned = time_elapsed + time_remaining_start;
  } else {
    time_remaining_now = time_remaining_start = time_planned = fixed(0);
  }
}