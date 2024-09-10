// compress current chunk and write it to file,
// also update directory map
void write_current_chunk(void) {
    // uncompressed chunk size
    unsigned long cs = thePandalog->chunk.buf_p - thePandalog->chunk.buf;
    unsigned long ccs = thePandalog->chunk.zsize;
    int ret;
    // loop allows compress2 to fail and resize output buffer as needed
    // not sure why compress2 needs output buf to be bigger than input
    // even though ultimately it is smaller.  scratch space?
    // 10 is just a random guess.  shouldn't need more than 1 re-try
    uint32_t i;
    for (i=0; i<10; i++) {
        ret = compress2(thePandalog->chunk.zbuf, &ccs, thePandalog->chunk.buf, cs, Z_BEST_COMPRESSION);
        if (ret == Z_OK) break;
        // bigger output buffer needed to perform compression?
        thePandalog->chunk.zsize *= 2;
        thePandalog->chunk.zbuf = (unsigned char *) realloc(thePandalog->chunk.zbuf, thePandalog->chunk.zsize);
        assert (thePandalog->chunk.zbuf != NULL);
    }
    // ccs is final compressed chunk size
    assert (ret == Z_OK);
    assert(ccs > 0);
    assert(cs >= ccs);
    printf ("writing chunk %d of pandalog %d / %d = %.2f compression\n",
            (int) thePandalog->chunk_num, (int) cs, (int) ccs, ((float) cs) / ((float) ccs));
    fwrite(thePandalog->chunk.zbuf, 1, ccs, thePandalog->file);
    add_dir_entry(thePandalog->chunk_num);
    // reset start instr / pos
    thePandalog->chunk.start_instr = rr_get_guest_instr_count();
    thePandalog->chunk.start_pos = ftell(thePandalog->file);
    // rewind chunk buf and inc chunk #
    thePandalog->chunk.buf_p = thePandalog->chunk.buf;
    thePandalog->chunk_num ++;
    thePandalog->chunk.ind_entry = 0;
}