// Parse XML information about a persistent file transfer
//
int PERS_FILE_XFER::parse(MIOFILE& fin) {
    char buf[256];

    while (fin.fgets(buf, 256)) {
        if (match_tag(buf, "</persistent_file_xfer>")) return 0;
        else if (parse_int(buf, "<num_retries>", nretry)) continue;
        else if (parse_double(buf, "<first_request_time>", first_request_time)) {
            continue;
        }
        else if (parse_double(buf, "<next_request_time>", next_request_time)) {
            continue;
        }
        else if (parse_double(buf, "<time_so_far>", time_so_far)) continue;
        else if (parse_double(buf, "<last_bytes_xferred>", last_bytes_xferred)) continue;
        else {
            if (log_flags.unparsed_xml) {
                msg_printf(NULL, MSG_INFO,
                    "[unparsed_xml] Unparsed line in file transfer info: %s", buf
                );
            }
        }
    }
    return ERR_XML_PARSE;
}