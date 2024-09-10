int create_semaphore(key_t key){
    int id, retval;
    SEMUN s;

    id = semget(key, 1, IPC_CREAT|IPC_EXCL|0777);
    if (id < 0) {
        return ERR_SEMGET;
    }
    memset(&s, 0, sizeof(s));
    s.val = 1;
    retval = semctl(id, 0, SETVAL, s);
    if (retval) {
        return ERR_SEMCTL;
    }
    return 0;
}