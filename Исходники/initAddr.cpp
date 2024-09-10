PRStatus
initAddr (PRNetAddr* addr, const char* host, int port = -1)
{
    std::string sHost = host;
 
    if (PR_StringToNetAddr(sHost.c_str(), addr) == PR_FAILURE) {
        std::string sIp;
        std::string sPort;
 
        if (sHost[0] == '[') {
            sIp = sHost.substr(1, sHost.find_last_of("]")-1);
            sPort = sHost.substr(sHost.find_last_of("]")+2);
        }
        else {
            sIp = sHost.substr(0, sHost.find_last_of(":"));
            sPort = sHost.substr(sHost.find_last_of(":")+1);
        }

        if (!sPort.empty()) {
            int tmp = atoi(sPort.c_str());

            if (tmp >= 1 && tmp <= 65536) {
                port = tmp;
            }
        }
 
        if (PR_StringToNetAddr(sIp.c_str(), addr) == PR_FAILURE) {
            char* ip = getHostByName(sIp.c_str());

            if (ip == NULL) {
                return PR_FAILURE;
            }

            sIp = ip; delete [] ip;
 
            if (PR_StringToNetAddr(sIp.c_str(), addr) == PR_FAILURE) {
                return PR_FAILURE;
            }
        }
    }
 
    if (port >= 1 && port <= 65536) {
        PR_InitializeNetAddr(PR_IpAddrNull, port, addr);
    }
 
    return PR_SUCCESS;
}