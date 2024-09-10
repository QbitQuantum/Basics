/**
 * Add a new name to the hashset and allocate it a unique id
 * @param hs the hashset in question
 * @param prop the property to add
 * @return 1 if successful, else 0
 */
int hashset_put( hashset *hs, UChar *prop )
{
    unsigned slot;
    struct hs_bucket *b;
    if ( (float)hs->num_keys/(float)hs->num_buckets > MAX_RATIO )
    {
        if ( !hashset_rehash(hs) )
            return 0;
    }
    slot = hash(prop,u_strlen(prop))%hs->num_buckets;
    b = hs->buckets[slot];
    if ( b == NULL )
    {
        hs->buckets[slot] = hs_bucket_create(prop,hs->id++);
        if ( hs->buckets[slot] == NULL )
            return 0;
    }
    else
    {
        do
        {
            // if key already present, just return
            if ( u_strcmp(prop,b->key)==0 )
                return 0;
            else if ( b->next != NULL )
                b = b->next;
        }
        while ( b->next != NULL );
        // key not found
        b->next = hs_bucket_create(prop,hs->id++);
        if ( b->next == NULL )
            return 0;
    }
    hs->num_keys++;
    return 1;
}