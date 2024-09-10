int postings_update(struct postings* post, struct postings_docstats* stats) {
    struct postings_node* node = post->update;
    unsigned int terms = 0,
                 dterms = 0;
    float weight = 0,
           fdt_log;

    while (node) {
        /* calculate document weight */
        fdt_log = (float) logf((float) node->offsets);
        weight += (1 + fdt_log) * (1 + fdt_log);

        assert(node->offsets);
        assert(node->last_count != node->vecmem);
        assert(node->last_count > node->vecmem);
        assert((post->docno > node->last_docno) || (node->last_docno == -1));

        /* check if we have to correct the count that we wrote before (1) */
        if (node->offsets > 1) {
            unsigned int len = vec_vbyte_len(node->offsets);
            struct vec offsetvec;
 
            /* check if the count will expand in size */
            if (len > 1) {
                /* check if we need to resize the vector */
                if ((VEC_LEN(&node->vec) < len - 1) 
                  /* resize it */
                  && !postings_node_expand(node)) {
                    return 0;
                }

                /* move offsets up to make room for expanded count */
                assert(node->vec.pos > node->last_count);
                assert(node->vecmem < node->last_count);
                memmove(node->last_count + len, node->last_count + 1, 
                  node->vec.pos - (node->last_count + 1));
                node->vec.pos += len - 1;
                post->size += len - 1;
            }

            /* point offsetvec to the correct location to write the correct
             * count */
            offsetvec.pos = node->last_count;
            offsetvec.end = node->vec.end;

            len = vec_vbyte_write(&offsetvec, node->offsets);
            assert(len);
        }

        /* watch for overflow */
        assert(node->occurs + node->offsets > node->occurs);  
        node->occurs += node->offsets;
        terms += node->offsets;
        dterms++;
        node->offsets = 0;

        node->last_docno = post->docno;
        node->last_offset = -1;
        node->last_count = node->vecmem;
        node->docs++;

        node = node->update;
    }

    post->update = NULL;                /* reset update list */
    post->update_required = 0;
    stats->weight = (float) sqrtf(weight);
    stats->terms = terms;
    stats->distinct = dterms;
    return 1;
}