uint8_t extcap_base_parse_options(extcap_parameters * extcap, int result, char * optargument)
{
    uint8_t ret = 1;

    switch (result) {
        case EXTCAP_OPT_DEBUG:
#ifdef _WIN32
            _putenv_s("G_MESSAGES_DEBUG", "all");
#else
            setenv("G_MESSAGES_DEBUG", "all", 1);
#endif
            extcap->debug = TRUE;
            break;
        case EXTCAP_OPT_DEBUG_FILE:
            extcap_init_custom_log(optargument);
            g_log_set_default_handler(extcap_custom_log, NULL);
            break;
        case EXTCAP_OPT_LIST_INTERFACES:
            extcap->do_list_interfaces = 1;
            break;
        case EXTCAP_OPT_VERSION:
            extcap->ws_version = g_strdup(optargument);
            extcap->do_version = 1;
            break;
        case EXTCAP_OPT_LIST_DLTS:
            extcap->do_list_dlts = 1;
            break;
        case EXTCAP_OPT_INTERFACE:
            extcap->interface = g_strdup(optargument);
            break;
        case EXTCAP_OPT_CONFIG:
            extcap->show_config = 1;
            break;
        case EXTCAP_OPT_CAPTURE:
            extcap->capture = 1;
            break;
        case EXTCAP_OPT_CAPTURE_FILTER:
            extcap->capture_filter = g_strdup(optargument);
            break;
        case EXTCAP_OPT_FIFO:
            extcap->fifo = g_strdup(optargument);
            break;
        default:
            ret = 0;
    }

    return ret;
}