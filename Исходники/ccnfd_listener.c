static void * publish_response(void * arg)
{
    prctl(PR_SET_NAME, "ccnfd_pub", 0, 0, 0);
    log_print(g_log, "publish_response: handling publish request");
    int sock;
    memcpy(&sock, (int * )arg, sizeof(int));
    free(arg);

    struct content_obj * content;
    content = (struct content_obj *) malloc(sizeof(struct content_obj));

    /* finish rcving the summary request packet */
    /* structure  of publish msg:
     * publisher : int
     * name_len : int
     * name : char[name_len]
     * timestamp : int
     * size : int
     * data : byte[size]
     */
    uint32_t publisher;
    uint32_t payload_size;
    uint32_t name_len;
    uint8_t name[MAX_NAME_LENGTH];
    uint32_t timestamp;
    uint32_t size;
    uint8_t * data = NULL;

    if (recv(sock, &payload_size, sizeof(uint32_t), 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }

    if (recv(sock, &publisher, sizeof(uint32_t), 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }

    if (recv(sock, &name_len, sizeof(uint32_t), 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }
    if (name_len > MAX_NAME_LENGTH)
        name_len = MAX_NAME_LENGTH - 1;

    if (recv(sock, name, name_len, 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }
    name[name_len] = '\0';

    if (recv(sock, &timestamp, sizeof(uint32_t), 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }

    if (recv(sock, &size, sizeof(uint32_t), 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }

    data = (uint8_t *) malloc(size);
    if (recv(sock, data, size, 0) == -1) {
        log_error(g_log, "recv: %s.", strerror(errno));
        free(data);
        goto END_PUBLISH_RESP;
    }

    content->name = content_name_create((char * )name);
    content->publisher = publisher;
    content->size = size;
    content->timestamp = timestamp;
    content->data = data;

    int rv = CS_put(content);
    if (send(sock, &rv, sizeof(uint32_t), 0) == -1) {
        log_print(g_log, "recv: %s.", strerror(errno));
        goto END_PUBLISH_RESP;
    }

    log_print(g_log, "Successfully published content:\n"
                 "\t\t\t\t\t\tname = %s\n"
                 "\t\t\t\t\t\ttimestamp = %d\n"
                 "\t\t\t\t\t\tsize = %d",
          name, timestamp , size);

    END_PUBLISH_RESP:

    close(sock);
    return NULL;
}