static BDMDExamineData* get_examine_data_from_table (GHashTable *table, gboolean free_table, GError **error) {
    BDMDExamineData *data = g_new0 (BDMDExamineData, 1);
    gchar *value = NULL;
    gchar *first_space = NULL;
    BSSize size = NULL;
    BSError *bs_error = NULL;
    struct tm tm;
    char time_str[20];
    gchar *name_str = NULL;

    data->level = g_strdup ((gchar*) g_hash_table_lookup (table, "Raid Level"));
    if (!(data->level))
        /* BUG: mdadm outputs "RAID Level" for some metadata formats (rhbz#1380034) */
        data->level = g_strdup ((gchar*) g_hash_table_lookup (table, "RAID Level"));

    value = (gchar*) g_hash_table_lookup (table, "Raid Devices");
    if (!value)
        /* BUG: mdadm outputs "RAID Devices" for some metadata formats (rhbz#1380034) */
        value = (gchar*) g_hash_table_lookup (table, "RAID Devices");
    if (value)
        data->num_devices = g_ascii_strtoull (value, NULL, 0);
    else
        data->num_devices = 0;

    name_str = ((gchar*) g_hash_table_lookup (table, "Name"));
    if (name_str) {
        g_strstrip (name_str);
        first_space = strchr (name_str, ' ');
        if (first_space)
            *first_space = '\0';
        data->name = g_strdup (name_str);
    }

    value = (gchar*) g_hash_table_lookup (table, "Array Size");
    if (value) {
        first_space = strchr (value, ' ');
        if (first_space)
            *first_space = '\0';
        if (value && first_space)
            /* Array Size is in KiB */
            data->size = g_ascii_strtoull (value, NULL, 0) * 1024;
    } else
        data->size = 0;

    data->uuid = g_strdup ((gchar*) g_hash_table_lookup (table, "Array UUID"));
    if (!data->uuid)
        /* also try just "UUID" which may be reported e.g for IMSM FW RAID */
        data->uuid = g_strdup ((gchar*) g_hash_table_lookup (table, "UUID"));

    value = (gchar*) g_hash_table_lookup (table, "Update Time");
    if (value) {
        memset(&tm, 0, sizeof(struct tm));
        strptime(value, "%a %b %e %H:%M:%S %Y", &tm);
        strftime(time_str, sizeof(time_str), "%s" , &tm);

        data->update_time = g_ascii_strtoull (time_str, NULL, 0);
    } else
        data->update_time = 0;

    data->dev_uuid = g_strdup ((gchar*) g_hash_table_lookup (table, "Device UUID"));

    value = (gchar*) g_hash_table_lookup (table, "Events");
    if (value)
        data->events = g_ascii_strtoull (value, NULL, 0);
    else
        data->events = 0;

    value = (gchar*) g_hash_table_lookup (table, "Version");
    if (value)
        data->metadata = g_strdup (value);
    else
        data->metadata = NULL;

    value = (gchar*) g_hash_table_lookup (table, "Chunk Size");
    if (value) {
        size = bs_size_new_from_str (value, &bs_error);
        if (size) {
            data->chunk_size = bs_size_get_bytes (size, NULL, &bs_error);
            bs_size_free (size);
        }

        if (bs_error) {
            g_set_error (error, BD_MD_ERROR, BD_MD_ERROR_PARSE,
                         "Failed to parse chunk size from mdexamine data: %s", bs_error->msg);
            bs_clear_error (&bs_error);
        }
    } else
        data->chunk_size = 0;

    if (free_table)
        g_hash_table_destroy (table);

    return data;
}