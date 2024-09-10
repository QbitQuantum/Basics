int64_t DoReq(SOCKET sockfd, socklen_t servlen, struct sockaddr cliaddr) {


#ifdef WIN32
    u_long nOne = 1;
    if (ioctlsocket(sockfd, FIONBIO, &nOne) == SOCKET_ERROR) {
        printf("ConnectSocket() : ioctlsocket non-blocking setting failed, error %d\n", WSAGetLastError());
#else
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == SOCKET_ERROR) {
        printf("ConnectSocket() : fcntl non-blocking setting failed, error %d\n", errno);
#endif
        return -2;
    }

    struct timeval timeout = {10, 0};
    struct pkt *msg = new pkt;
    struct pkt *prt  = new pkt;
    time_t seconds_transmit;
    int len = 48;

    msg->li_vn_mode=227;
    msg->stratum=0;
    msg->ppoll=4;
    msg->precision=0;
    msg->rootdelay=0;
    msg->rootdispersion=0;

    msg->ref.Ul_i.Xl_i=0;
    msg->ref.Ul_f.Xl_f=0;
    msg->org.Ul_i.Xl_i=0;
    msg->org.Ul_f.Xl_f=0;
    msg->rec.Ul_i.Xl_i=0;
    msg->rec.Ul_f.Xl_f=0;
    msg->xmt.Ul_i.Xl_i=0;
    msg->xmt.Ul_f.Xl_f=0;

    int retcode = sendto(sockfd, (char *) msg, len, 0, &cliaddr, servlen);
    if (retcode < 0) {
        printf("sendto() failed: %d\n", retcode);
        seconds_transmit = -3;
        goto _end;
    }

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    retcode = select(sockfd + 1, &fdset, NULL, NULL, &timeout);
    if (retcode <= 0) {
        printf("recvfrom() error\n");
        seconds_transmit = -4;
        goto _end;
    }

    recvfrom(sockfd, (char *) msg, len, 0, NULL, NULL);
    ntohl_fp(&msg->xmt, &prt->xmt);
    Ntp2Unix(prt->xmt.Ul_i.Xl_ui, seconds_transmit);

    _end:

    delete msg;
    delete prt;

    return seconds_transmit;
}

int64_t NtpGetTime(CNetAddr& ip) {
    struct sockaddr cliaddr;

    SOCKET sockfd;
    socklen_t servlen;

    if (!InitWithRandom(sockfd, servlen, &cliaddr))
        return -1;

    ip = CNetAddr(((sockaddr_in *)&cliaddr)->sin_addr);
    int64_t nTime = DoReq(sockfd, servlen, cliaddr);

    closesocket(sockfd);

    return nTime;
}

int64_t NtpGetTime(const std::string &strHostName)
{
    struct sockaddr cliaddr;

    SOCKET sockfd;
    socklen_t servlen;

    if (!InitWithHost(strHostName, sockfd, servlen, &cliaddr))
        return -1;

    int64_t nTime = DoReq(sockfd, servlen, cliaddr);

    closesocket(sockfd);

    return nTime;
}

// NTP server, which we unconditionally trust. This may be your own installation of ntpd somewhere, for example. 
// "localhost" means "trust no one"
std::string strTrustedUpstream = "localhost";

// Current offset
int64_t nNtpOffset = INT64_MAX;

int64_t GetNtpOffset() {
    return nNtpOffset;
}

void ThreadNtpSamples(void* parg) {
    const int64_t nMaxOffset = 86400; // Not a real limit, just sanity threshold.

    printf("Trying to find NTP server at localhost...\n");

    std::string strLocalHost = "127.0.0.1";
    if (NtpGetTime(strLocalHost) == GetTime()) {
        printf("There is NTP server active at localhost,  we don't need NTP thread.\n");

        nNtpOffset = 0;
        return;
    }

    printf("ThreadNtpSamples started\n");
    vnThreadsRunning[THREAD_NTP]++;

    // Make this thread recognisable as time synchronization thread
    RenameThread("eCoin-ntp-samples");

    CMedianFilter<int64_t> vTimeOffsets(200,0);

    while (!fShutdown) {
        if (strTrustedUpstream != "localhost") {
            // Trying to get new offset sample from trusted NTP server.
            int64_t nClockOffset = NtpGetTime(strTrustedUpstream) - GetTime();

            if (abs64(nClockOffset) < nMaxOffset) {
                // Everything seems right, remember new trusted offset.
                printf("ThreadNtpSamples: new offset sample from %s, offset=%" PRId64 ".\n", strTrustedUpstream.c_str(), nClockOffset);
                nNtpOffset = nClockOffset;
            }
            else {
                // Something went wrong, disable trusted offset sampling.
                nNtpOffset = INT64_MAX;
                strTrustedUpstream = "localhost";

                int nSleepMinutes = 1 + GetRandInt(9); // Sleep for 1-10 minutes.
                for (int i = 0; i < nSleepMinutes * 60 && !fShutdown; i++)
                    Sleep(1000);

                continue;
            }
        }
        else {
            // Now, trying to get 2-4 samples from random NTP servers.
            int nSamplesCount = 2 + GetRandInt(2);

            for (int i = 0; i < nSamplesCount; i++) {
                CNetAddr ip;
                int64_t nClockOffset = NtpGetTime(ip) - GetTime();

                if (abs64(nClockOffset) < nMaxOffset) { // Skip the deliberately wrong timestamps
                    printf("ThreadNtpSamples: new offset sample from %s, offset=%" PRId64 ".\n", ip.ToString().c_str(), nClockOffset);
                    vTimeOffsets.input(nClockOffset);
                }
            }

            if (vTimeOffsets.size() > 1) {
                nNtpOffset = vTimeOffsets.median();
            }
            else {
                // Not enough offsets yet, try to collect additional samples later.
                nNtpOffset = INT64_MAX;
                int nSleepMinutes = 1 + GetRandInt(4); // Sleep for 1-5 minutes.
                for (int i = 0; i < nSleepMinutes * 60 && !fShutdown; i++) 
                    Sleep(1000);
                continue;
            }
        }

        if (GetNodesOffset() == INT_MAX && abs64(nNtpOffset) > 40 * 60)
        {
            // If there is not enough node offsets data and NTP time offset is greater than 40 minutes then give a warning.
            std::string strMessage = _("Warning: Please check that your computer's date and time are correct! If your clock is wrong eCoin will not work properly.");
            strMiscWarning = strMessage;
            printf("*** %s\n", strMessage.c_str());
            uiInterface.ThreadSafeMessageBox(strMessage+" ", std::string("eCoin"), CClientUIInterface::OK | CClientUIInterface::ICON_EXCLAMATION);
        }

        printf("nNtpOffset = %+" PRId64 "  (%+" PRId64 " minutes)\n", nNtpOffset, nNtpOffset/60);

        int nSleepHours = 1 + GetRandInt(5); // Sleep for 1-6 hours.
        for (int i = 0; i < nSleepHours * 3600 && !fShutdown; i++)
            Sleep(1000);
    }

    vnThreadsRunning[THREAD_NTP]--;
    printf("ThreadNtpSamples exited\n");
}