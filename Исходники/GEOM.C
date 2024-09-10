char* grist_point_ser(grist_point* p, size_t* sz) {
    size_t newsz = sizeof(grist_coord);
    char* serialized = malloc(newsz);
    assert(serialized);
    uint64_t x;
    uint64_t y;
    uint64_t z;
    x = htonll(dtoll(p->coord->x));
    y = htonll(dtoll(p->coord->y));
    z = htonll(dtoll(p->coord->z));
    memcpy(serialized, &x, sizeof(uint64_t));
    size_t offset = sizeof(uint64_t);
    memcpy((serialized+offset), &y, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    memcpy((serialized+offset), &z, sizeof(uint64_t));
    *sz = newsz;
    return serialized;
}