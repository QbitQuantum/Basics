stream_t FIFOcreate(size_t blocksize){
    if(blocksize<=sizeof(void*)){
        Abort("block size must exceed pointer size");
    }
    stream_t fifo=RT_NEW(struct stream_s);
    stream_init(fifo);
    fifo->blocksize=blocksize;
    fifo->blocks=1;
    fifo->read_block=RTmalloc(blocksize);
    *((void**)fifo->read_block)=NULL;
    fifo->read_idx=sizeof(void*);
    fifo->write_block=fifo->read_block;
    fifo->write_idx=sizeof(void*);
    fifo->procs.read_max=fifo_read_max;
    fifo->procs.read=stream_default_read;
    fifo->procs.empty=fifo_empty;
    fifo->procs.close=FIFOdestroy;
    fifo->procs.write=fifo_write;
    fifo->procs.flush=fifo_flush;
    return fifo;
}