/* Parse the data section of VCD */
static void parse_contents(FILE *file, const struct sr_dev_inst *sdi, struct context *ctx)
{
    GString *token = g_string_sized_new(32);

    uint64_t prev_timestamp = 0;
    uint64_t prev_values = 0;

    /* Read one space-delimited token at a time. */
    while (read_until(file, NULL, 'N') && read_until(file, token, 'W'))
    {
        if (token->str[0] == '#' && g_ascii_isdigit(token->str[1]))
        {
            /* Numeric value beginning with # is a new timestamp value */
            uint64_t timestamp;
            timestamp = strtoull(token->str + 1, NULL, 10);

            if (ctx->downsample > 1)
                timestamp /= ctx->downsample;

            /* Skip < 0 => skip until first timestamp.
             * Skip = 0 => don't skip
             * Skip > 0 => skip until timestamp >= skip.
             */
            if (ctx->skip < 0)
            {
                ctx->skip = timestamp;
                prev_timestamp = timestamp;
            }
            else if (ctx->skip > 0 && timestamp < (uint64_t)ctx->skip)
            {
                prev_timestamp = ctx->skip;
            }
            else if (timestamp == prev_timestamp)
            {
                /* Ignore repeated timestamps (e.g. sigrok outputs these) */
            }
            else
            {
                if (ctx->compress != 0 && timestamp - prev_timestamp > ctx->compress)
                {
                    /* Compress long idle periods */
                    prev_timestamp = timestamp - ctx->compress;
                }

                sr_dbg("New timestamp: %" PRIu64, timestamp);

                /* Generate samples from prev_timestamp up to timestamp - 1. */
                send_samples(sdi, prev_values, timestamp - prev_timestamp);
                prev_timestamp = timestamp;
            }
        }
        else if (token->str[0] == '$' && token->len > 1)
        {
            /* This is probably a $dumpvars, $comment or similar.
             * $dump* contain useful data, but other tags will be skipped until $end. */
            if (g_strcmp0(token->str, "$dumpvars") == 0 ||
                    g_strcmp0(token->str, "$dumpon") == 0 ||
                    g_strcmp0(token->str, "$dumpoff") == 0 ||
                    g_strcmp0(token->str, "$end") == 0)
            {
                /* Ignore, parse contents as normally. */
            }
            else
            {
                /* Skip until $end */
                read_until(file, NULL, '$');
            }
        }
        else if (strchr("bBrR", token->str[0]) != NULL)
        {
            /* A vector value. Skip it and also the following identifier. */
            read_until(file, NULL, 'N');
            read_until(file, NULL, 'W');
        }
        else if (strchr("01xXzZ", token->str[0]) != NULL)
        {
            /* A new 1-bit sample value */
            int i, bit;
            GSList *l;
            struct probe *probe;

            bit = (token->str[0] == '1');

            g_string_erase(token, 0, 1);
            if (token->len == 0)
            {
                /* There was a space between value and identifier.
                 * Read in the rest.
                 */
                read_until(file, NULL, 'N');
                read_until(file, token, 'W');
            }

            for (i = 0, l = ctx->probes; i < ctx->probecount && l; i++, l = l->next)
            {
                probe = l->data;

                if (g_strcmp0(token->str, probe->identifier) == 0)
                {
                    sr_dbg("Probe %d new value %d.", i, bit);

                    /* Found our probe */
                    if (bit)
                        prev_values |= (1 << i);
                    else
                        prev_values &= ~(1 << i);

                    break;
                }
            }

            if (i == ctx->probecount)
            {
                sr_dbg("Did not find probe for identifier '%s'.", token->str);
            }
        }
        else
        {
            sr_warn("Skipping unknown token '%s'.", token->str);
        }

        g_string_truncate(token, 0);
    }

    g_string_free(token, TRUE);
}