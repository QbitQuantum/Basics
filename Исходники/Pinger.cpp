std::vector<double> Pinger::runPingProcessInstance(const uint16_t requestCount, const double delay){
    std::vector<double> result;
    this->progressMutex.lock();
    this->progress = 0;
    this->progressMutex.unlock();
    double progressStep = 1.0 / requestCount;

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(iResult != 0)
        throw std::runtime_error("WSAStartup failed");

    PDNS_RECORD dnsResultPtr;
    DNS_STATUS dnsStatus = DnsQuery_UTF8(this->host.c_str(), DNS_TYPE_A, DNS_QUERY_STANDARD, nullptr, &dnsResultPtr, nullptr);
    if(dnsStatus != DNS_RCODE_NOERROR)
        throw std::runtime_error("DnsQuery error");

    IP4_ADDRESS ip = dnsResultPtr->Data.A.IpAddress;

    HANDLE hIcmp = IcmpCreateFile();
    if(hIcmp == INVALID_HANDLE_VALUE)
        throw std::runtime_error("IcmpCreateFile error");

    char SendData[32];
    DWORD ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    LPVOID ReplyBuffer = reinterpret_cast<LPVOID>(malloc(ReplySize));
    if(ReplyBuffer == nullptr)
        throw std::runtime_error("malloc error");

    std::chrono::duration<int, std::milli> pingDelay(static_cast<int>(delay * 1000));

    for(uint32_t i = 0; i < requestCount && this->stopFlag == false; ++i){
        auto lastTime = std::chrono::high_resolution_clock::now();

        DWORD resIcmp = IcmpSendEcho(hIcmp, ip, SendData, sizeof(SendData), nullptr, ReplyBuffer, ReplySize, 1000);
        if(resIcmp == 0)
            throw std::runtime_error("IcmpSendEcho error");

        PICMP_ECHO_REPLY pReply = reinterpret_cast<PICMP_ECHO_REPLY>(ReplyBuffer);

        result.push_back(pReply->RoundTripTime);

        this->progressMutex.lock();
        if(this->progress + progressStep <= 1.0){//если шагов больше чем requestCount - не переполняем счетчик
            this->progress += progressStep;
        }
        this->progressMutex.unlock();

        if(i < requestCount)
            std::this_thread::sleep_until(lastTime + pingDelay);
    }

    if(this->stopFlag == false){
        this->progressMutex.lock();
        this->progress = 1.0;
        this->progressMutex.unlock();
    }

    return result;
}