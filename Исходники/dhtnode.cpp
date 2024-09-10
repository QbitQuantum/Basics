int
main(int argc, char **argv)
{
    DhtRunner dht;
    try {
        auto params = parseArgs(argc, argv);
        if (params.help) {
            print_usage();
            return 0;
        }

        // TODO: remove with GnuTLS >= 3.3
        int rc = gnutls_global_init();
        if (rc != GNUTLS_E_SUCCESS)
            throw std::runtime_error(std::string("Error initializing GnuTLS: ")+gnutls_strerror(rc));

        dht::crypto::Identity crt {};
        if (params.generate_identity) {
            auto ca_tmp = dht::crypto::generateIdentity("DHT Node CA");
            crt = dht::crypto::generateIdentity("DHT Node", ca_tmp);
        }
    
        dht.run(params.port, crt, true, params.is_bootstrap_node);

        if (params.log)
            enableLogging(dht);

        if (not params.bootstrap.first.empty()) {
            std::cout << "Bootstrap: " << params.bootstrap.first << ":" << params.bootstrap.second << std::endl;
            dht.bootstrap(params.bootstrap.first.c_str(), params.bootstrap.second.c_str());
        }

        print_node_info(dht, params);
        std::cout << " (type 'h' or 'help' for a list of possible commands)" << std::endl << std::endl;

        // using the GNU History API
        using_history();

        while (true)
        {
            // using the GNU Readline API
            std::string line = readLine();
            if (!line.empty() && line[0] == '\0')
                break;

            std::istringstream iss(line);
            std::string op, idstr, value;
            iss >> op >> idstr;

            if (op == "x" || op == "q" || op == "exit" || op == "quit") {
                break;
            } else if (op == "h" || op == "help") {
                print_help();
                continue;
            } else if (op == "ll") {
                print_node_info(dht, params);
                unsigned good4, dubious4, cached4, incoming4;
                unsigned good6, dubious6, cached6, incoming6;
                dht.getNodesStats(AF_INET, &good4, &dubious4, &cached4, &incoming4);
                dht.getNodesStats(AF_INET6, &good6, &dubious6, &cached6, &incoming6);
                std::cout << "IPv4 nodes : " << good4 << " good, " << dubious4 << " dubious, " << incoming4 << " incoming." << std::endl;
                std::cout << "IPv6 nodes : " << good6 << " good, " << dubious6 << " dubious, " << incoming6 << " incoming." << std::endl;
                continue;
            } else if (op == "lr") {
                std::cout << "IPv4 routing table:" << std::endl;
                std::cout << dht.getRoutingTablesLog(AF_INET) << std::endl;
                std::cout << "IPv6 routing table:" << std::endl;
                std::cout << dht.getRoutingTablesLog(AF_INET6) << std::endl;
                continue;
            } else if (op == "ld") {
                std::cout << dht.getStorageLog() << std::endl;
                continue;
            } else if (op == "ls") {
                std::cout << "Searches:" << std::endl;
                std::cout << dht.getSearchesLog() << std::endl;
                continue;
            } else if (op == "la")  {
                std::cout << "Reported public addresses:" << std::endl;
                auto addrs = dht.getPublicAddressStr();
                for (const auto& addr : addrs)
                    std::cout << addr << std::endl;
                continue;
            } else if (op == "b") {
                try {
                    auto addr = splitPort(idstr);
                    if (not addr.first.empty() and addr.second.empty())
                        addr.second = std::to_string(DHT_DEFAULT_PORT);
                    dht.bootstrap(addr.first.c_str(), addr.second.c_str());
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
                continue;
            } else if (op == "log") {
                params.log = !params.log;
                if (params.log)
                    enableLogging(dht);
                else
                    disableLogging(dht);
                continue;
            }

            if (op.empty())
                continue;

            dht::InfoHash id {idstr};
            static const std::set<std::string> VALID_OPS {"g", "l", "p", "s", "e", "a"};
            if (VALID_OPS.find(op) == VALID_OPS.cend()) {
                std::cout << "Unknown command: " << op << std::endl;
                std::cout << " (type 'h' or 'help' for a list of possible commands)" << std::endl;
                continue;
            }
            static constexpr dht::InfoHash INVALID_ID {};
            if (id == INVALID_ID) {
                std::cout << "Syntax error: invalid InfoHash." << std::endl;
                continue;
            }

            auto start = std::chrono::high_resolution_clock::now();
            if (op == "g") {
                dht.get(id, [start](std::shared_ptr<Value> value) {
                    auto now = std::chrono::high_resolution_clock::now();
                    std::cout << "Get: found value (after " << print_dt(now-start) << "s)" << std::endl;
                    std::cout << "\t" << *value << std::endl;
                    return true;
                }, [start](bool ok) {
                    auto end = std::chrono::high_resolution_clock::now();
                    std::cout << "Get: " << (ok ? "completed" : "failure") << " (took " << print_dt(end-start) << "s)" << std::endl;
                });
            }
            else if (op == "l") {
                std::cout << id << std::endl;
                dht.listen(id, [](std::shared_ptr<Value> value) {
                    std::cout << "Listen: found value:" << std::endl;
                    std::cout << "\t" << *value << std::endl;
                    return true;
                });
            }
            else if (op == "p") {
                std::string v;
                iss >> v;
                dht.put(id, dht::Value {
                    dht::ValueType::USER_DATA.id,
                    std::vector<uint8_t> {v.begin(), v.end()}
                }, [start](bool ok) {
                    auto end = std::chrono::high_resolution_clock::now();
                    std::cout << "Put: " << (ok ? "success" : "failure") << " (took " << print_dt(end-start) << "s)" << std::endl;
                });
            }
            else if (op == "s") {
                if (not params.generate_identity) {
                    print_id_req();
                    continue;
                }
                std::string v;
                iss >> v;
                dht.putSigned(id, dht::Value {
                    dht::ValueType::USER_DATA.id,
                    std::vector<uint8_t> {v.begin(), v.end()}
                }, [start](bool ok) {
                    auto end = std::chrono::high_resolution_clock::now();
                    std::cout << "Put signed: " << (ok ? "success" : "failure") << " (took " << print_dt(end-start) << "s)" << std::endl;
                });
            }
            else if (op == "e") {