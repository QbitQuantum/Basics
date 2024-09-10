int
create_table() {
    NdbDictionary::Dictionary* dict = g_ndb->getDictionary();
    assert(dict);
    if(g_paramters[P_CREATE].value) {
        const NdbDictionary::Table * pTab = NDBT_Tables::getTable(g_table);
        assert(pTab);
        NdbDictionary::Table copy = * pTab;
        copy.setLogging(false);
        if(dict->createTable(copy) != 0) {
            g_err << "Failed to create table: " << g_table << endl;
            return -1;
        }

        NdbDictionary::Index x(g_ordered);
        x.setTable(g_table);
        x.setType(NdbDictionary::Index::OrderedIndex);
        x.setLogging(false);
        for (unsigned k = 0; k < copy.getNoOfColumns(); k++) {
            if(copy.getColumn(k)->getPrimaryKey()) {
                x.addColumn(copy.getColumn(k)->getName());
            }
        }

        if(dict->createIndex(x) != 0) {
            g_err << "Failed to create index: " << endl;
            return -1;
        }

        x.setName(g_unique);
        x.setType(NdbDictionary::Index::UniqueHashIndex);
        if(dict->createIndex(x) != 0) {
            g_err << "Failed to create index: " << endl;
            return -1;
        }
    }
    g_tab = dict->getTable(g_table);
    g_i_unique = dict->getIndex(g_unique, g_table);
    g_i_ordered = dict->getIndex(g_ordered, g_table);
    assert(g_tab);
    assert(g_i_unique);
    assert(g_i_ordered);
    return 0;
}