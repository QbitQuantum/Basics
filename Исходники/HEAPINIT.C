void __cdecl _heap_init (
        void
        )
{

#define _INITREGIONSZ 0x1000

        /*LATER -- do we need to do anything to init heap? Yes, in case user not malloc first*/
        int oldregionsz = _heap_regionsize;     /* save current region size */

        struct _heap_region_ *pHeapRegions;
        void *p;
        void *p2;

        if (hHeapRegions == NULL)
                {
                hHeapRegions = NewHandle(sizeof(struct _heap_region_)*_HEAP_REGIONMAX);
                if (hHeapRegions == NULL)
                        {
                        DSErrCode = appMemFullErr;
                        ExitToShell();
                        }
                HLock(hHeapRegions);
                pHeapRegions = (struct _heap_region_ *)(*hHeapRegions);
                memset(pHeapRegions, 0, sizeof(struct _heap_region_)*_HEAP_REGIONMAX);
                _heap_region_table_cur = _HEAP_REGIONMAX;
                }


        _heap_regionsize = _INITREGIONSZ;       /* set region size to 64 Kb */

        /* make sure we have enough memory to do initialization */
        if ((p = NewPtr(_HEAP_EMPTYLIST_SIZE)) == NULL)
                {
                DSErrCode = appMemFullErr;
                ExitToShell();
                }

        if ((p2 = NewPtr(_heap_regionsize)) == NULL)
                {
                DSErrCode = appMemFullErr;
                ExitToShell();
                }

        if (p)
                {
                DisposePtr(p);
                }
        if (p2)
                {
                DisposePtr(p2);
                }

        p = _malloc_base(4);
        if (p == NULL)
                {
                DSErrCode = appMemFullErr;
                ExitToShell();
                }
        _free_base( p );                /* malloc, then free a block */
        _heap_regionsize = oldregionsz;         /* restore region size */

}