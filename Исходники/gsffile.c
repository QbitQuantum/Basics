static GwyContainer*
gsf_load(const gchar *filename,
         G_GNUC_UNUSED GwyRunType mode,
         GError **error)
{
    GwyContainer *container = NULL, *meta = NULL;
    GwyDataField *dfield = NULL;
    GwyTextHeaderParser parser;
    GwySIUnit *unit;
    guchar *p, *value, *buffer = NULL, *header = NULL;
    const guchar *datap;
    GHashTable *hash = NULL;
    gsize size, expected_size;
    GError *err = NULL;
    gdouble xreal, yreal, xoff, yoff;
    guint i, xres, yres;
    gdouble *d;

    if (!gwy_file_get_contents(filename, &buffer, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        return NULL;
    }

    if (size < MAGIC_SIZE || memcmp(buffer, MAGIC, MAGIC_SIZE) != 0) {
        err_FILE_TYPE(error, "Gwyddion Simple Field");
        goto fail;
    }

    p = buffer + MAGIC_SIZE;
    datap = memchr(p, '\0', size - (p - buffer));
    if (!datap) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("File header is truncated."));
        goto fail;
    }
    header = g_strdup(p);
    datap += 4 - ((datap - buffer) % 4);

    gwy_clear(&parser, 1);
    parser.key_value_separator = "=";
    if (!(hash = gwy_text_header_parse(header, &parser, NULL, NULL))) {
        g_propagate_error(error, err);
        goto fail;
    }

    xres = read_pixel_size(hash, "XRes", error);
    yres = read_pixel_size(hash, "YRes", error);
    if (!xres || !yres)
        goto fail;

    expected_size = (datap - buffer) + sizeof(gfloat)*xres*yres;
    if (err_SIZE_MISMATCH(error, expected_size, size, TRUE))
        goto fail;

    xreal = read_real_size(hash, "XReal");
    yreal = read_real_size(hash, "YReal");
    dfield = gwy_data_field_new(xres, yres, xreal, yreal, FALSE);

    xoff = read_real_offset(hash, "XOffset");
    yoff = read_real_offset(hash, "YOffset");
    gwy_data_field_set_xoffset(dfield, xoff);
    gwy_data_field_set_yoffset(dfield, yoff);

    value = g_hash_table_lookup(hash, "XYUnits");
    unit = gwy_si_unit_new(value);
    gwy_data_field_set_si_unit_xy(dfield, unit);
    g_object_unref(unit);

    value = g_hash_table_lookup(hash, "ZUnits");
    unit = gwy_si_unit_new(value);
    gwy_data_field_set_si_unit_z(dfield, unit);
    g_object_unref(unit);

    d = gwy_data_field_get_data(dfield);
    for (i = xres*yres; i; i--)
        *(d++) = gwy_get_gfloat_le(&datap);

    container = gwy_container_new();
    gwy_container_set_object(container, gwy_app_get_data_key_for_id(0), dfield);
    g_object_unref(dfield);

    if ((value = g_hash_table_lookup(hash, "Title"))) {
        /* FIXME: Ensure valid UTF-8 */
        gwy_container_set_string_by_name(container, "/0/data/title",
                                         g_strdup(value));
    }
    else
        gwy_app_channel_title_fall_back(container, 0);

    meta = gwy_container_new();
    g_hash_table_foreach(hash, add_meta, meta);
    if (gwy_container_get_n_items(meta))
        gwy_container_set_object_by_name(container, "/0/meta", meta);
    g_object_unref(meta);

    gwy_file_channel_import_log_add(container, 0, NULL, filename);

fail:
    gwy_file_abandon_contents(buffer, size, NULL);
    if (header)
        g_free(header);
    if (hash)
        g_hash_table_destroy(hash);

    return container;
}