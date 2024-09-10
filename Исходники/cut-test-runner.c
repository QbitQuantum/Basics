static void
connect_to_test_case (CutRunContext *context, CutTestCase *test_case)
{
#define CONNECT(name)                                                   \
    g_signal_connect(test_case, #name,                                  \
                     G_CALLBACK(cb_ ## name ## _test_case), context)

    CONNECT(start_test);
    CONNECT(complete_test);
    CONNECT(start_test_iterator);
    CONNECT(complete_test_iterator);

    CONNECT(success);
    CONNECT(failure);
    CONNECT(error);
    CONNECT(pending);
    CONNECT(notification);
    CONNECT(omission);
    CONNECT(crash);

    CONNECT(failure_in);
    CONNECT(error_in);
    CONNECT(pending_in);
    CONNECT(notification_in);
    CONNECT(omission_in);
    CONNECT(crash_in);

    CONNECT(ready);
    CONNECT(start);
    CONNECT(complete);
#undef CONNECT
}