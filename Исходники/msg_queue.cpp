int create_message_queue(key_t key) {
    int mq_id;

    mq_id = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    if (mq_id < 0) {
        perror("create_message_queue: msgget");
        return -1;
    }
    return 0;
}