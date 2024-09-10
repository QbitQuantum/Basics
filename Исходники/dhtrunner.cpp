void
DhtRunner::run(const char* ip4, const char* ip6, const char* service, const crypto::Identity identity, bool threaded, StatusCallback cb)
{
    auto res4 = getAddrInfo(ip4, service);
    auto res6 = getAddrInfo(ip6, service);
    run(res4.empty() ? nullptr : (sockaddr_in*) &res4.front().first,
        res6.empty() ? nullptr : (sockaddr_in6*)&res6.front().first, identity, threaded, cb);
}