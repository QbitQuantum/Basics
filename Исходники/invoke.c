int InsertExternalFile(char *name)
{
    if (HasExt(name, ".ASM") || HasExt(name,".NAS"))
    {
        InsertFile(&objlist, name, ".o");
        InsertFile(&asmlist, name, 0);
        return 1; /* compiler shouldn't process it*/
    }
    else if (HasExt(name, ".L"))
    {
        InsertFile(&liblist, name, 0);
        return 1;
    }
    else if (HasExt(name, ".RC"))
    {
        InsertFile(&reslist, name, ".RES");
        InsertFile(&rclist, name, 0);
        return 1;
    }
    else if (HasExt(name, ".RES"))
    {
        InsertFile(&reslist, name, 0);
        return 1;
    }
    else if (HasExt(name, ".o"))
    {
        InsertFile(&objlist, name, 0);
        return 1;
    }

    InsertFile(&objlist, name, ".O");
    
    // compiling via assembly
    if (cparams.prm_asmfile && !cparams.prm_compileonly)
    {
        InsertFile(&asmlist, name, ".ASM");
    }
    return 0; /* compiler should process it*/
}