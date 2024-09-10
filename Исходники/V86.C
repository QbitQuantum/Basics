void SetV86(void (*f)())
{
#ifdef __MSC__
	_heapmin();
#endif
    SetTSS( (TSS *)&v86tss, seg.cs, seg.ds, f, 0x23002L,
            (unsigned char *) sbrk(0)+2048, seg.ss,
        stack+STACKSIZE, 0x10);

    v86tss.tss.iobase = v86tss.iomap
                       -(unsigned char *)&v86tss;
    memset(v86tss.iomap, 0, sizeof(v86tss.iomap));
    v86tss.iomap[8192]=0xff;

    ProtoTssSel = AllocSel();
    SetSegDesc(ProtoTssSel,
        SegToLinier(seg.ds, (unsigned short) &tss),
            (long) sizeof(TSS), TypeTSS, SmallSeg, 0);
    V86TssSel = AllocSel();
    SetSegDesc(V86TssSel,
        SegToLinier(seg.ds, (unsigned short) &v86tss),
            (long) sizeof(TSS_IO), TypeTSS, SmallSeg, 0);

    IntHandler = v86int;
}