Variant HHVM_FUNCTION(getprotobynumber, int64_t number) {
    Lock lock(NetworkMutex);

    struct protoent *ent = getprotobynumber(number);
    if (ent == NULL) {
        return false;
    }
    return String(ent->p_name, CopyString);
}