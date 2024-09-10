bool
parcHashCodeTable_Add(PARCHashCodeTable *table, void *key, void *data)
{
    assertNotNull(table, "Parameter table must be non-null");
    assertNotNull(key, "Parameter key must be non-null");
    assertNotNull(data, "Parameter data must be non-null");

    if (table->hashtable.tableSize >= table->hashtable.expandThreshold) {
        _expand(table);
    }

    HashCodeType hashcode = table->keyHashCodeFunc(key);

    PARCHashCodeTable_AddResult result = ADD_OK;
    do {
        result = _innerTableAdd(&table->hashtable, table->keyEqualsFunc, hashcode, key, data);
        if (result == ADD_NOSPACE) {
            _expand(table);
        }
    } while (result == ADD_NOSPACE);

    return (result == ADD_OK);
}