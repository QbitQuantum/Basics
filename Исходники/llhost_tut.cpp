void host_object::test<9>()
{
    std::string hostStr = "google.com";
    LLHost host;
    host.setHostByName(hostStr);

    // reverse DNS will likely result in appending of some
    // sub-domain to the main hostname. so look for
    // the main domain name and not do the exact compare

    std::string hostname = host.getHostName();
    ensure("getHostName failed", hostname.find(hostStr) != std::string::npos);
}