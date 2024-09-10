static void print_status_info(const StatusInfo *i) {
        const char *old_tz = NULL, *tz;
        bool have_time = false;
        char a[LINE_MAX];
        struct tm tm;
        time_t sec;
        size_t n;
        int r;

        assert(i);

        /* Save the old $TZ */
        tz = getenv("TZ");
        if (tz)
                old_tz = strdupa(tz);

        /* Set the new $TZ */
        if (setenv("TZ", isempty(i->timezone) ? "UTC" : i->timezone, true) < 0)
                log_warning_errno(errno, "Failed to set TZ environment variable, ignoring: %m");
        else
                tzset();

        if (i->time != 0) {
                sec = (time_t) (i->time / USEC_PER_SEC);
                have_time = true;
        } else if (IN_SET(arg_transport, BUS_TRANSPORT_LOCAL, BUS_TRANSPORT_MACHINE)) {
                sec = time(NULL);
                have_time = true;
        } else
                log_warning("Could not get time from timedated and not operating locally, ignoring.");

        if (have_time) {
                n = strftime(a, sizeof a, "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&sec, &tm));
                printf("               Local time: %s\n", n > 0 ? a : "n/a");

                n = strftime(a, sizeof a, "%a %Y-%m-%d %H:%M:%S UTC", gmtime_r(&sec, &tm));
                printf("           Universal time: %s\n", n > 0 ? a : "n/a");
        } else {
                printf("               Local time: %s\n", "n/a");
                printf("           Universal time: %s\n", "n/a");
        }

        if (i->rtc_time > 0) {
                time_t rtc_sec;

                rtc_sec = (time_t) (i->rtc_time / USEC_PER_SEC);
                n = strftime(a, sizeof a, "%a %Y-%m-%d %H:%M:%S", gmtime_r(&rtc_sec, &tm));
                printf("                 RTC time: %s\n", n > 0 ? a : "n/a");
        } else
                printf("                 RTC time: %s\n", "n/a");

        if (have_time)
                n = strftime(a, sizeof a, "%Z, %z", localtime_r(&sec, &tm));

        /* Restore the $TZ */
        if (old_tz)
                r = setenv("TZ", old_tz, true);
        else
                r = unsetenv("TZ");
        if (r < 0)
                log_warning_errno(errno, "Failed to set TZ environment variable, ignoring: %m");
        else
                tzset();

        printf("                Time zone: %s (%s)\n"
               "System clock synchronized: %s\n"
               "              NTP service: %s\n"
               "          RTC in local TZ: %s\n",
               strna(i->timezone), have_time && n > 0 ? a : "n/a",
               yes_no(i->ntp_synced),
               i->ntp_capable ? (i->ntp_active ? "active" : "inactive") : "n/a",
               yes_no(i->rtc_local));

        if (i->rtc_local)
                printf("\n%s"
                       "Warning: The system is configured to read the RTC time in the local time zone.\n"
                       "         This mode cannot be fully supported. It will create various problems\n"
                       "         with time zone changes and daylight saving time adjustments. The RTC\n"
                       "         time is never updated, it relies on external facilities to maintain it.\n"
                       "         If at all possible, use RTC in UTC by calling\n"
                       "         'timedatectl set-local-rtc 0'.%s\n", ansi_highlight(), ansi_normal());
}