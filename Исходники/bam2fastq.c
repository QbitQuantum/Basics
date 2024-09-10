const char* get_sequence(const bam1_t *b) {
    if(b == NULL) die("get_sequence: parameter error\n");
    const uint8_t *seq = bam_get_seq(b);
    size_t len = b->core.l_qseq;
    char* sequence;
    sequence = malloc(len*sizeof(char));
    uint8_t offset = (b->core.flag & BAM_FREVERSE) ? 16 : 0;
    size_t i;
    for (i=0; i<len; i++) {
        switch(bam_seqi(seq, i) + offset)
        {
        case 1:
            sequence[i] = 'A';
            break;
        case 2:
            sequence[i] = 'C';
            break;
        case 4:
            sequence[i] = 'G';
            break;
        case 8:
            sequence[i] = 'T';
            break;
        case 15:
            sequence[i] = 'N';
            break;
        //Complements (original index + 16)
        case 17:
            sequence[i] = 'T';
            break;
        case 18:
            sequence[i] = 'G';
            break;
        case 20:
            sequence[i] = 'C';
            break;
        case 24:
            sequence[i] = 'A';
            break;
        case 31:
            sequence[i] = 'N';
            break;
        default:
            sequence[i] = 'N';
            break;
        }
    }
    if (offset) sequence = strrev(sequence);
    return sequence;
}