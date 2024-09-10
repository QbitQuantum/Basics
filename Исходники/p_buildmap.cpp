static bool P_LoadBloodMap (BYTE *data, size_t len, FMapThing **mapthings, int *numspr)
{
    BYTE infoBlock[37];
    int mapver = data[5];
    DWORD matt;
    int numRevisions, numWalls, numsprites, skyLen, visibility, parallaxType;
    int i;
    int k;

    if (mapver != 6 && mapver != 7)
    {
        return false;
    }

    matt = *(DWORD *)(data + 28);
    if (matt != 0 &&
            matt != MAKE_ID('M','a','t','t') &&
            matt != MAKE_ID('t','t','a','M'))
    {
        Decrypt (infoBlock, data + 6, 37, 0x7474614d);
    }
    else
    {
        memcpy (infoBlock, data + 6, 37);
    }
    skyLen = 2 << LittleShort(*(WORD *)(infoBlock + 16));
    visibility = LittleLong(*(DWORD *)(infoBlock + 18));
    parallaxType = infoBlock[26];
    numRevisions = LittleLong(*(DWORD *)(infoBlock + 27));
    numsectors = LittleShort(*(WORD *)(infoBlock + 31));
    numWalls = LittleShort(*(WORD *)(infoBlock + 33));
    numsprites = LittleShort(*(WORD *)(infoBlock + 35));
    Printf("Visibility: %d\n", visibility);

    if (mapver == 7)
    {
        // Version 7 has some extra stuff after the info block. This
        // includes a copyright, and I have no idea what the rest of
        // it is.
        data += 171;
    }
    else
    {
        data += 43;
    }

    // Skip the sky info.
    data += skyLen;

    sectortype *bsec = new sectortype[numsectors];
    walltype *bwal = new walltype[numWalls];
    spritetype *bspr = new spritetype[numsprites];
    Xsprite *xspr = new Xsprite[numsprites];

    // Read sectors
    k = numRevisions * sizeof(sectortype);
    for (i = 0; i < numsectors; ++i)
    {
        if (mapver == 7)
        {
            Decrypt (&bsec[i], data, sizeof(sectortype), k);
        }
        else
        {
            memcpy (&bsec[i], data, sizeof(sectortype));
        }
        data += sizeof(sectortype);
        if (bsec[i].extra > 0)	// skip Xsector
        {
            data += 60;
        }
    }

    // Read walls
    k |= 0x7474614d;
    for (i = 0; i < numWalls; ++i)
    {
        if (mapver == 7)
        {
            Decrypt (&bwal[i], data, sizeof(walltype), k);
        }
        else
        {
            memcpy (&bwal[i], data, sizeof(walltype));
        }
        data += sizeof(walltype);
        if (bwal[i].extra > 0)	// skip Xwall
        {
            data += 24;
        }
    }

    // Read sprites
    k = (numRevisions * sizeof(spritetype)) | 0x7474614d;
    for (i = 0; i < numsprites; ++i)
    {
        if (mapver == 7)
        {
            Decrypt (&bspr[i], data, sizeof(spritetype), k);
        }
        else
        {
            memcpy (&bspr[i], data, sizeof(spritetype));
        }
        data += sizeof(spritetype);
        if (bspr[i].extra > 0)	// copy Xsprite
        {
            assert(sizeof(Xsprite) == 56);
            memcpy(&xspr[i], data, sizeof(Xsprite));
            data += sizeof(Xsprite);
        }
        else
        {
            memset(&xspr[i], 0, sizeof(Xsprite));
        }
    }

    // Now convert to Doom format, since we've extracted all the standard
    // BUILD info from the map we need. (Sprites are ignored.)
    LoadSectors (bsec);
    LoadWalls (bwal, numWalls, bsec);
    *mapthings = new FMapThing[numsprites];
    *numspr = LoadSprites (bspr, xspr, numsprites, bsec, *mapthings);

    delete[] bsec;
    delete[] bwal;
    delete[] bspr;
    delete[] xspr;

    return true;
}