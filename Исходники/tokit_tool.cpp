    // 将无符号64位整数转换为字符串
    // 例如：tostr(100123) = "100123"
    string tostr(uint64 n)
    {
        char buf[64] = {0};

#ifdef WIN32
        errno_t err = _ui64toa_s (n, buf, sizeof(buf), 10);
        if(err){
            return "";
        }

        return buf;
#else
        
        snprintf(buf, sizeof(buf), "%" PRIu64 "", n);

        // snprintf(buf, sizeof(buf), "%llu", n);
        return buf;
#endif
    }