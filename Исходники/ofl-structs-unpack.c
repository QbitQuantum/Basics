ofl_err
ofl_structs_group_stats_unpack(struct ofp_group_stats *src, size_t *len, struct ofl_group_stats **dst) {
    struct ofl_group_stats *s;
    struct ofp_bucket_counter *c;
    ofl_err error;
    size_t slen;
    size_t i;

    if (*len < sizeof(struct ofp_group_stats)) {
        OFL_LOG_WARN(LOG_MODULE, "Received group desc stats reply is too short (%zu).", *len);
        return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
    }

    if (*len < ntohs(src->length)) {
        OFL_LOG_WARN(LOG_MODULE, "Received group stats reply has invalid length (set to %u, but only %zu received).", ntohs(src->length), *len);
        return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
    }

    if (ntohl(src->group_id) > OFPG_MAX) {
        if (OFL_LOG_IS_WARN_ENABLED(LOG_MODULE)) {
            char *gs = ofl_group_to_string(ntohl(src->group_id));
            OFL_LOG_WARN(LOG_MODULE, "Received group stats has invalid group_id (%s).", gs);
            free(gs);
        }
        return ofl_error(OFPET_BAD_ACTION, OFPBRC_BAD_LEN);
    }
    slen = ntohs(src->length) - sizeof(struct ofp_group_stats);

    s = (struct ofl_group_stats *)malloc(sizeof(struct ofl_group_stats));
    s->group_id = ntohl(src->group_id);
    s->ref_count = ntohl(src->ref_count);
    s->packet_count = ntoh64(src->packet_count);
    s->byte_count = ntoh64(src->byte_count);
    s->duration_sec =  htonl(src->duration_sec);
    s->duration_nsec =  htonl(src->duration_nsec);

    error = ofl_utils_count_ofp_bucket_counters(src->bucket_stats, slen, &s->counters_num);
    if (error) {
        free(s);
        return error;
    }
    s->counters = (struct ofl_bucket_counter **)malloc(s->counters_num * sizeof(struct ofl_bucket_counter *));

    c = src->bucket_stats;
    for (i = 0; i < s->counters_num; i++) {
        error = ofl_structs_bucket_counter_unpack(c, &slen, &(s->counters[i]));
        if (error) {
            OFL_UTILS_FREE_ARR(s->counters, i);
            free(s);
            return error;
        }
        c = (struct ofp_bucket_counter *)((uint8_t *)c + sizeof(struct ofp_bucket_counter));
    }

    if (slen != 0) {
        *len = *len - ntohs(src->length) + slen;
        OFL_LOG_WARN(LOG_MODULE, "The received group stats contained extra bytes (%zu).", slen);
        ofl_structs_free_group_stats(s);
        return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
    }

    *len -= ntohs(src->length);
    *dst = s;
    return 0;
}