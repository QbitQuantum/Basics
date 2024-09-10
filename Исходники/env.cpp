Handle<Value> EnvWrap::open(const Arguments& args) {
    HandleScope scope;
    int rc;
    int flags = 0;
    
    // Get the wrapper
    EnvWrap *ew = ObjectWrap::Unwrap<EnvWrap>(args.This());
    
    if (!ew->env) {
        ThrowException(Exception::Error(String::New("The environment is already closed.")));
        return Undefined();
    }
    
    Local<Object> options = args[0]->ToObject();
    Local<String> path = options->Get(String::NewSymbol("path"))->ToString();
    
    rc = applyUint32Setting(&mdb_env_set_maxdbs, ew->env, options, 1, "maxDbs");
    if (rc != 0) {
        ThrowException(Exception::Error(String::New(mdb_strerror(rc))));
        return Undefined();
    }
    
    rc = applyUint32Setting(&mdb_env_set_mapsize, ew->env, options, 10485760, "mapSize");
    if (rc != 0) {
        ThrowException(Exception::Error(String::New(mdb_strerror(rc))));
        return Undefined();
    }

    // TODO: expose mdb_env_set_maxreaders
    
    // NOTE: MDB_FIXEDMAP is not exposed here since it is "highly experimental" + it is irrelevant for this use case
    // NOTE: MDB_NOTLS is not exposed here because it is irrelevant for this use case, as node will run all this on a single thread anyway
    setFlagFromValue(&flags, MDB_NOSUBDIR, "noSubdir", false, options);
    setFlagFromValue(&flags, MDB_RDONLY, "readOnly", false, options);
    setFlagFromValue(&flags, MDB_WRITEMAP, "useWritemap", false, options);
    setFlagFromValue(&flags, MDB_NOMETASYNC, "noMetaSync", false, options);
    setFlagFromValue(&flags, MDB_NOSYNC, "noSync", false, options);
    setFlagFromValue(&flags, MDB_MAPASYNC, "mapAsync", false, options);
    
    int l = path->Length();
    char *cpath = new char[l + 1];
    path->WriteAscii(cpath);
    cpath[l] = 0;
    
    // TODO: make file attributes configurable
    rc = mdb_env_open(ew->env, cpath, flags, 0664);
    
    if (rc != 0) {
        mdb_env_close(ew->env);
        ew->env = NULL;
        ThrowException(Exception::Error(String::New(mdb_strerror(rc))));
        return Undefined();
    }
    
    return Undefined();
}