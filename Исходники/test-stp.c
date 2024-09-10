int
main(int argc, char *argv[])
{
    struct test_case *tc;
    FILE *input_file;
    int i;

    if (argc != 2) {
        ovs_fatal(0, "usage: test-stp INPUT.STP\n");
    }
    file_name = argv[1];

    input_file = fopen(file_name, "r");
    if (!input_file) {
        ovs_fatal(errno, "error opening \"%s\"", file_name);
    }

    tc = new_test_case();
    for (i = 0; i < 26; i++) {
        char name[2];
        name[0] = 'a' + i;
        name[1] = '\0';
        new_lan(tc, name);
    }

    for (line_number = 1; fgets(line, sizeof line, input_file);
         line_number++)
    {
        char *newline, *hash;

        newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }
        hash = strchr(line, '#');
        if (hash) {
            *hash = '\0';
        }

        pos = line;
        if (!get_token()) {
            continue;
        }
        if (match("bridge")) {
            struct bridge *bridge;
            int bridge_no, port_no;

            bridge_no = must_get_int();
            if (bridge_no < tc->n_bridges) {
                bridge = tc->bridges[bridge_no];
            } else if (bridge_no == tc->n_bridges) {
                bridge = new_bridge(tc, must_get_int());
            } else {
                err("bridges must be numbered consecutively from 0");
            }
            if (match("^")) {
                stp_set_bridge_priority(bridge->stp, must_get_int());
            }

            if (match("=")) {
                for (port_no = 0; port_no < STP_MAX_PORTS; port_no++) {
                    struct stp_port *p = stp_get_port(bridge->stp, port_no);
                    if (!token || match("X")) {
                        stp_port_disable(p);
                    } else if (match("_")) {
                        /* Nothing to do. */
                    } else {
                        struct lan *lan;
                        int path_cost;

                        if (!strcmp(token, "0")) {
                            lan = NULL;
                        } else if (strlen(token) == 1
                                && islower((unsigned char)*token)) {
                            lan = tc->lans[*token - 'a'];
                        } else {
                            err("%s is not a valid LAN name "
                                "(0 or a lowercase letter)", token);
                        }
                        get_token();

                        path_cost = match(":") ? must_get_int() : 10;
                        if (port_no < bridge->n_ports) {
                            stp_port_set_path_cost(p, path_cost);
                            stp_port_enable(p);
                            reconnect_port(bridge, port_no, lan);
                        } else if (port_no == bridge->n_ports) {
                            new_port(bridge, lan, path_cost);
                        } else {
                            err("ports must be numbered consecutively");
                        }
                        if (match("^")) {
                            stp_port_set_priority(p, must_get_int());
                        }
                    }
                }
            }
        } else if (match("run")) {
            simulate(tc, must_get_int());
        } else if (match("dump")) {
            dump(tc);
        } else if (match("tree")) {
            tree(tc);
        } else if (match("check")) {
            struct bridge *b;
            struct stp *stp;
            int bridge_no, port_no;

            bridge_no = must_get_int();
            if (bridge_no >= tc->n_bridges) {
                err("no bridge numbered %d", bridge_no);
            }
            b = tc->bridges[bridge_no];
            stp = b->stp;

            must_match("=");

            if (match("rootid")) {
                uint64_t rootid;
                must_match(":");
                rootid = must_get_int();
                if (match("^")) {
                    rootid |= (uint64_t) must_get_int() << 48;
                } else {
                    rootid |= UINT64_C(0x8000) << 48;
                }
                if (stp_get_designated_root(stp) != rootid) {
                    warn("%s: root %"PRIx64", not %"PRIx64,
                         stp_get_name(stp), stp_get_designated_root(stp),
                         rootid);
                }
            }

            if (match("root")) {
                if (stp_get_root_path_cost(stp)) {
                    warn("%s: root path cost of root is %u but should be 0",
                         stp_get_name(stp), stp_get_root_path_cost(stp));
                }
                if (!stp_is_root_bridge(stp)) {
                    warn("%s: root is %"PRIx64", not %"PRIx64,
                         stp_get_name(stp),
                         stp_get_designated_root(stp), stp_get_bridge_id(stp));
                }
                for (port_no = 0; port_no < b->n_ports; port_no++) {
                    struct stp_port *p = stp_get_port(stp, port_no);
                    enum stp_state state = stp_port_get_state(p);
                    if (!(state & (STP_DISABLED | STP_FORWARDING))) {
                        warn("%s: root port %d in state %s",
                             stp_get_name(b->stp), port_no,
                             stp_state_name(state));
                    }
                }
            } else {
                for (port_no = 0; port_no < STP_MAX_PORTS; port_no++) {
                    struct stp_port *p = stp_get_port(stp, port_no);
                    enum stp_state state;
                    if (token == NULL || match("D")) {
                        state = STP_DISABLED;
                    } else if (match("B")) {
                        state = STP_BLOCKING;
                    } else if (match("Li")) {
                        state = STP_LISTENING;
                    } else if (match("Le")) {
                        state = STP_LEARNING;
                    } else if (match("F")) {
                        state = STP_FORWARDING;
                    } else if (match("_")) {
                        continue;
                    } else {
                        err("unknown port state %s", token);
                    }
                    if (stp_port_get_state(p) != state) {
                        warn("%s port %d: state is %s but should be %s",
                             stp_get_name(stp), port_no,
                             stp_state_name(stp_port_get_state(p)),
                             stp_state_name(state));
                    }
                    if (state == STP_FORWARDING) {
                        struct stp_port *root_port = stp_get_root_port(stp);
                        if (match(":")) {
                            int root_path_cost = must_get_int();
                            if (p != root_port) {
                                warn("%s: port %d is not the root port",
                                     stp_get_name(stp), port_no);
                                if (!root_port) {
                                    warn("%s: (there is no root port)",
                                         stp_get_name(stp));
                                } else {
                                    warn("%s: (port %d is the root port)",
                                         stp_get_name(stp),
                                         stp_port_no(root_port));
                                }
                            } else if (root_path_cost
                                       != stp_get_root_path_cost(stp)) {
                                warn("%s: root path cost is %u, should be %d",
                                     stp_get_name(stp),
                                     stp_get_root_path_cost(stp),
                                     root_path_cost);
                            }
                        } else if (p == root_port) {
                            warn("%s: port %d is the root port but "
                                 "not expected to be",
                                 stp_get_name(stp), port_no);
                        }
                    }
                }
            }
            if (n_warnings) {
                exit(EXIT_FAILURE);
            }
        }
        if (get_token()) {
            err("trailing garbage on line");
        }
    }
    free(token);

    for (i = 0; i < tc->n_lans; i++) {
        struct lan *lan = tc->lans[i];
        free((char *) lan->name);
        free(lan);
    }
    for (i = 0; i < tc->n_bridges; i++) {
        struct bridge *bridge = tc->bridges[i];
        stp_destroy(bridge->stp);
        free(bridge);
    }
    free(tc);

    return 0;
}