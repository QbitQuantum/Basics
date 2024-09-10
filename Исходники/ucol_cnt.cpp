U_CAPI int32_t  U_EXPORT2
uprv_cnttab_constructTable(CntTable *table, uint32_t mainOffset, UErrorCode *status) {
    int32_t i = 0, j = 0;
    if(U_FAILURE(*status) || table->size == 0) {
        return 0;
    }

    table->position = 0;

    if(table->offsets != NULL) {
        uprv_free(table->offsets);
    }
    table->offsets = (int32_t *)uprv_malloc(table->size*sizeof(int32_t));
    if(table->offsets == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return 0;
    }


    /* See how much memory we need */
    for(i = 0; i<table->size; i++) {
        table->offsets[i] = table->position+mainOffset;
        table->position += table->elements[i]->position;
    }

    /* Allocate it */
    if(table->CEs != NULL) {
        uprv_free(table->CEs);
    }
    table->CEs = (uint32_t *)uprv_malloc(table->position*sizeof(uint32_t));
    if(table->CEs == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        uprv_free(table->offsets);
        table->offsets = NULL;
        return 0;
    }
    uprv_memset(table->CEs, '?', table->position*sizeof(uint32_t));

    if(table->codePoints != NULL) {
        uprv_free(table->codePoints);
    }
    table->codePoints = (UChar *)uprv_malloc(table->position*sizeof(UChar));
    if(table->codePoints == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        uprv_free(table->offsets);
        table->offsets = NULL;
        uprv_free(table->CEs);
        table->CEs = NULL;
        return 0;
    }
    uprv_memset(table->codePoints, '?', table->position*sizeof(UChar));

    /* Now stuff the things in*/

    UChar *cpPointer = table->codePoints;
    uint32_t *CEPointer = table->CEs;
    for(i = 0; i<table->size; i++) {
        int32_t size = table->elements[i]->position;
        uint8_t ccMax = 0, ccMin = 255, cc = 0;
        for(j = 1; j<size; j++) {
            cc = u_getCombiningClass(table->elements[i]->codePoints[j]);
            if(cc>ccMax) {
                ccMax = cc;
            }
            if(cc<ccMin) {
                ccMin = cc;
            }
            *(cpPointer+j) = table->elements[i]->codePoints[j];
        }
        *cpPointer = ((ccMin==ccMax)?1:0 << 8) | ccMax;

        uprv_memcpy(CEPointer, table->elements[i]->CEs, size*sizeof(uint32_t));
        for(j = 0; j<size; j++) {
            if(isCntTableElement(*(CEPointer+j))) {
                *(CEPointer+j) = constructContractCE(getCETag(*(CEPointer+j)), table->offsets[getContractOffset(*(CEPointer+j))]);
            }
        }
        cpPointer += size;
        CEPointer += size;
    }

    // TODO: this one apparently updates the contraction CEs to point to a real address (relative to the 
    // start of the flat file). However, what is done below is just wrong and it affects building of 
    // tailorings that have constructions in a bad way. At least, one should enumerate the trie. Also,
    // keeping a list of code points that are contractions might be smart, although I'm not sure if it's
    // feasible.
    uint32_t CE;
    for(i = 0; i<=0x10FFFF; i++) {
        /*CE = ucmpe32_get(table->mapping, i);*/
        CE = utrie_get32(table->mapping, i, NULL);
        if(isCntTableElement(CE)) {
            CE = constructContractCE(getCETag(CE), table->offsets[getContractOffset(CE)]);
            /*ucmpe32_set(table->mapping, i, CE);*/
            utrie_set32(table->mapping, i, CE);
        }
    }


    return table->position;
}