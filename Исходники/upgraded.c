int main(int argc, char *argv[]) {
    pid_t sid;
    char upgfile[512];
    int tPid;
    struct stat stat_buf;
    int use_storage_firmware = 0;
    if(argc < 2) {
        print_usage_exit(1);
    }
    /* FIX ME !!!
     * If we need further parameters for this procedure, then we should use
     * opt parser and formal parameters.
     * */
    if(argv[1][0] == '-') {
        switch(argv[1][1]) {
            case 'b':
                strcpy(upgfile, "/tmp/mnt/USB/firmware.bin");
                if(stat(upgfile, &stat_buf)) {
                    printf("There is no \"firmware.bin\" in USB or USB is not inserted\n");
                    print_usage_exit(1);
                }
                else {
                    use_storage_firmware = 1;
                    printf("Using \"firmware.bin\" in USB to upgrade.\n");
                }
                strcpy(upgfile, "/usr/sbin/ezpup /tmp/mnt/USB/firmware.bin");
                break;
            case 's':
                strcpy(upgfile, "/tmp/mnt/SD/firmware.bin");
                if(stat(upgfile, &stat_buf)) {
                    printf("There is no \"firmware.bin\" in SD card or SD card is inserted\n");
                    print_usage_exit(1);
                }
                else {
                    use_storage_firmware = 2;
                    printf("Using \"firmware.bin\" in SD card to upgrade.\n");
                }
                strcpy(upgfile, "/usr/sbin/ezpup /tmp/mnt/SD/firmware.bin");
                break;
            case 'a':
                strcpy(upgfile, "/tmp/mnt/SD/firmware.bin");
                if(stat(upgfile, &stat_buf)) {
                    printf("There is no \"firmware.bin\" in SD card or SD card is inserted\n");
                    strcpy(upgfile, "/tmp/mnt/USB/firmware.bin");
                    if(stat(upgfile, &stat_buf)) {
                        printf("There is no \"firmware.bin\" in USB or USB is not inserted\n");
                        print_usage_exit(1);
                    }
                    else {
                        use_storage_firmware = 1;
                        printf("Using \"firmware.bin\" in USB to upgrade.\n");
                        strcpy(upgfile, "/usr/sbin/ezpup /tmp/mnt/USB/firmware.bin");
                    }
                }
                else {
                    use_storage_firmware = 2;
                    printf("Using \"firmware.bin\" in SD card to upgrade.\n");
                    strcpy(upgfile, "/usr/sbin/ezpup /tmp/mnt/SD/firmware.bin");
                }
                break;
            case 'u':
                if(argc == 3) {
                    snprintf(upgfile, sizeof(upgfile), "wget %s -O /tmp/firmware 2>&1 | cat > /tmp/fw_log.txt", argv[2]);
                    system(upgfile);
                    if(!check_wget_ok("/tmp/fw_log.txt")) {
                        printf("Unable to get URL %s\n", argv[2]);
                        print_usage_exit(1);
                    }
                    snprintf(upgfile, sizeof(upgfile), "/usr/sbin/ezpup /tmp/firmware");
                    printf("Get firmware from %s successfully, using /tmp/firmware to upgrade.\n", argv[2]);
                }
                else {
                    print_usage_exit(1);
                }
                break;
        }
    } else {
        snprintf(upgfile, sizeof(upgfile), "/usr/sbin/ezpup %s", argv[1]);
    }
    tPid = fork();
    if(tPid < 0)
    {
        reboot(RB_AUTOBOOT);
        exit(1); // Error on fork
    }
    else if(tPid > 0)
    {
        exit(0);
    }
    else
    {
        FILE *fp;
        sid = setsid();
        if (sid < 0)
            exit(EXIT_FAILURE);
#if defined(PLATFORM_AXA)
        system("/usr/sbin/ezp-i2c gauge host booting");
#endif
        system("/sbin/stop_services.sh");
        system("/sbin/reserve_link.sh");
        system(upgfile);
        system("/tmp/ezp-i2c gauge upgrade finish");
        fp = fopen("/tmp/fw_incorrect", "r");
        if(fp) {
            printf("Upgrade failed, firmware incorrect\n");
            fclose(fp);
        } else {
            printf("Upgrade successfully\n");
            fp = fopen("/tmp/fw_correct", "w+");
            if(fp) {
                fprintf(fp, "success\n");
                fclose(fp);
            }
        }
        sleep(5);
        reboot(RB_AUTOBOOT);
    }
    return 0;
}