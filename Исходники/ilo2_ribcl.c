/**
 * ilo2_ribcl_open: open (initiate) instance of the iLO2 RIBCL plug-in
 * @handler_config: Pointer to openhpi config file.
 *
 * This function opens an instance of the iLO2 RIBCL plugin.
 * Detailed description:
 * 	- Reads iLO2 IP address and hostname from the configfile hash
 * 	- Reads iLO2 user name and password from the configfile hash.
 * 	- Intializes plugin internal data structures. Allocates memory
 * 	  for RIBCL send/receive buffers.
 * 	- Initilaizes iLO2 RIBCL SSL module to communicate with iLO2.
 * 	- Error handling: Frees allocated memory (if any) before returning.
 *
 * Return values:
 * 	Plugin handle - normal operation.
 * 	NULL - on error.
 **/
void *ilo2_ribcl_open(GHashTable *handler_config,
                      unsigned int hid,
                      oh_evt_queue *eventq)
{
    struct oh_handler_state *oh_handler = NULL;
    ilo2_ribcl_handler_t *ilo2_ribcl_handler = NULL;
    char *ilo2_hostname = NULL;
    char *ilo2_port_str = NULL;
    char *ilo2_user_name = NULL;
    char *ilo2_password = NULL;
    char *entity_root = NULL;
    int host_len = 0;
    int port_len = 0;
    int temp_len = 0;

#ifdef ILO2_RIBCL_SIMULATE_iLO2_RESPONSE
    char *d_responsefile;
    size_t fnamesize;
#endif /* #ifdef ILO2_RIBCL_SIMULATE_iLO2_RESPONSE */

    /* check input parameters */
    if (!handler_config) {
        err("ilo2_ribcl Open:No config file provided.");
        return(NULL);
    } else if (!hid) {
        err("ilo2 ribcl Open:Bad handler id passed.");
        return NULL;
    } else if (!eventq) {
        err("ilo2 ribcl Open:No event queue was passed.");
        return NULL;
    }

    /* set up entity root in g_epbase */
    entity_root = (char *)g_hash_table_lookup(handler_config,
                  "entity_root");
    if(!entity_root) {
        err("ilo2 ribcl Open:entity root is not present");
        return(NULL);
    }
    oh_encode_entitypath(entity_root, &g_epbase);

    /* read hostname, port string user_name, and password from the
       config file */
    ilo2_hostname = (char *)g_hash_table_lookup(handler_config,
                    "ilo2_ribcl_hostname");
    if(!ilo2_hostname) {
        err("ilo2 ribcl Open:ilo2_ribcl_hostname is not specified in the config file");
        return(NULL);
    }
    host_len = strlen(ilo2_hostname);
    if((host_len < ILO2_HOST_NAME_MIN_LEN) ||
            (host_len > ILO2_HOST_NAME_MAX_LEN)) {
        err("ilo2 ribcl Open: Invalid iLO2 IP address");
        return(NULL);
    }

    ilo2_port_str = (char *)g_hash_table_lookup(handler_config,
                    "ilo2_ribcl_portstr");
    if(!ilo2_port_str) {
        err("ilo2 ribcl Open:ilo2_ribcl_port_str is not specified in the config file");
        return(NULL);
    } else if((port_len = strlen(ilo2_port_str)) < ILO2_MIN_PORT_STR_LEN) {
        err("ilo2 ribcl Open:Invalid iLO2 port");
        return(NULL);
    }

    ilo2_user_name = (char *)g_hash_table_lookup(handler_config,
                     "ilo2_ribcl_username");
    if(!ilo2_user_name) {
        err("ilo2 ribcl Open:ilo2_ribcl_username is not specified in the config file");
        return(NULL);
    }
    temp_len = strlen(ilo2_user_name);
    if(temp_len > ILO2_RIBCL_USER_NAME_MAX_LEN) {
        err("ilo2 ribcl Open:Invalid ilo2_ribcl_username - too long");
        return(NULL);
    } else if(temp_len < ILO2_RIBCL_USER_NAME_MIN_LEN) {
        err("ilo2 ribcl Open:Invalid ilo2_ribcl_username - too short");
        return(NULL);
    }

    ilo2_password = (char *)g_hash_table_lookup(handler_config,
                    "ilo2_ribcl_password");
    if(!ilo2_password) {
        err("ilo2 ribcl Open:ilo2_ribcl_password is not specified in the config file");
        return(NULL);
    }
    temp_len = strlen(ilo2_password);
    if(temp_len > ILO2_RIBCL_PASSWORD_MAX_LEN) {
        err("ilo2 ribcl Open:Invalid ilo2_ribcl_password - too long");
        return(NULL);
    } else if(temp_len < ILO2_RIBCL_PASSWORD_MIN_LEN) {
        err("ilo2 ribcl Open:Invalid ilo2_ribcl_password - too short");
        return(NULL);
    }

    /* allocate main handler and initialize it */
    oh_handler = malloc(sizeof(*oh_handler));
    if(!oh_handler) {
        err("ilo2 ribcl Open:unable to allocate main handler");
        return(NULL);
    }
    memset(oh_handler, '\0', sizeof(*oh_handler));

    /* assign config to handler_config and initialize rptcache */
    oh_handler->config = handler_config;

    oh_handler->rptcache = (RPTable *)g_malloc0(sizeof(RPTable));
    if(!oh_handler->rptcache) {
        err("ilo2 ribcl Open:unable to allocate RPT cache");
        free(oh_handler);
        return(NULL);
    }

    oh_handler->hid = hid;
    oh_handler->eventq = eventq;

    /* allocate memory for ilo2 ribcl private handler */
    ilo2_ribcl_handler = malloc(sizeof(*ilo2_ribcl_handler));
    if(!ilo2_ribcl_handler) {
        err("ilo2 ribcl Open:unable to allocate main handler");
        free(oh_handler->rptcache);
        free(oh_handler);
        return(NULL);
    }
    memset(ilo2_ribcl_handler, '\0', sizeof(*ilo2_ribcl_handler));
    oh_handler->data = ilo2_ribcl_handler;

    /* Save configuration in the handler */
    ilo2_ribcl_handler->entity_root = entity_root;

    /* build complete hostname with port string appended */
    /* add one extra byte to account for : in the middle of hostname:port
       string example: 10.100.1.1:443 */
    ilo2_ribcl_handler->ilo2_hostport = g_malloc(host_len+port_len+2);
    if(ilo2_ribcl_handler->ilo2_hostport == NULL) {
        err("ilo2 ribcl Open:unable to allocate memory");
        free(ilo2_ribcl_handler);
        free(oh_handler->rptcache);
        free(oh_handler);
        return(NULL);
    }
    snprintf(ilo2_ribcl_handler->ilo2_hostport,
             (host_len+port_len+2), "%s:%s",
             ilo2_hostname, ilo2_port_str);

    ilo2_ribcl_handler->user_name = ilo2_user_name;
    ilo2_ribcl_handler->password = ilo2_password;

    /* Build the customized RIBCL command strings containing the
     * login and password for this ilo2 host */

    if (ir_xml_build_cmdbufs( ilo2_ribcl_handler) != RIBCL_SUCCESS) {
        err("ilo2_ribcl_open(): ir_xml_build_cmdbufs failed to build buffers.");
        free(ilo2_ribcl_handler->ilo2_hostport);
        free(ilo2_ribcl_handler);
        free(oh_handler->rptcache);
        free(oh_handler);
        return(NULL);
    }

#ifdef ILO2_RIBCL_SIMULATE_iLO2_RESPONSE

    /* Check if a iLO2 response file should be used for discovery testing.
     * We will use the contents of this file as the command response,
     * rather than communucating with an actual iLO2. */

    d_responsefile = (char *)g_hash_table_lookup(handler_config,
                     "discovery_responsefile");
    if(  d_responsefile) {

        fnamesize = strlen( d_responsefile) + 1;
        ilo2_ribcl_handler->discovery_responsefile = malloc( fnamesize);

        if( ilo2_ribcl_handler->discovery_responsefile == NULL) {
            err("ilo2_ribcl_open(): allocation for discovery_responsefile failed.");
        } else {
            strncpy( ilo2_ribcl_handler->discovery_responsefile,
                     d_responsefile, fnamesize);
        }
    }

#endif /* ILO2_RIBCL_SIMULATE_iLO2_RESPONSE */

    /* initialize SSL */
    ilo2_ribcl_ssl_init();
    ilo2_ribcl_handler->ssl_ctx = ilo2_ribcl_ssl_ctx_init();
    if(ilo2_ribcl_handler->ssl_ctx == NULL) {
        err("ilo2_ribcl_open(): failed to initialize ssl connection to %s",
            ilo2_ribcl_handler->ilo2_hostport);
        free(ilo2_ribcl_handler->ilo2_hostport);
        free(ilo2_ribcl_handler);
        free(oh_handler->rptcache);
        free(oh_handler);
        return(NULL);
    }

    /* Initialize sensor data */
    ilo2_ribcl_init_sensor_data( ilo2_ribcl_handler);

    return((void *)oh_handler);
}