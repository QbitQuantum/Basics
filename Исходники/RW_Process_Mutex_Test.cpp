/*
 * The set of readers and the writer will operate in a staggered sequence
 * of acquiring and releasing the lock. The sequence is designed to exercise
 * waiting behavior of both readers and writer, as well as allowing multiple
 * readers in, without getting tripped up by any differences in ordering
 * on different platforms which may favor writers, or vice-versa.
 * In this timeline, time on seconds is on the left, time holding the lock
 * is solid, time waiting is dots, acquire/release point is a dash, and
 * time without the lock is blank.
 *
 *   TIME        WRITER    READER1    READER2    READER3
 *     0            |
 *                  |
 *     1            |         .
 *                  |         .
 *     2            -         -          -
 *                            |          |
 *     3                      |          |          -
 *                            |          |          |
 *     4                      -          |          |
 *                                       |          |
 *     5                                 -          |
 *                                                  |
 *     6            -                               -
 *                  |
 *     7            |         .          .          .
 *                  |         .          .          .
 *     8            -         -          -          -
 *                            |          |          |
 *     9                      |          |          |
 *
 * A file is used to test the sequencing. When the writer first gets the
 * lock, it will ensure the file is not present. At the end of its time
 * holding the lock the first time, it will write a "writer 1" string to
 * the file. When it gets the lock the second time, it will write a
 * different string to the file, and just before releasing the second time
 * write a "writer 2" string to the file. The readers all check to be sure
 * that the file is present and says "writer 1" at the start and end of
 * their periods of holding the reader lock and, similarly, check for
 * "writer 2" the second time they hold the lock.
 */
static void
reader (int num)
{
    // Let the writer get there first.
    ACE_OS::sleep (1);

    ACE_SOCK_Dgram sock;
    ACE_INET_Addr parent;
    parent.set (reporting_port, ACE_LOCALHOST, 1, AF_INET);
    ACE_TCHAR me_str[80];
    parent.addr_to_string (me_str, 80);
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Sending reports to %s\n"), me_str));

    if (sock.open (ACE_Addr::sap_any, PF_INET) == -1)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("UDP open")));

    Range_Report report;
    report.child_ = num;
    ACE_Time_Value start (ACE_Time_Value::zero), stop (ACE_Time_Value::zero);

    ACE_RW_Process_Mutex mutex (mutex_name.c_str ());

    // Make sure the constructor succeeded
    if (ACE_LOG_MSG->op_status () != 0)
    {
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Reader %d, mutex %s %p\n"),
                    num,
                    mutex_name.c_str (),
                    ACE_TEXT ("ctor")));
        return;
    }

    ACE_OS::sleep (num);
    // Grab the lock
    if (-1 == mutex.acquire_read ())
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Reader %d %p\n"),
                    num,
                    ACE_TEXT ("first acquire_read")));
    else
    {
        start = ACE_OS::gettimeofday ();
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("Reader %d acquired first time\n"),
                    num));
    }

    // Wait a bit, then release and report the range held.
    ACE_OS::sleep (num);

    // Release the lock then wait; in the interim, the writer should change
    // the file.
    stop = ACE_OS::gettimeofday ();
    if (-1 == mutex.release ())
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Reader %d %p\n"),
                    num,
                    ACE_TEXT ("first release")));
    else
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Reader %d released first time\n"), num));
    report.range_.set (start, stop);
    ssize_t bytes = sock.send (&report, sizeof (report), parent);
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Reader %d sent %b byte report\n"),
                num,
                bytes));

    ACE_OS::sleep (4 - num);
    start = stop = ACE_Time_Value::zero;
    if (-1 == mutex.acquire_read ())
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Reader %d %p\n"),
                    num,
                    ACE_TEXT ("second acquire_read")));
    else
    {
        start = ACE_OS::gettimeofday ();
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("Reader %d acquired second time\n"),
                    num));
    }

    // Done; small delay, release, report, and return.
    ACE_OS::sleep (1);
    stop = ACE_OS::gettimeofday ();
    if (-1 == mutex.release ())
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Reader %d %p\n"),
                    num,
                    ACE_TEXT ("second release")));
    else
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("Reader %d released second time; done\n"),
                    num));
    report.range_.set (start, stop);
    bytes = sock.send (&report, sizeof (report), parent);
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Reader %d sent %b byte report\n"),
                num,
                bytes));
    sock.close ();
    return;
}