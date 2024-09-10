// static
int vrpn_Mutex_Remote::handle_initialize(void *userdata, vrpn_HANDLERPARAM p)
{
    vrpn_Mutex_Remote *me = (vrpn_Mutex_Remote *)userdata;
    const char *b = p.buffer;

    // Only pay attention to the first initialize() message we get
    // after startup.
    if (me->d_myIndex != -1) {
        return 0;
    }

    vrpn_int32 expected_payload_len =
        2 * sizeof(vrpn_int32) + sizeof(vrpn_uint32);
    if (p.payload_len != expected_payload_len) {
        fprintf(stderr,
                "vrpn_Mutex_Remote::handle_initialize: "
                "Warning: Ignoring message with length %d, expected %d\n",
                p.payload_len, expected_payload_len);
        return 0;
    }

    vrpn_uint32 ip_addr;
    vrpn_int32 pid;
    vrpn_unbuffer(&b, &ip_addr);
    vrpn_unbuffer(&b, &pid);
    vrpn_int32 my_pid = 0;
#ifdef _WIN32
    my_pid = _getpid();
#else
    my_pid = getpid();
#endif
    if ((ip_addr != getmyIP()) || (pid != my_pid)) {
        fprintf(
            stderr,
            "vrpn_Mutex_Remote::handle_initialize: "
            "Warning: Ignoring message that doesn't match ip/pid identifier\n");
#ifdef VERBOSE
        fprintf(stderr, "Got %lu %d, expected %lu %d.\n", ip_addr, pid,
                getmyIP(), my_pid);
#endif
        return 0;
    }
    vrpn_unbuffer(&b, &(me->d_myIndex));

#ifdef VERBOSE
    fprintf(stderr, "vrpn_Mutex_Remote::handle_initialize:  "
                    "Got assigned index %d.\n",
            me->d_myIndex);
#endif

    if (me->d_requestBeforeInit) {
#ifdef VERBOSE
        fprintf(stderr, "vrpn_Mutex_Remote::handle_initialize:  "
                        "Sending request\n");
#endif
        me->request();
    }

    return 0;
}