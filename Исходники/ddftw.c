int getLocationsViafstab()
{
    FILE* fp;
    char line[512];
    int ret = 0;

    // In this case, we'll first get the partitions we care about (with labels)
    fp = fopen("/etc/recovery.fstab", "rt");
    if (fp == NULL)
    {
        LOGE("=> Unable to open /etc/recovery.fstab\n");
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char mount[32], fstype[32], device[256];
        char* pDevice = device;

        if (line[0] != '/')     continue;
        sscanf(line + 1, "%s %s %s", mount, fstype, device);

        // Attempt to flip mounts until we find the block device
        char realDevice[256];
        memset(realDevice, 0, sizeof(realDevice));
        while (readlink(device, realDevice, sizeof(realDevice)) > 0)
        {
            strcpy(device, realDevice);
            memset(realDevice, 0, sizeof(realDevice));
        }

        if (device[0] != '/')   pDevice = NULL;
        setLocationData(mount, pDevice, pDevice, fstype, 0);
    }
    fclose(fp);

    // We can ignore the results of this call. But if it works, it at least helps get details
    getSizesViaPartitions();

    // Now, let's retrieve base partition sizes
    if (isEMMCdevice)
    {
        fp = __popen("fdisk -l /dev/block/mmcblk0","r");
        if (fp == NULL)
        {
            LOGE("=> Unable to retrieve partition sizes via fdisk\n");
            return -1;
        }
    
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char isBoot[64], device[64], blocks[2][16], *pSizeBlock;
            unsigned long long size = 0;
    
            if (line[0] != '/')     continue;
            sscanf(line, "%s %s %*s %s %s", device, isBoot, blocks[0], blocks[1]);
    

            if (isBoot[0] == '*')   pSizeBlock = blocks[1];
            else                    pSizeBlock = blocks[0];

            // If the block size isn't accurate, don't record it.
            if (pSizeBlock[strlen(pSizeBlock)-1] == '+')    pSizeBlock = NULL;

            // This could be NULL if we decided the size wasn't accurate
            if (pSizeBlock)
            {
                size = ((unsigned long long) atol(pSizeBlock)) * 1024ULL;
            }

            if (size && (setLocationData(NULL, device, NULL, NULL, size) == 0))
            {
//                LOGI("  Mount %s size: %d\n", device, size);
            }
        }
        fclose(fp);
    }

    return ret;
}