static int GM_UNIQUENAME(Open)(LIBBASETYPEPTR hdskBase, struct IOExtTD *iotd, IPTR unitnum, ULONG flags)
{
    STRPTR unitname;
    struct unit *unit;
    UBYTE unitflags = 0;

    if (unitnum < 1024)
    {
        ULONG len = strlen(hdskBase->DiskDevice) + 5;

        unitname = AllocVec(len, MEMF_ANY);
        if (!unitname)
            return FALSE;

        unitflags = UNIT_FREENAME;
        NewRawDoFmt(hdskBase->DiskDevice, (VOID_FUNC)RAWFMTFUNC_STRING, unitname, unitnum + hdskBase->unitBase);
    }
    else
        unitname = (STRPTR)unitnum;

    D(bug("hostdisk: open unit %s\n", unitname));

    ObtainSemaphore(&hdskBase->sigsem);

    unit = (struct unit *)FindName(&hdskBase->units, unitname);

    if (unit)
    {
        unit->usecount++;
        ReleaseSemaphore(&hdskBase->sigsem);
            
        iotd->iotd_Req.io_Unit                    = (struct Unit *)unit;
        iotd->iotd_Req.io_Error                   = 0;
        iotd->iotd_Req.io_Message.mn_Node.ln_Type = NT_REPLYMSG;

        DOPEN(bug("hostdisk: in libopen func. Yep. Unit is already open\n"));    
        return TRUE;
    }

    DOPEN(bug("hostdisk: in libopen func. No, it is not. So creating new unit ...\n"));

    unit = (struct unit *)AllocMem(sizeof(struct unit), MEMF_PUBLIC | MEMF_CLEAR);

    if (unit != NULL)
    {
        ULONG p = strlen(GM_UNIQUENAME(LibName));
        char taskName[p + strlen(unitname) + 2];
        struct Task *unitTask;

        DOPEN(bug("hostdisk: in libopen func. Allocation of unit memory okay. Setting up unit and calling CreateNewProc ...\n"));

        CopyMem(GM_UNIQUENAME(LibName), taskName, p);
        taskName[p] = ' ';
        strcpy(&taskName[p + 1], unitname);

        unit->n.ln_Name = unitname;
        unit->usecount  = 1;
        unit->hdskBase  = hdskBase;
        unit->flags     = unitflags;
        NEWLIST((struct List *)&unit->changeints);

        iotd->iotd_Req.io_Unit = (struct Unit *)unit;
        SetSignal(0, SIGF_SINGLE);
        unitTask = NewCreateTask(TASKTAG_PC  , unitentry,
                                 TASKTAG_NAME, taskName,
                                 TASKTAG_ARG1, iotd,
                                 TAG_DONE);

        DOPEN(bug("hostdisk: in libopen func. NewCreateTask() called. Task = 0x%p\n", unitTask));

        if (unitTask)
        {
            DOPEN(bug("hostdisk: in libopen func. Waiting for signal from unit task...\n"));
            Wait(SIGF_SINGLE);

            DOPEN(bug("hostdisk: in libopen func. Unit error %u, flags 0x%02X\n", iotd->iotd_Req.io_Error, unit->flags));
            if (!iotd->iotd_Req.io_Error)
            {
                AddTail((struct List *)&hdskBase->units, &unit->n);
                ReleaseSemaphore(&hdskBase->sigsem);
                return TRUE;
            }
        }
        else
            iotd->iotd_Req.io_Error = TDERR_NoMem;

        freeUnit(unit);
    }
    else
        iotd->iotd_Req.io_Error = TDERR_NoMem;

    ReleaseSemaphore(&hdskBase->sigsem);

    return FALSE;
}