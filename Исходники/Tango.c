tango_connection_t *tango_create(const char *share, const char* username, const char *password) {
    static unsigned short next_mid = 0;

    tango_connection_t *tango_connection_ptr = malloc(sizeof(tango_connection_t));
    if (tango_connection_ptr == NULL) {
        _tango_set_error(tango_connection_ptr, kTangoErrorGeneralSystemError, "tango_create(): Unable to malloc mem.\n");
        error("tango_create(): Unable to malloc mem.\n");
        return NULL;
    }

    // Null it
    memset(tango_connection_ptr, 0, sizeof(tango_connection_t));

    // Create a socket
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        _tango_set_error(tango_connection_ptr, kTangoErrorGeneralSystemError, "tango_create(): Failed to create socket().\n");
        debug("tango_create(): Failed to create socket().\n");
        goto bailout;
    }

    tango_connection_ptr->socket = sock;
    struct sockaddr_in sock_addr;

    // Parse share-string
    if (strncmp(share, "\\\\", 2) != 0 || strlen(share) < 3) {
        _tango_set_error(tango_connection_ptr, kTangoErrorParameterInvalid, "tango_create(): Passed parameter not a valid share.\n");
        debug("tango_create(): Passed parameter not a valid share.\n");
        goto bailout;
    }

    const char *begin_ptr = share + 2;
    char *end_ptr = strchr(begin_ptr, '\\');


    // Form: \\hostname\share
    char hostname[64];
    assert(strlen(begin_ptr) < 64 && "Hostname longer than 64 bytes");
    strncpy(hostname, begin_ptr, end_ptr - begin_ptr);
    hostname[end_ptr - begin_ptr] = '\0';
    sock_addr.sin_addr = address_for_host(hostname);
    int sin_addr_set = sock_addr.sin_addr.s_addr != INADDR_NONE;

    if (!sin_addr_set) {
        _tango_set_error(tango_connection_ptr, kTangoErrorParameterInvalid, "tango_create(): Invalid share.\n");
        error("tango_create(): Passed parameter not a valid share or contains no valid hostname/IP.\n");
        goto bailout;
    }


    char *slash_ptr = strchr(share + 2, '\\');
    slash_ptr = strchr(slash_ptr + 1, '\\');
    if (slash_ptr != NULL) {
        // Format: \\hostname\share\subfolder
        unsigned int slash_idx = slash_ptr - share;
        strncpy(tango_connection_ptr->share, share, slash_idx);
        tango_connection_ptr->share[slash_idx + 1] = '\0';
    }
    else {
        // Format: \\hostname\share
        slash_ptr = strchr(share + 2, '\\');
        strcpy(tango_connection_ptr->share, slash_ptr+1);
    }

    // Configure port and connection-type
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(445); // Default-port for SMB over TCP/IP without NetBios

    tango_connection_ptr->sock_addr = sock_addr;

    // Set our Ids
    tango_connection_ptr->pid = 0x1234;
    tango_connection_ptr->mid = next_mid++;

    // Store username and password
    strcpy(tango_connection_ptr->user_name, username);
    strcpy(tango_connection_ptr->user_password, password);

    return tango_connection_ptr;

bailout:
    free(tango_connection_ptr);
    return NULL;
}