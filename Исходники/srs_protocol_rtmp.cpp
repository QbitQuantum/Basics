int SrsHandshakeBytes::create_c2()
{
    int ret = ERROR_SUCCESS;
    
    if (c2) {
        return ret;
    }
    
    c2 = new char[1536];
    srs_random_generate(c2, 1536);
    
    // time
    SrsStream stream;
    if ((ret = stream.initialize(c2, 8)) != ERROR_SUCCESS) {
        return ret;
    }
    stream.write_4bytes(::time(NULL));
    // c2 time2 copy from s1
    if (s0s1s2) {
        stream.write_bytes(s0s1s2 + 1, 4);
    }
    
    return ret;
}