void vdoa_test(void)
{
    uint8_t *buffer = malloc(IMG_WIDTH * IMG_HEIGHT * 1.5 + 0x1000);
	/*the VDOA file is extracted from VPU decoder in tiled frame mode*/
	uint8_t readfile[] = "vdoa_in.yuv";
    int count, err;
    int fin = 0;

    if (buffer == NULL)
        return;

    hdmi_1080P60_video_output(1, 0);
    if (FSInit(NULL, bufy, maxdevices, maxhandles, maxcaches) != SUCCESS) {
        err = -1;
        return;
    }

    FSDriveInit(DeviceNum);
    SetCWDHandle(DeviceNum);

    print_media_fat_info(DeviceNum);

    if ((fin = Fopen(readfile, (uint8_t *) "r")) < 0) {
        printf("cannot open file %s!\n", readfile);
        return;
    }

    buffer = (uint8_t *) (((uint32_t) buffer + 0xFFF) & 0xFFFFF000);

    set_card_access_mode(1, 0);
    
    count = Fread(fin, (uint8_t *) buffer, IMG_WIDTH * IMG_HEIGHT * 1.5);

    vdoa_clear_interrupt();
    vdoa_setup(IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH, IMG_WIDTH, 0, 0, 16, 0);
    vdoa_start((uint32_t) buffer, IMG_WIDTH * IMG_HEIGHT, IPU2_CH23_EBA0, IMG_WIDTH * 1088);

    while (!vdoa_check_tx_eot()) ;
    Fclose(fin);
}