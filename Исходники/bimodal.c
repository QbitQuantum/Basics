void main (int argc, char *argv[])
        {
        union REGS r;
        DPMI_CALLREGS dr;
        struct SREGS sr;
        char *lowp;
        unsigned short __far *alias;
        void far *fh;
        WORD orig_rm_seg;
        WORD orig_rm_off;
        DWORD orig_pm_off;
        WORD orig_pm_sel;
        int c;
        int doprot = 1;
        int doreal = 1;

        while (argc-- > 1)
                {
                if (argv[argc][0] != '-')
                        {
badarg:
                        printf ("Invalid argument '%s'\n", argv[argc]);
                        printf ("Valid options are:\n");
                        printf ("\t-p   Don't install protected mode handler\n");
                        printf ("\t-r   Don't install real mode handler\n");
                        printf ("\t-2   Use COM2 instead of COM1 for testing\n");
                        exit (1);
                        }

                switch (argv[argc][1])
                        {
                        case 'p':
                                {
                                doprot = 0;
                                printf ("Not hooking in protected mode\n");
                                break;
                                }
                        case 'r':
                                {
                                doreal = 0;
                                printf ("Not hooking in real mode\n");
                                break;
                                }
                        case '2':
                                {
                                com_id = 2;
                                com_int = 0x0B;
                                com_port = 0x2F8;
                                printf ("Using COM2 instead of COM1 for testing\n");
                                break;
                                }
                        default:
                                goto badarg;
                        }

                if (argv[argc][2])
                        goto badarg;
                }

        /* Save the starting real-mode and protected-mode handler addresses.
        */
        r.x.eax = 0x0204;                                                       /* DPMI get protected mode vector */
        r.h.bl = com_int;
        int386 (0x31, &r, &r);
        orig_pm_sel = (WORD) r.x.ecx;
        orig_pm_off = r.x.edx;

        r.x.eax = 0x0200;                                                       /* DPMI get real mode vector */
        r.h.bl = com_int;
        int386 (0x31, &r, &r);
        orig_rm_seg = (WORD) r.x.ecx;
        orig_rm_off = (WORD) r.x.edx;

        /* Patch the code of the real mode handler so it knows which
                com port is doing the communications.  This is done before
                the handler is copied low, to take advantage of the label
                "com_port_low" while it's still valid.
        */
        alias = &com_port_low;
        fh = (void __far *) &com_port;
        *(alias = MK_FP(FP_SEG(fh), FP_OFF(alias))) = com_port;

        /* Allocate 128 bytes of DOS memory for the real-mode handler,
                which must of course be less than 128 bytes long, plus 1029
                bytes for the data.  Then copy the real-mode handler to DOS
                memory and initialize the data to zero.
        */
        if (! (lowp = D32DosMemAlloc (128 + 4 + 1024 + 1, &lowmem_seg)))
                {
                printf ("Couldn't get low memory!\n");
                exit (1);
                }
        _fmemcpy ((char __far *) lowp, (void __far *) rmhandler, 128);
        _fmemset ((char __far *) lowp + 128, 0, 4 + 1024 + 1);
        fh = (void __far *) pmhandler;

        /* Install the new handlers.  The memory touched by the protected mode
                handler needs to be locked, in case we are running under VMM
                or an external DPMI host.
        */
        if (doprot)
                {
                r.x.eax = 0x0205;                                                       /* DPMI set protected mode vector */
                r.x.ebx = (DWORD) com_int;
                r.x.ecx = (DWORD) FP_SEG(fh);
                r.x.edx = FP_OFF(fh);
                int386 (0x31, &r, &r);

                r.x.eax = 0x0600;                                                       /* DPMI lock linear region */
                r.x.ebx = ((DWORD) pmhandler) >> 16;
                r.x.ecx = ((DWORD) pmhandler) & 0xFFFF;
                r.x.esi = 0;
                r.x.edi = 256;                                                          /* lock 256 bytes */
                int386 (0x31, &r, &r);
                r.x.eax = 0x0600;
                r.x.ebx = ((DWORD) &com_port) >> 16;
                r.x.ecx = ((DWORD) &com_port) & 0xFFFF;
                r.x.esi = 0;
                r.x.edi = sizeof(WORD);                                 /* lock 2 bytes */
                int386 (0x31, &r, &r);
                }
        if (doreal)
                {
                r.x.eax = 0x0201;                                                       /* DPMI set real mode vector */
                r.x.ebx = (DWORD) com_int;
                r.x.ecx = D32RealSeg(lowp);                     /* CX:DX == real mode &handler */
                r.x.edx = D32RealOff(lowp);
                int386 (0x31, &r, &r);
                }

        /* Initialize COM port.
        */
        com_init ();

        puts ("Move the mouse or transmit data; press ESC to cancel\n");

        /* Wait for the ESC key to be pressed.  This loop has a good mix of
                time spent in real mode and protected mode, so the upper left
                hand corner of your color screen will toggle between 'R' and 'P'.
        */
        while (1)
                {
                /* Explicitly go down to real mode to ask if a key is ready.
                        (The kbhit() call is simpler to code, but extra transfers to
                        real mode may be optimized out by the DOS extender.)
                */
                r.x.eax = 0x300;                                                /* DPMI signal real mode interrupt */
                r.x.ebx = 0x16;
                r.x.ecx = 0;
                fh = (void far *) &dr;
                _fmemset (fh, 0, sizeof(DPMI_CALLREGS));
                dr.eax = 0x0100;
                sr.ds = 0;
                sr.es = FP_SEG(fh);
                r.x.edi = FP_OFF(fh);
                int386x (0x31, &r, &r, &sr);

                if (! (dr.flags & 0x40))                        /* Test zero flag */
                        {
                        if (((c = getch ()) & 0xff) == 27)
                                break;
                        putch (c);
                        }

                /* Here we just check for an overflow, update our count of
                        interrupts, and reset the buffer.  You would process the
                        data before flushing the buffer.
                */
                _disable ();
                if (*(lowp + 128 + 4 + 1024))           /* Overflow? */
                        break;
                total_count += *((unsigned long *)(lowp + 128));
                *((unsigned long *)(lowp + 128)) = 0;
                _enable ();
                }

        /* Clean up.
        */
        r.x.eax = 0x0201;                                                       /* DPMI set real mode vector */
        r.x.ebx = (DWORD) com_int;
        r.x.ecx = (DWORD) orig_rm_seg;          /* CX:DX == real mode &handler */
        r.x.edx = (DWORD) orig_rm_off;
        int386 (0x31, &r, &r);

        r.x.eax = 0x0205;                                                       /* DPMI set protected mode vector */
        r.x.ebx = (DWORD) com_int;
        r.x.ecx = (DWORD) orig_pm_sel;
        r.x.edx = orig_pm_off;
        int386 (0x31, &r, &r);

        if (*(lowp + 128 + 4 + 1024))
                printf ("\nOverflow! Increase data receive buffer size or check the\nbuffer more often.\n");
        else
                printf ("\n%lu interrupts processed (%lu in protected mode, %lu real mode).\n",
                        total_count, pm_count, total_count - pm_count);
        }