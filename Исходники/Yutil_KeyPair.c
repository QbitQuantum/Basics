/**
 * removeKeyDict
 * removes data by key from an existing KeyPair dictionary
 */
int removeKeyDict(char* key, KeyDict* dict) {
    int hash = dict->hash(key);
    Node *node = dict->list[hash];

    if (node != NULL) {
        node->head(&node);
        int length = node->length(node);
        for(int i = 0; i < length; i++, node = node->next) {
            KeyPair *this_key_pair = node->data;
            size_t key_size = strlen(key);
            if(!strncmp(this_key_pair->key, key, key_size)) {
                node->remove(&node, i);
            }
        }
    }

    return 0;
}