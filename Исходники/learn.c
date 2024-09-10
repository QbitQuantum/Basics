/* Appends a description of 'learn' to 's', in the format that ovs-ofctl(8)
 * describes. */
void
learn_format(const struct ofpact_learn *learn, struct ds *s)
{
    const struct ofpact_learn_spec *spec;
    struct match match;

    match_init_catchall(&match);

    ds_put_format(s, "%slearn(%s%stable=%s%"PRIu8,
                  colors.learn, colors.end, colors.special, colors.end,
                  learn->table_id);
    if (learn->idle_timeout != OFP_FLOW_PERMANENT) {
        ds_put_format(s, ",%sidle_timeout=%s%"PRIu16,
                      colors.param, colors.end, learn->idle_timeout);
    }
    if (learn->hard_timeout != OFP_FLOW_PERMANENT) {
        ds_put_format(s, ",%shard_timeout=%s%"PRIu16,
                      colors.param, colors.end, learn->hard_timeout);
    }
    if (learn->fin_idle_timeout) {
        ds_put_format(s, ",%sfin_idle_timeout=%s%"PRIu16,
                      colors.param, colors.end, learn->fin_idle_timeout);
    }
    if (learn->fin_hard_timeout) {
        ds_put_format(s, "%s,fin_hard_timeout=%s%"PRIu16,
                      colors.param, colors.end, learn->fin_hard_timeout);
    }
    if (learn->priority != OFP_DEFAULT_PRIORITY) {
        ds_put_format(s, "%s,priority=%s%"PRIu16,
                      colors.special, colors.end, learn->priority);
    }
    if (learn->flags & NX_LEARN_F_SEND_FLOW_REM) {
        ds_put_format(s, ",%ssend_flow_rem%s", colors.value, colors.end);
    }
    if (learn->flags & NX_LEARN_F_DELETE_LEARNED) {
        ds_put_format(s, ",%sdelete_learned%s", colors.value, colors.end);
    }
    if (learn->cookie != 0) {
        ds_put_format(s, ",%scookie=%s%#"PRIx64,
                      colors.param, colors.end, ntohll(learn->cookie));
    }

    OFPACT_LEARN_SPEC_FOR_EACH (spec, learn) {
        unsigned int n_bytes = DIV_ROUND_UP(spec->n_bits, 8);
        ds_put_char(s, ',');

        switch (spec->src_type | spec->dst_type) {
        case NX_LEARN_SRC_IMMEDIATE | NX_LEARN_DST_MATCH: {
            if (spec->dst.ofs == 0
                && spec->dst.n_bits == spec->dst.field->n_bits) {
                union mf_value value;

                memset(&value, 0, sizeof value);
                memcpy(&value.b[spec->dst.field->n_bytes - n_bytes],
                       ofpact_learn_spec_imm(spec), n_bytes);
                ds_put_format(s, "%s%s=%s", colors.param,
                              spec->dst.field->name, colors.end);
                mf_format(spec->dst.field, &value, NULL, s);
            } else {
                ds_put_format(s, "%s", colors.param);
                mf_format_subfield(&spec->dst, s);
                ds_put_format(s, "=%s", colors.end);
                ds_put_hex(s, ofpact_learn_spec_imm(spec), n_bytes);
            }
            break;
        }
        case NX_LEARN_SRC_FIELD | NX_LEARN_DST_MATCH:
            ds_put_format(s, "%s", colors.param);
            mf_format_subfield(&spec->dst, s);
            ds_put_format(s, "%s", colors.end);
            if (spec->src.field != spec->dst.field ||
                spec->src.ofs != spec->dst.ofs) {
                ds_put_format(s, "%s=%s", colors.param, colors.end);
                mf_format_subfield(&spec->src, s);
            }
            break;

        case NX_LEARN_SRC_IMMEDIATE | NX_LEARN_DST_LOAD:
            ds_put_format(s, "%sload:%s", colors.special, colors.end);
            ds_put_hex(s, ofpact_learn_spec_imm(spec), n_bytes);
            ds_put_format(s, "%s->%s", colors.special, colors.end);
            mf_format_subfield(&spec->dst, s);
            break;

        case NX_LEARN_SRC_FIELD | NX_LEARN_DST_LOAD:
            ds_put_format(s, "%sload:%s", colors.special, colors.end);
            mf_format_subfield(&spec->src, s);
            ds_put_format(s, "%s->%s", colors.special, colors.end);
            mf_format_subfield(&spec->dst, s);
            break;

        case NX_LEARN_SRC_FIELD | NX_LEARN_DST_OUTPUT:
            ds_put_format(s, "%soutput:%s", colors.special, colors.end);
            mf_format_subfield(&spec->src, s);
            break;
        }
    }