void
PeerDiscovery::DomainPeerDiscovery::listenerpack_thread()
{
    int stopfds_pipe[2];
#ifndef _WIN32
    if (pipe(stopfds_pipe) == -1)
        throw std::runtime_error(std::string("Can't open pipe: ") + strerror(errno));
#else
    net::udpPipe(stopfds_pipe);
#endif
    int stop_readfd = stopfds_pipe[0];
    stop_writefd_ = stopfds_pipe[1];

    while (true) {
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(stop_readfd, &readfds);
        FD_SET(sockfd_, &readfds);


        int data_coming = select(std::max(sockfd_, stop_readfd) + 1, &readfds, nullptr, nullptr, nullptr);

        {
            std::unique_lock<std::mutex> lck(dmtx_);
            if (not drunning_)
                break;
        }

        if (data_coming < 0) {
            if(errno != EINTR) {
                perror("Select Error");
                std::this_thread::sleep_for( std::chrono::seconds(1) );
            }
        } else if (data_coming > 0) {
            if (FD_ISSET(stop_readfd, &readfds)) {
                std::array<uint8_t, 64 * 1024> buf;
                recv(stop_readfd, (char*)buf.data(), buf.size(), 0);
            }

            try {
                auto rcv = recvFrom();
                msgpack::object obj = rcv.second.get();

                if (obj.type != msgpack::type::MAP)
                    continue;
                for (unsigned i = 0; i < obj.via.map.size; i++) {
                    auto& o = obj.via.map.ptr[i];
                    if (o.key.type != msgpack::type::STR)
                        continue;
                    auto key = o.key.as<std::string>();
                    ServiceDiscoveredCallback cb;
                    {
                        std::lock_guard<std::mutex> lck(dmtx_);
                        auto callback = callbackmap_.find(key);
                        if (callback != callbackmap_.end())
                            cb = callback->second;
                    }
                    if (cb)
                        cb(std::move(o.val), std::move(rcv.first));
                }
            } catch (const std::exception& e) {
                std::cerr << "Error receiving packet: " << e.what() << std::endl;
            }
        }
    }
    if (stop_readfd != -1)
        close(stop_readfd);
    if (stop_writefd_ != -1) {
        close(stop_writefd_);
        stop_writefd_ = -1;
    }
}