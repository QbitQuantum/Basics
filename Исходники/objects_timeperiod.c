static void _get_next_invalid_time(time_t pref_time, time_t *invalid_time, timeperiod *tperiod)
{
	timeperiodexclusion *temp_timeperiodexclusion = NULL;
	int depth = 0;
	int max_depth = 300; // commonly roughly equal to "days in the future"
	struct tm *t, tm_s;
	time_t earliest_time = pref_time;
	time_t last_earliest_time = 0;
	time_t midnight = (time_t)0L;
	time_t day_range_start = (time_t)0L;
	time_t day_range_end = (time_t)0L;
	time_t potential_time = 0;
	time_t excluded_time = 0;
	time_t last_range_end = 0;
	int have_earliest_time = FALSE;
	timerange *last_range = NULL, *temp_timerange = NULL;

	/* if no period was specified, assume the time is good */
	if (tperiod == NULL || check_time_against_period(pref_time, tperiod) == ERROR) {
		*invalid_time = pref_time;
		return;
	}

	/* first excluded time may well be the time we're looking for */
	for (temp_timeperiodexclusion = tperiod->exclusions; temp_timeperiodexclusion != NULL; temp_timeperiodexclusion = temp_timeperiodexclusion->next) {
		/* if pref_time is excluded, we're done */
		if (check_time_against_period(pref_time, temp_timeperiodexclusion->timeperiod_ptr) != ERROR) {
			*invalid_time = pref_time;
			return;
		}
		_get_next_valid_time(pref_time, &potential_time, temp_timeperiodexclusion->timeperiod_ptr);
		if (!excluded_time || excluded_time > potential_time)
			excluded_time = potential_time;
	}

	while (earliest_time != last_earliest_time && depth < max_depth) {
		have_earliest_time = FALSE;
		depth++;
		last_earliest_time = earliest_time;

		t = localtime_r((time_t *)&earliest_time, &tm_s);
		t->tm_sec = 0;
		t->tm_min = 0;
		t->tm_hour = 0;
		midnight = mktime(t);

		temp_timerange = _get_matching_timerange(earliest_time, tperiod);

		for (; temp_timerange; last_range = temp_timerange, temp_timerange = temp_timerange->next) {
			/* ranges with start/end of zero mean exlude this day */

			day_range_start = (time_t)(midnight + temp_timerange->range_start);
			day_range_end = (time_t)(midnight + temp_timerange->range_end);

#ifdef TEST_TIMEPERIODS_B
			printf("  INVALID RANGE START: %lu (%lu) = %s", temp_timerange->range_start, (unsigned long)day_range_start, ctime(&day_range_start));
			printf("  INVALID RANGE END:   %lu (%lu) = %s", temp_timerange->range_end, (unsigned long)day_range_end, ctime(&day_range_end));
#endif

			if (temp_timerange->range_start == 0 && temp_timerange->range_end == 0)
				continue;

			if (excluded_time && day_range_end > excluded_time) {
				earliest_time = excluded_time;
				have_earliest_time = TRUE;
				break;
			}

			/*
			 * Unless two consecutive days have adjoining timeranges,
			 * the end of the last period is the start of the first
			 * invalid time. This only needs special-casing when the
			 * last range of the previous day ends at midnight, and
			 * also catches the special case when there are only
			 * exceptions in a timeperiod and some days are skipped
			 * entirely.
			 */
			if (last_range && last_range->range_end == SECS_PER_DAY && last_range_end && day_range_start != last_range_end) {
				earliest_time = last_range_end;
				have_earliest_time = TRUE;
				break;
			}

			/* stash this day_range_end in case we skip a day */
			last_range_end = day_range_end;

			if (pref_time <= day_range_end && temp_timerange->range_end != SECS_PER_DAY) {
				earliest_time = day_range_end;
				have_earliest_time = TRUE;
#ifdef TEST_TIMEPERIODS_B
				printf("    EARLIEST INVALID TIME: %lu = %s", (unsigned long)earliest_time, ctime(&earliest_time));
#endif
				break;
			}
		}

		/* if we found this in the exclusions, we're done */
		if (have_earliest_time == TRUE) {
			break;
		}

		earliest_time = midnight + SECS_PER_DAY;
	}
#ifdef TEST_TIMEPERIODS_B
	printf("    FINAL EARLIEST INVALID TIME: %lu = %s", (unsigned long)earliest_time, ctime(&earliest_time));
#endif

	if (depth == max_depth)
		*invalid_time = pref_time;
	else
		*invalid_time = earliest_time;
}