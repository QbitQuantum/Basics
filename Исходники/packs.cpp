size_t getMachineShard(const std::string& hostname = "", bool force = false) {
    static size_t shard = 0;
    if (shard > 0 && !force) {
        return shard;
    }

    // An optional input hostname may override hostname detection for testing.
    auto hn = (hostname.empty()) ? getHostname() : hostname;
    auto hn_hash = hashFromBuffer(HASH_TYPE_MD5, hn.c_str(), hn.size());
    if (hn_hash.size() >= 2) {
        long hn_char;
        if (safeStrtol(hn_hash.substr(0, 2), 16, hn_char)) {
            shard = (hn_char * 100) / 255;
        }
    }
    return shard;
}