int
sis1100_ddma_map(struct sis1100_softc *sc, struct sis1100_fdata* fd,
    struct sis1100_ddma_map* map)
{
    struct demand_dma* dma;
    int i;

    /* we are called from 'release' with map==0 */
    if ((map!=0) && (map->num!=0) && (map->size!=0)) {
        /*if (map->num<2)
            return EINVAL;*/

        if (map->size&(NBPG-1)) {
            pINFO(sc, "ddma_map: size not multiple of page size");
            return EINVAL;
        }

        if ((unsigned long)map->addr&(NBPG-1)) {
            pINFO(sc, "ddma_map: addr not at page boundary");
            return EINVAL;
        }
    }

    dma=&sc->demand_dma;
    mutex_lock(&dma->mux);

    /* is an other process using DMA? */
    if ((dma->status!=dma_invalid) && (dma->owner!=fd)){
        mutex_unlock(&dma->mux);
        return EPERM;
    }
    /* is DMA still active? */
    if (dma->status==dma_running) {
        mutex_unlock(&dma->mux);
        return EALREADY;
    }

    /* if DMA is initialized we will free all structures first */
    if (dma->status==dma_ready) {
        for (i=0; i<dma->numblocks; i++)
            sis1100_ddma_unmap_block(sc, dma->block+i);
        KFREE(dma->block);
        dma->block=0;
        dma->status=dma_invalid;
    }

    /* if the user did not request a new mapping we are done here */
    if ((map==0) || (map->num==0) || (map->size==0)) {
        mutex_unlock(&dma->mux);
        return 0;
    }

    pINFO(sc, "dma_map: size=%lld addr=%p num=%d",
        (unsigned long long)map->size, map->addr, map->num);

    dma->block=KMALLOC(map->num*sizeof(struct demand_dma_block));
    if (dma->block==0) {
        mutex_unlock(&dma->mux);
        return ENOMEM;
    }

    dma->owner=fd;
    dma->size=map->size;
    dma->numblocks=map->num;
    dma->uaddr=map->addr;
    for (i=0; i<dma->numblocks; i++)
        sis1100_ddma_zero(dma->block+i);

    for (i=0; i<dma->numblocks; i++) {
        struct demand_dma_block* block=dma->block+i;
        int res;

        block->uaddr=dma->uaddr+i*dma->size;
        block->size=dma->size;
#ifdef __NetBSD__
        block->p=fd->p;
#endif
        /*pINFO(sc, "dma_map: try block %d", i);*/
        res=sis1100_ddma_map_block(sc, block);
        if (res) {
            int j;
            pINFO(sc, "dma_map: block %d: res=%d", i, res);
            for (j=0; j<dma->numblocks; j++)
                sis1100_ddma_unmap_block(sc, dma->block+j);
            KFREE(dma->block);
            dma->block=0;
            mutex_unlock(&dma->mux);
            return res;
        }
    }
    for (i=0; i<dma->numblocks; i++) {
        pERROR(sc, "dmadpr0[%d]=%08x", i, dma->block[i].dmadpr0);
    }

    dma->status=dma_ready;
    mutex_unlock(&dma->mux);
    return 0;
}