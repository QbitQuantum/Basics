void * perform_scan(void * args) {
    ps_args_t* ps_args = ((ps_args_t *) args);
    string ip = "ip";
    int port = 0;
    while (ip != "finish" && port != -1) {
        get_next_ip_port(*ps_args, ip, port);
        if (ip == "finish" && port == -1) {
            return NULL;
        }
        for (int s = 0; s < 6; s++) {
            if (ps_args->scans[s] == 1) {
                Scan sc = Scan();
                sc.ipToScan = ip;
                sc.port = htons(port);
                //sc.scanVector = vector<ScanType>();
                switch (s) {
                    case SYN:
                        sc.cScan = SYN;

                        sc.runTcpScan();
                        break;
                    case NUL:
                        sc.cScan = NUL;

                        sc.runTcpScan();
                        break;
                    case FIN:
                        sc.cScan = FIN;

                        sc.runTcpScan();
                        break;
                    case XMAS:
                        sc.cScan = XMAS;

                        sc.runTcpScan();
                        break;
                    case ACK:
                        sc.cScan = ACK;

                        sc.runTcpScan();
                        break;
                    case UDP:
                        sc.cScan = UDP;
                        sc.runUdpScan();
                        break;
                }
                pthread_mutex_lock(&arrMutex);
                scanArray.push_back(sc);
                pthread_mutex_unlock(&arrMutex);
            }
        }
    }
    return NULL;
}