/* Returns TRUE on success, FALSE on failure; sets "*err" to an error code on
   failure. */
gboolean network_instruments_dump_open(wtap_dumper *wdh, int *err)
{
    observer_dump_private_state * private_state = NULL;
    capture_file_header file_header;

    tlv_header comment_header;
    tlv_time_info time_header;
    char comment[64];
    size_t comment_length;
    struct tm * current_time;
    time_t system_time;

    /* initialize the private state */
    private_state = (observer_dump_private_state *) g_malloc(sizeof(observer_dump_private_state));
    private_state->packet_count = 0;
    private_state->network_type = wtap_to_observer_encap(wdh->encap);
    private_state->time_format = TIME_INFO_GMT;

    /* populate the fields of wdh */
    wdh->priv = (void *) private_state;
    wdh->subtype_write = observer_dump;

    /* initialize the file header */
    memset(&file_header, 0x00, sizeof(file_header));
    g_strlcpy(file_header.observer_version, network_instruments_magic, 31);
    file_header.offset_to_first_packet = (guint16)sizeof(file_header);
    file_header.offset_to_first_packet_high_byte = 0;

    /* create the file comment TLV */
    {
        time(&system_time);
        current_time = localtime(&system_time);
        memset(&comment, 0x00, sizeof(comment));
        g_snprintf(comment, 64, "This capture was saved from Wireshark on %s", asctime(current_time));
        comment_length = strlen(comment);

        comment_header.type = INFORMATION_TYPE_COMMENT;
        comment_header.length = (guint16) (sizeof(comment_header) + comment_length);

        /* update the file header to account for the comment TLV */
        file_header.number_of_information_elements++;
        file_header.offset_to_first_packet += comment_header.length;
    }

    /* create the timestamp encoding TLV */
    {
        time_header.type = INFORMATION_TYPE_TIME_INFO;
        time_header.length = (guint16) (sizeof(time_header));
        time_header.time_format = TIME_INFO_GMT;

        /* update the file header to account for the timestamp encoding TLV */
        file_header.number_of_information_elements++;
        file_header.offset_to_first_packet += time_header.length;
    }

    /* write the file header, swapping any multibyte fields first */
    CAPTURE_FILE_HEADER_TO_LE_IN_PLACE(file_header);
    if (!wtap_dump_file_write(wdh, &file_header, sizeof(file_header), err)) {
        return FALSE;
    }
    wdh->bytes_dumped += sizeof(file_header);

    /* write the comment TLV */
    {
        TLV_HEADER_TO_LE_IN_PLACE(comment_header);
        if (!wtap_dump_file_write(wdh, &comment_header, sizeof(comment_header), err)) {
            return FALSE;
        }
        wdh->bytes_dumped += sizeof(comment_header);

        if (!wtap_dump_file_write(wdh, &comment, comment_length, err)) {
            return FALSE;
        }
        wdh->bytes_dumped += comment_length;
    }

    /* write the time info TLV */
    {
        TLV_TIME_INFO_TO_LE_IN_PLACE(time_header);
        if (!wtap_dump_file_write(wdh, &time_header, sizeof(time_header), err)) {
            return FALSE;
        }
        wdh->bytes_dumped += sizeof(time_header);
    }

    init_gmt_to_localtime_offset();

    return TRUE;
}