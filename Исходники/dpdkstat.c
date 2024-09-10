static void dpdk_stats_resolve_cnt_type(char *cnt_type, size_t cnt_type_len,
                                        const char *cnt_name) {
  char *type_end;
  type_end = strrchr(cnt_name, '_');

  if ((type_end != NULL) && (strncmp(cnt_name, "rx_", strlen("rx_")) == 0)) {
    if (strstr(type_end, "bytes") != NULL) {
      sstrncpy(cnt_type, "if_rx_octets", cnt_type_len);
    } else if (strstr(type_end, "error") != NULL) {
      sstrncpy(cnt_type, "if_rx_errors", cnt_type_len);
    } else if (strstr(type_end, "dropped") != NULL) {
      sstrncpy(cnt_type, "if_rx_dropped", cnt_type_len);
    } else if (strstr(type_end, "packets") != NULL) {
      sstrncpy(cnt_type, "if_rx_packets", cnt_type_len);
    } else if (strstr(type_end, "_placement") != NULL) {
      sstrncpy(cnt_type, "if_rx_errors", cnt_type_len);
    } else if (strstr(type_end, "_buff") != NULL) {
      sstrncpy(cnt_type, "if_rx_errors", cnt_type_len);
    } else {
      /* Does not fit obvious type: use a more generic one */
      sstrncpy(cnt_type, "derive", cnt_type_len);
    }

  } else if ((type_end != NULL) &&
             (strncmp(cnt_name, "tx_", strlen("tx_"))) == 0) {
    if (strstr(type_end, "bytes") != NULL) {
      sstrncpy(cnt_type, "if_tx_octets", cnt_type_len);
    } else if (strstr(type_end, "error") != NULL) {
      sstrncpy(cnt_type, "if_tx_errors", cnt_type_len);
    } else if (strstr(type_end, "dropped") != NULL) {
      sstrncpy(cnt_type, "if_tx_dropped", cnt_type_len);
    } else if (strstr(type_end, "packets") != NULL) {
      sstrncpy(cnt_type, "if_tx_packets", cnt_type_len);
    } else {
      /* Does not fit obvious type: use a more generic one */
      sstrncpy(cnt_type, "derive", cnt_type_len);
    }
  } else if ((type_end != NULL) &&
             (strncmp(cnt_name, "flow_", strlen("flow_"))) == 0) {

    if (strstr(type_end, "_filters") != NULL) {
      sstrncpy(cnt_type, "operations", cnt_type_len);
    } else if (strstr(type_end, "error") != NULL)
      sstrncpy(cnt_type, "errors", cnt_type_len);

  } else if ((type_end != NULL) &&
             (strncmp(cnt_name, "mac_", strlen("mac_"))) == 0) {
    if (strstr(type_end, "error") != NULL) {
      sstrncpy(cnt_type, "errors", cnt_type_len);
    }
  } else {
    /* Does not fit obvious type, or strrchr error:
     *   use a more generic type */
    sstrncpy(cnt_type, "derive", cnt_type_len);
  }
}