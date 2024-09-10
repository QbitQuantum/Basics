int zmq::socket_base_t::connect (const char *addr_)
{
    ENTER_MUTEX();

    if (unlikely (ctx_terminated)) {
        errno = ETERM;
        EXIT_MUTEX();
        return -1;
    }

    //  Process pending commands, if any.
    int rc = process_commands (0, false);
    if (unlikely (rc != 0)) {
        EXIT_MUTEX();
        return -1;
    }

    //  Parse addr_ string.
    std::string protocol;
    std::string address;
    if (parse_uri (addr_, protocol, address) || check_protocol (protocol)) {
        EXIT_MUTEX();
        return -1;
    }

    if (protocol == "inproc") {

        //  TODO: inproc connect is specific with respect to creating pipes
        //  as there's no 'reconnect' functionality implemented. Once that
        //  is in place we should follow generic pipe creation algorithm.

        //  Find the peer endpoint.
        endpoint_t peer = find_endpoint (addr_);

        // The total HWM for an inproc connection should be the sum of
        // the binder's HWM and the connector's HWM.
        int sndhwm = 0;
        if (peer.socket == NULL)
            sndhwm = options.sndhwm;
        else if (options.sndhwm != 0 && peer.options.rcvhwm != 0)
            sndhwm = options.sndhwm + peer.options.rcvhwm;
        int rcvhwm = 0;
        if (peer.socket == NULL)
            rcvhwm = options.rcvhwm;
        else
        if (options.rcvhwm != 0 && peer.options.sndhwm != 0)
            rcvhwm = options.rcvhwm + peer.options.sndhwm;

        //  Create a bi-directional pipe to connect the peers.
        object_t *parents [2] = {this, peer.socket == NULL ? this : peer.socket};
        pipe_t *new_pipes [2] = {NULL, NULL};

        bool conflate = options.conflate &&
            (options.type == ZMQ_DEALER ||
             options.type == ZMQ_PULL ||
             options.type == ZMQ_PUSH ||
             options.type == ZMQ_PUB ||
             options.type == ZMQ_SUB);

        int hwms [2] = {conflate? -1 : sndhwm, conflate? -1 : rcvhwm};
        bool conflates [2] = {conflate, conflate};
        int rc = pipepair (parents, new_pipes, hwms, conflates);
        if (!conflate) {
            new_pipes[0]->set_hwms_boost(peer.options.sndhwm, peer.options.rcvhwm);
            new_pipes[1]->set_hwms_boost(options.sndhwm, options.rcvhwm);
        }

        errno_assert (rc == 0);

        if (!peer.socket) {
            //  The peer doesn't exist yet so we don't know whether
            //  to send the identity message or not. To resolve this,
            //  we always send our identity and drop it later if
            //  the peer doesn't expect it.
            msg_t id;
            rc = id.init_size (options.identity_size);
            errno_assert (rc == 0);
            memcpy (id.data (), options.identity, options.identity_size);
            id.set_flags (msg_t::identity);
            bool written = new_pipes [0]->write (&id);
            zmq_assert (written);
            new_pipes [0]->flush ();

            const endpoint_t endpoint = {this, options};
            pend_connection (std::string (addr_), endpoint, new_pipes);
        }
        else {
            //  If required, send the identity of the local socket to the peer.
            if (peer.options.recv_identity) {
                msg_t id;
                rc = id.init_size (options.identity_size);
                errno_assert (rc == 0);
                memcpy (id.data (), options.identity, options.identity_size);
                id.set_flags (msg_t::identity);
                bool written = new_pipes [0]->write (&id);
                zmq_assert (written);
                new_pipes [0]->flush ();
            }

            //  If required, send the identity of the peer to the local socket.
            if (options.recv_identity) {
                msg_t id;
                rc = id.init_size (peer.options.identity_size);
                errno_assert (rc == 0);
                memcpy (id.data (), peer.options.identity, peer.options.identity_size);
                id.set_flags (msg_t::identity);
                bool written = new_pipes [1]->write (&id);
                zmq_assert (written);
                new_pipes [1]->flush ();
            }

            //  Attach remote end of the pipe to the peer socket. Note that peer's
            //  seqnum was incremented in find_endpoint function. We don't need it
            //  increased here.
            send_bind (peer.socket, new_pipes [1], false);
        }

        //  Attach local end of the pipe to this socket object.
        attach_pipe (new_pipes [0]);

        // Save last endpoint URI
        last_endpoint.assign (addr_);

        // remember inproc connections for disconnect
        inprocs.insert (inprocs_t::value_type (std::string (addr_), new_pipes [0]));

        options.connected = true;
        EXIT_MUTEX();
        return 0;
    }
    bool is_single_connect = (options.type == ZMQ_DEALER ||
                              options.type == ZMQ_SUB ||
                              options.type == ZMQ_REQ);
    if (unlikely (is_single_connect)) {
        const endpoints_t::iterator it = endpoints.find (addr_);
        if (it != endpoints.end ()) {
            // There is no valid use for multiple connects for SUB-PUB nor
            // DEALER-ROUTER nor REQ-REP. Multiple connects produces
            // nonsensical results.
            EXIT_MUTEX();
            return 0;
        }
    }

    //  Choose the I/O thread to run the session in.
    io_thread_t *io_thread = choose_io_thread (options.affinity);
    if (!io_thread) {
        errno = EMTHREAD;
        EXIT_MUTEX();
        return -1;
    }

    address_t *paddr = new (std::nothrow) address_t (protocol, address);
    alloc_assert (paddr);

    //  Resolve address (if needed by the protocol)
    if (protocol == "tcp") {
        //  Do some basic sanity checks on tcp:// address syntax
        //  - hostname starts with digit or letter, with embedded '-' or '.'
        //  - IPv6 address may contain hex chars and colons.
        //  - IPv4 address may contain decimal digits and dots.
        //  - Address must end in ":port" where port is *, or numeric
        //  - Address may contain two parts separated by ':'
        //  Following code is quick and dirty check to catch obvious errors,
        //  without trying to be fully accurate.
        const char *check = address.c_str ();
        if (isalnum (*check) || isxdigit (*check) || *check == '[') {
            check++;
            while (isalnum  (*check)
                || isxdigit (*check)
                || *check == '.' || *check == '-' || *check == ':'|| *check == ';'
                || *check == ']')
                check++;
        }
        //  Assume the worst, now look for success
        rc = -1;
        //  Did we reach the end of the address safely?
        if (*check == 0) {
            //  Do we have a valid port string? (cannot be '*' in connect
            check = strrchr (address.c_str (), ':');
            if (check) {
                check++;
                if (*check && (isdigit (*check)))
                    rc = 0;     //  Valid
            }
        }
        if (rc == -1) {
            errno = EINVAL;
            LIBZMQ_DELETE(paddr);
            EXIT_MUTEX();
            return -1;
        }
        //  Defer resolution until a socket is opened
        paddr->resolved.tcp_addr = NULL;
    }
#if !defined ZMQ_HAVE_WINDOWS && !defined ZMQ_HAVE_OPENVMS
    else
    if (protocol == "ipc") {
        paddr->resolved.ipc_addr = new (std::nothrow) ipc_address_t ();
        alloc_assert (paddr->resolved.ipc_addr);
        int rc = paddr->resolved.ipc_addr->resolve (address.c_str ());
        if (rc != 0) {
            LIBZMQ_DELETE(paddr);
            EXIT_MUTEX();
            return -1;
        }
    }
#endif

// TBD - Should we check address for ZMQ_HAVE_NORM???

#ifdef ZMQ_HAVE_OPENPGM
    if (protocol == "pgm" || protocol == "epgm") {
        struct pgm_addrinfo_t *res = NULL;
        uint16_t port_number = 0;
        int rc = pgm_socket_t::init_address(address.c_str(), &res, &port_number);
        if (res != NULL)
            pgm_freeaddrinfo (res);
        if (rc != 0 || port_number == 0) {
          EXIT_MUTEX();
          return -1;
        }
    }
#endif
#if defined ZMQ_HAVE_TIPC
    else
    if (protocol == "tipc") {
        paddr->resolved.tipc_addr = new (std::nothrow) tipc_address_t ();
        alloc_assert (paddr->resolved.tipc_addr);
        int rc = paddr->resolved.tipc_addr->resolve (address.c_str());
        if (rc != 0) {
            LIBZMQ_DELETE(paddr);
            EXIT_MUTEX();
            return -1;
        }
    }
#endif

    //  Create session.
    session_base_t *session = session_base_t::create (io_thread, true, this,
        options, paddr);
    errno_assert (session);

    //  PGM does not support subscription forwarding; ask for all data to be
    //  sent to this pipe. (same for NORM, currently?)
    bool subscribe_to_all = protocol == "pgm" || protocol == "epgm" || protocol == "norm";
    pipe_t *newpipe = NULL;

    if (options.immediate != 1 || subscribe_to_all) {
        //  Create a bi-directional pipe.
        object_t *parents [2] = {this, session};
        pipe_t *new_pipes [2] = {NULL, NULL};

        bool conflate = options.conflate &&
            (options.type == ZMQ_DEALER ||
             options.type == ZMQ_PULL ||
             options.type == ZMQ_PUSH ||
             options.type == ZMQ_PUB ||
             options.type == ZMQ_SUB);

        int hwms [2] = {conflate? -1 : options.sndhwm,
            conflate? -1 : options.rcvhwm};
        bool conflates [2] = {conflate, conflate};
        rc = pipepair (parents, new_pipes, hwms, conflates);
        errno_assert (rc == 0);

        //  Attach local end of the pipe to the socket object.
        attach_pipe (new_pipes [0], subscribe_to_all);
        newpipe = new_pipes [0];

        //  Attach remote end of the pipe to the session object later on.
        session->attach_pipe (new_pipes [1]);
    }

    //  Save last endpoint URI
    paddr->to_string (last_endpoint);

    add_endpoint (addr_, (own_t *) session, newpipe);
    EXIT_MUTEX();
    return 0;
}