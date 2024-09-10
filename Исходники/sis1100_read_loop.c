int
sis1100_read_loop(
    struct sis1100_softc* sc,
    struct sis1100_fdata* fd,
    u_int32_t addr,           /* VME or SDRAM address */
    int32_t am,               /* address modifier, not used if <0 */
    int size,                 /* datasize (bytes/word) */
    int space,                /* remote space (1,2: VME; 6: SDRAM) */
    int fifo_mode,
    size_t count,             /* words (of size 'size') to be transferred */
                              /* count==0 is illegal */
    size_t* count_read,       /* words transferred */
    u_int8_t* data,           /* destination (user virtual address) */
    int* prot_error
    )
{
    u_int32_t head;
    int idx, res=0;

#if 0
    pERROR(sc, "read_loop size=%d count=%llu addr=%08x",
        size, (unsigned long long)count, addr);
#endif

    *count_read=count;
    head=0x00000002|(space&0x3f)<<16;
    mutex_lock(&sc->sem_hw);
    if (am>=0) {
        head|=0x800;
        sis1100writereg(sc, t_am, am);
    }
    switch (size) {
    case 1:
        for (idx=0; idx<count; idx++, data++) {
            u_int32_t val;
            sis1100writereg(sc, t_hdr, head|(0x01000000<<(addr&3)));
            sis1100writereg(sc, t_adl, addr);
            do {
                *prot_error=sis1100readreg(sc, prot_error);
            } while (*prot_error==0x005);
            if (*prot_error) {
                *count_read=idx;
                break;
            }
            val=sis1100rawreadreg(sc, tc_dal);

#if defined(__LITTLE_ENDIAN)
            __put_user((val>>((addr&3)<<3))&0xff, (u_int8_t*)(data));
#else
            __put_user((val>>((3-(addr&3))<<3))&0xff, (u_int8_t*)(data));
#endif
            if (!fifo_mode)
                addr++;
        }
        break;
    case 2:
        for (idx=0; idx<count; idx++, data+=2) {
            u_int32_t val;
            sis1100writereg(sc, t_hdr, head|(0x03000000<<(addr&3)));
            sis1100writereg(sc, t_adl, addr);
            do {
                *prot_error=sis1100readreg(sc, prot_error);
            } while (*prot_error==0x005);
            if (*prot_error) {
                *count_read=idx;
                break;
            }
            val=sis1100rawreadreg(sc, tc_dal);

#if defined(__LITTLE_ENDIAN)
            __put_user((val>>((addr&2)<<3))&0xffff, (u_int16_t*)data);
#else
            __put_user((val>>((2-(addr&2))<<3))&0xffff, (u_int16_t*)data);
#endif
            if (!fifo_mode)
                addr+=2;
        }
        break;
    case 4:
        sis1100writereg(sc, t_hdr, head|0x0f000000);
        for (idx=0; idx<count; idx++, data+=4) {
            u_int32_t val;
            sis1100writereg(sc, t_adl, addr);
            do {
                *prot_error=sis1100readreg(sc, prot_error);
            } while (*prot_error==0x005);
            if (*prot_error) {
                *count_read=idx;
                break;
            }
            val=sis1100rawreadreg(sc, tc_dal);
            __put_user(val, (u_int32_t*)data);
            if (!fifo_mode)
                    addr+=4;
        }
        break;
    }
    mutex_unlock(&sc->sem_hw);
    return res;
}