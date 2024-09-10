int deviceConnectHardDiskRemove(const char *fileName) {
    t_nubitcc count;
    FILE *image;
    if (fileName) {
        image = FOPEN(fileName, "wb");
        if (image) {
            if (!vhdd.connect.flagReadOnly)
                count = FWRITE((void *) vhdd.connect.pImgBase, sizeof(t_nubit8), vhddGetImageSize, image);
            vhdd.connect.flagDiskExist = False;
            FCLOSE(image);
        } else {
            return True;
        }
    }
    vhdd.connect.flagDiskExist = False;
    MEMSET((void *) vhdd.connect.pImgBase, Zero8, vhddGetImageSize);
    return False;
}