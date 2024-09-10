    int Payload::print_state(FILE * stream) const
    {
        int len = 0;

        len += FPRINTF(stream, "  Payload %s:\n", name);
        len += FPRINTF(stream, "    at address 0x%016"PRIx64"\n", payload_addr);
        len += FPRINTF(stream, "    state %d\n", state);
        len += FPRINTF(stream, "    rc %d\n", rc);
        if ( buildid )
        {
            len += FPRINTF(stream, "    buildid ");

            for ( unsigned int i = 0; i < buildid_len; i++ )
                len += FPRINTF(stream, "%02x", buildid[i]);

            len += FPUTS("\n", stream);
        }
        len += FPRINTF(stream, "    text [0x%016"PRIx64"-0x%016"PRIx64"]\n",
                       text_addr, text_end - 1);
        if ( rw_end > rw_addr )
            len += FPRINTF(stream, "    rw   [0x%016"PRIx64"-0x%016"PRIx64"]\n",
                           rw_addr, rw_end - 1);
        if ( ro_end > ro_addr )
            len += FPRINTF(stream, "    ro   [0x%016"PRIx64"-0x%016"PRIx64"]\n",
                           ro_addr, ro_end - 1);

        return len;
    }