static void mm_rearm_timer(struct qemu_alarm_timer *t)
{
    int nearest_delta_ms;

    assert(alarm_has_dynticks(t));
    if (!qemu_clock_has_timers(QEMU_CLOCK_REALTIME) &&
        !qemu_clock_has_timers(QEMU_CLOCK_VIRTUAL) &&
        !qemu_clock_has_timers(QEMU_CLOCK_HOST)) {
        return;
    }

    timeKillEvent(mm_timer);

    nearest_delta_ms = (qemu_next_alarm_deadline() + 999999) / 1000000;
    if (nearest_delta_ms < 1) {
        nearest_delta_ms = 1;
    }
    mm_timer = timeSetEvent(nearest_delta_ms,
                            mm_period,
                            mm_alarm_handler,
                            (DWORD_PTR)t,
                            TIME_ONESHOT | TIME_CALLBACK_FUNCTION);

    if (!mm_timer) {
        fprintf(stderr, "Failed to re-arm win32 alarm timer %ld\n",
                GetLastError());

        timeEndPeriod(mm_period);
        exit(1);
    }
}