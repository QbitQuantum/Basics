int WsCreate(wchar_t *CartName)
{
    int Checksum, i, j;
    FILE* fp;
    BYTE buf[16];
    wchar_t* p;

    for (i = 0; i < 256; i++)
    {
        ROMMap[i] = MemDummy;
        RAMMap[i] = MemDummy;
    }
    memset(IRAM, 0, sizeof(IRAM));
    memset(MemDummy, 0xA0, sizeof(MemDummy));
    memset(IO, 0, sizeof(IO));
    if (CartName == NULL)
    {
        return WsSetPdata();
    }
    if ((fp = _wfopen(CartName, L"rb")) == NULL)
    {
        ErrorMsg(ERR_FOPEN);
        return -1;
    }
    fseek(fp, -10, 2);
    if (fread(buf, 1, 10, fp) != 10)
    {
        ErrorMsg(ERR_FREAD_ROMINFO);
        return -1;
    }
    switch (buf[4])
    {
    case 1:
        ROMBanks = 4;
        break;
    case 2:
        ROMBanks = 8;
        break;
    case 3:
        ROMBanks = 16;
        break;
    case 4:
        ROMBanks = 32;
        break;
    case 5:
        ROMBanks = 48;
        break;
    case 6:
        ROMBanks = 64;
        break;
    case 7:
        ROMBanks = 96;
        break;
    case 8:
        ROMBanks = 128;
        break;
    case 9:
        ROMBanks = 256;
        break;
    default:
        ROMBanks = 0;
        break;
    }
    if (ROMBanks == 0)
    {
        ErrorMsg(ERR_ILLEGAL_ROMSIZE);
        return -1;
    }
    switch (buf[5])
    {
    case 0x01:
        RAMBanks = 1;
        RAMSize = 0x2000;
        CartKind = 0;
        break;
    case 0x02:
        RAMBanks = 1;
        RAMSize = 0x8000;
        CartKind = 0;
        break;
    case 0x03:
        RAMBanks = 2;
        RAMSize = 0x20000;
        CartKind = 0;
        break;
    case 0x04:
        RAMBanks = 4;
        RAMSize = 0x40000;
        CartKind = 0;
        break;
    case 0x10:
        RAMBanks = 1;
        RAMSize = 0x80;
        CartKind = CK_EEP;
        break;
    case 0x20:
        RAMBanks = 1;
        RAMSize = 0x800;
        CartKind = CK_EEP;
        break;
    case 0x50:
        RAMBanks = 1;
        RAMSize = 0x400;
        CartKind = CK_EEP;
        break;
    default:
        RAMBanks = 0;
        RAMSize = 0;
        CartKind = 0;
        break;
    }
    WsRomPatch(buf);
    Checksum = (int)((buf[9] << 8) + buf[8]);
    Checksum += (int)(buf[9] + buf[8]);
    for (i = ROMBanks - 1; i >= 0; i--)
    {
        fseek(fp, (ROMBanks - i) * -0x10000, 2);
        if ((ROMMap[0x100 - ROMBanks + i] = (BYTE*)malloc(0x10000)) != NULL)
        {
            if (fread(ROMMap[0x100 - ROMBanks + i], 1, 0x10000, fp) == 0x10000)
            {
                for (j = 0; j < 0x10000; j++)
                {
                    Checksum -= ROMMap[0x100 - ROMBanks + i][j];
                }
            }
            else
            {
                ErrorMsg(ERR_FREAD_ROM);
                break;
            }
        }
        else
        {
            ErrorMsg(ERR_MALLOC);
            break;
        }
    }
    fclose(fp);
    if (i >= 0)
    {
        return -1;
    }
    if (Checksum & 0xFFFF)
    {
        //ErrorMsg(ERR_CHECKSUM);
    }
    if (RAMBanks)
    {
        for (i = 0; i < RAMBanks; i++)
        {
            if ((RAMMap[i] = (BYTE*)malloc(0x10000)) != NULL)
            {
                memset(RAMMap[i], 0x00, 0x10000);
            }
            else
            {
                ErrorMsg(ERR_MALLOC);
                return -1;
            }
        }
    }
    if (RAMSize)
    {
        wcscpy (SaveName, CurDir);
        p = wcsrchr(CartName, L'\\');
        if (p)
        {
            wcscat(SaveName, SaveDir);
            if (PathIsDirectoryW(SaveName) == FALSE)
            {
                CreateDirectoryW(SaveName, NULL);
            }
            wcscat(SaveName, p);
            p = wcsrchr(SaveName, L'.');
            if (p)
            {
                *p = 0;
            }
            wcscat(SaveName, L".sav");
        }
        else
        {
            SaveName[0] = 0;
        }
        if ((fp = _wfopen(SaveName, L"rb")) != NULL)
        {
            for (i = 0; i < RAMBanks; i++)
            {
                if (RAMSize < 0x10000)
                {
                    if (fread(RAMMap[i], 1, RAMSize, fp) != (size_t)RAMSize)
                    {
                        ErrorMsg(ERR_FREAD_SAVE);
                        break;
                    }
                }
                else
                {
                    if (fread(RAMMap[i], 1, 0x10000, fp) != 0x10000)
                    {
                        ErrorMsg(ERR_FREAD_SAVE);
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }
    else
    {
        SaveName[0] = 0;
    }
    wcscpy (StateName, CurDir);
    p = wcsrchr(CartName, L'\\');
    if (p)
    {
        wcscat(StateName, StateDir);
        if (PathIsDirectoryW(StateName) == FALSE)
        {
            CreateDirectoryW(StateName, NULL);
        }
        wcscat(StateName, p);
        p = wcsrchr(StateName, L'.');
        if (p)
        {
            *p = 0;
        }
    }
    WsReset();
    SetDrawMode(buf[6] & 1); // 0:横 1:縦
    return 0;
}