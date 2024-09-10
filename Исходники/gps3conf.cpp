// not thread safe!!
// Called only once.
bool InitConfig(const char* conf_path,
                const char* section /*unused currently*/) {
    if (!conf_path) {
        // empty path, log error
        return false;
    }

    if (!s3cfg) {
        s3cfg = new Config(conf_path);
        if (!s3cfg) {
// create s3cfg fail
// log error
#ifndef DEBUGS3
            write_log("failed to parse config file\n");
#endif
            return false;
        }
    }

    Config* cfg = s3cfg;
    bool ret = false;
    string content;
    content = cfg->Get("default", "loglevel", "INFO");
    s3ext_loglevel = getLogLevel(content.c_str());

    content = cfg->Get("default", "logtype", "INTERNAL");
    s3ext_logtype = getLogType(content.c_str());

    s3ext_accessid = cfg->Get("default", "accessid", "");
    s3ext_secret = cfg->Get("default", "secret", "");
    s3ext_token = cfg->Get("default", "token", "");

#ifdef DEBUGS3
// s3ext_loglevel = EXT_DEBUG;
// s3ext_logtype = LOCAL_LOG;
#endif

    s3ext_logpath = cfg->Get("default", "logpath", "/tmp/.s3log.sock");
    s3ext_logserverhost = cfg->Get("default", "logserverhost", "127.0.0.1");

    ret = cfg->Scan("default", "logserverport", "%d", &s3ext_logserverport);
    if (!ret) {
        s3ext_logserverport = 1111;
    }

    ret = cfg->Scan("default", "threadnum", "%d", &s3ext_threadnum);
    if (!ret) {
        S3INFO("failed to get thread number, use default value 4");
        s3ext_threadnum = 4;
    }

    ret = cfg->Scan("default", "chunksize", "%d", &s3ext_chunksize);
    if (!ret) {
        S3INFO("failed to get chunksize, use default value %d",
               64 * 1024 * 1024);
        s3ext_chunksize = 64 * 1024 * 1024;
    }

    ret = cfg->Scan("default", "low_speed_limit", "%d", &s3ext_low_speed_limit);
    if (!ret) {
        s3ext_low_speed_limit = 1024;
    }

    ret = cfg->Scan("default", "low_speed_time", "%d", &s3ext_low_speed_time);
    if (!ret) {
        s3ext_low_speed_time = 60;
    }

    content = cfg->Get("default", "encryption", "true");
    s3ext_encryption = to_bool(content);

#ifdef DEBUGS3
    s3ext_segid = 0;
    s3ext_segnum = 1;
#else
    s3ext_segid = GpIdentity.segindex;
    s3ext_segnum = GpIdentity.numsegments;
#endif
    return true;
}