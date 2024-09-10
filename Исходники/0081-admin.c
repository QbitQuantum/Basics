/**
 * @brief Print the ConfigEntrys in the provided array.
 */
static void
test_print_ConfigEntry_array (const rd_kafka_ConfigEntry_t **entries,
                              size_t entry_cnt, unsigned int depth) {
        const char *indent = &"    "[4 - (depth > 4 ? 4 : depth)];
        size_t ei;

        for (ei = 0 ; ei < entry_cnt ; ei++) {
                const rd_kafka_ConfigEntry_t *e = entries[ei];
                const rd_kafka_ConfigEntry_t **syns;
                size_t syn_cnt;

                syns = rd_kafka_ConfigEntry_synonyms(e, &syn_cnt);

#define YN(v) ((v) ? "y" : "n")
                TEST_SAY("%s#%"PRIusz"/%"PRIusz
                         ": Source %s (%d): \"%s\"=\"%s\" "
                         "[is read-only=%s, default=%s, sensitive=%s, "
                         "synonym=%s] with %"PRIusz" synonym(s)\n",
                         indent,
                         ei, entry_cnt,
                         rd_kafka_ConfigSource_name(
                                 rd_kafka_ConfigEntry_source(e)),
                         rd_kafka_ConfigEntry_source(e),
                         rd_kafka_ConfigEntry_name(e),
                         rd_kafka_ConfigEntry_value(e) ?
                         rd_kafka_ConfigEntry_value(e) : "(NULL)",
                         YN(rd_kafka_ConfigEntry_is_read_only(e)),
                         YN(rd_kafka_ConfigEntry_is_default(e)),
                         YN(rd_kafka_ConfigEntry_is_sensitive(e)),
                         YN(rd_kafka_ConfigEntry_is_synonym(e)),
                         syn_cnt);
#undef YN

                if (syn_cnt > 0)
                        test_print_ConfigEntry_array(syns, syn_cnt, depth+1);
        }
}