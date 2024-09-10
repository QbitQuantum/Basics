// not thread safe!!
// invoked by s3_import(), need to be exception safe
bool InitConfig(string conf_path, string section /*not used currently*/) {
    try {
        if (conf_path == "") {
#ifndef DEBUG_S3
            write_log("Config file is not specified\n");
#endif
            return false;
        }

        if (s3cfg) delete s3cfg;

        s3cfg = new Config(conf_path);
        if (!s3cfg || !s3cfg->Handle()) {
#ifndef DEBUG_S3
            write_log("Failed to parse config file\n");
#endif
            if (s3cfg) {
                delete s3cfg;
                s3cfg = NULL;
            }
            return false;
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

#ifdef DEBUG_S3
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
            S3INFO("Failed to get thread number, use default value 4");
            s3ext_threadnum = 4;
        }
        if (s3ext_threadnum > 8) {
            S3INFO("The given thread number is too big, use max value 8");
            s3ext_threadnum = 8;
        }
        if (s3ext_threadnum < 1) {
            S3INFO("The given thread number is too small, use min value 1");
            s3ext_threadnum = 1;
        }

        ret = cfg->Scan("default", "chunksize", "%d", &s3ext_chunksize);
        if (!ret) {
            S3INFO("Failed to get chunksize, use default value 64MB");
            s3ext_chunksize = 64 * 1024 * 1024;
        }
        if (s3ext_chunksize > 128 * 1024 * 1024) {
            S3INFO("The given chunksize is too large, use max value 128MB");
            s3ext_chunksize = 128 * 1024 * 1024;
        }
        if (s3ext_chunksize < 2 * 1024 * 1024) {
            S3INFO("The given chunksize is too small, use min value 2MB");
            s3ext_chunksize = 2 * 1024 * 1024;
        }

        ret = cfg->Scan("default", "low_speed_limit", "%d",
                        &s3ext_low_speed_limit);
        if (!ret) {
            S3INFO(
                "Failed to get low_speed_limit, use default value %d bytes/s",
                10240);
            s3ext_low_speed_limit = 10240;
        }

        ret =
            cfg->Scan("default", "low_speed_time", "%d", &s3ext_low_speed_time);
        if (!ret) {
            S3INFO("Failed to get low_speed_time, use default value %d seconds",
                   60);
            s3ext_low_speed_time = 60;
        }

        content = cfg->Get("default", "encryption", "true");
        s3ext_encryption = to_bool(content);

#ifdef DEBUG_S3
        s3ext_segid = 0;
        s3ext_segnum = 1;
#else
        s3ext_segid = GpIdentity.segindex;
        s3ext_segnum = GpIdentity.numsegments;
#endif
    } catch (...) {
        return false;
    }

    return true;
}