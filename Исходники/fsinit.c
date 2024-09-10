bool InitImgFS(const char* path) {
    // find drive # of the last image FAT drive
    u32 drv_i = NORM_FS - IMGN_FS;
    char fsname[8];
    for (; drv_i < NORM_FS; drv_i++) {
        snprintf(fsname, 7, "%lu:", drv_i);
        if (!(DriveType(fsname)&DRV_IMAGE)) break;
    }
    // deinit image filesystem
    DismountDriveType(DRV_IMAGE);
    // (re)mount image, done if path == NULL
    u64 type = MountImage(path);
    InitVirtualImageDrive();
    if ((type&IMG_NAND) && (drv_i < NORM_FS)) drv_i = NORM_FS;
    else if ((type&IMG_FAT) && (drv_i < NORM_FS - IMGN_FS + 1)) drv_i = NORM_FS - IMGN_FS + 1;
    // reinit image filesystem
    for (u32 i = NORM_FS - IMGN_FS; i < drv_i; i++) {
        snprintf(fsname, 7, "%lu:", i);
        fs_mounted[i] = (f_mount(fs + i, fsname, 1) == FR_OK);
    }
    return GetMountState();
}