static void
primary_parser_package_start (PrimarySAXContext *ctx,
                              const char *name,
                              const char **attrs)
{
    SAXContext *sctx = &ctx->sctx;

    Package *p = sctx->current_package;
    int i;
    const char *attr;
    const char *value;

    g_assert (p != NULL);

    sctx->want_text = TRUE;

    if (!strcmp (name, "format")) {
        ctx->state = PRIMARY_PARSER_FORMAT;
    }

    else if (!strcmp (name, "version")) {
        parse_version_info(attrs, p);
    }

    else if (!strcmp (name, "checksum")) {
        for (i = 0; attrs && attrs[i]; i++) {
            attr = attrs[i];
            value = attrs[++i];

            if (!strcmp (attr, "type"))
                p->checksum_type = g_string_chunk_insert (p->chunk, value);
        }
    }

    else if (!strcmp (name, "time")) {
        for (i = 0; attrs && attrs[i]; i++) {
            attr = attrs[i];
            value = attrs[++i];

            if (!strcmp (attr, "file"))
                p->time_file = strtol(value, NULL, 10);
            else if (!strcmp (attr, "build"))
                p->time_build = strtol(value, NULL, 10);
        }
    }

    else if (!strcmp (name, "size")) {
        for (i = 0; attrs && attrs[i]; i++) {
            attr = attrs[i];
            value = attrs[++i];

            if (!strcmp (attr, "package"))
                p->size_package = strtoll(value, NULL, 10);
            else if (!strcmp (attr, "installed"))
                p->size_installed = strtoll(value, NULL, 10);
            else if (!strcmp (attr, "archive"))
                p->size_archive = strtoll(value, NULL, 10);
        }
    }

    else if (!strcmp (name, "location")) {
        for (i = 0; attrs && attrs[i]; i++) {
            attr = attrs[i];
            value = attrs[++i];

            if (!strcmp (attr, "href"))
                p->location_href = g_string_chunk_insert (p->chunk, value);
            else if (!strcmp (attr, "xml:base"))
                p->location_base = g_string_chunk_insert (p->chunk, value);
        }
    }
}