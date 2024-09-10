F_close()
    {
    register char wRetStat;
    register int iocb16, iocb;

    iocb16 = reg_X;
    iocb = iocb16 >> 4;

    Fclose(rgwDOShand[iocb]);
    rgwDOShand[iocb] = -1;

    wRetStat = 1;
    reg_Y = wRetStat;

    reg_Z = wRetStat;
    reg_N = (wRetStat & 0x80) ? TRUE : FALSE;
    reg_PC = 0xE45B;
    }