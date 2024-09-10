static inline void installer(u32 a9lhBoot)
{
    if(!mountSD())
        shutdown(1, "Error: failed to mount the SD card");

    const char *path;
    u32 updatea9lh = 0;

    //If making a first install, we need the OTP
    if(!a9lhBoot)
    {
        //Read OTP
        path = "homebrew/3ds/ShadowNAND_Installer/otp.bin";
        if(fileRead((void *)OTP_OFFSET, path) != 256)
        {
            const u8 zeroes[256] = {0};
            if(memcmp((void *)OTP_FROM_MEM, zeroes, 256) == 0)
                shutdown(1, "Error: otp.bin doesn't exist and can't be dumped");

            fileWrite((void *)OTP_FROM_MEM, path, 256);
            memcpy((void *)OTP_OFFSET, (void *)OTP_FROM_MEM, 256);
        }
    }

    //Setup the key sector de/encryption with the SHA register or otp.bin
    setupKeyslot0x11(a9lhBoot, (void *)OTP_OFFSET);

    //Calculate the CTR for the 3DS partitions
    getNandCTR();

    //Get NAND FIRM0 and test that the CTR is correct
    readFirm0((u8 *)FIRM0_OFFSET, FIRM0_SIZE);
    if(memcmp((void *)FIRM0_OFFSET, "FIRM", 4) != 0)
        shutdown(1, "Error: failed to setup FIRM encryption");

    //If booting from A9LH or on N3DS, we can use the key sector from NAND
    if(a9lhBoot || console)
    {
		 updatea9lh = 1;
		 //Read decrypted key sector
         path = "homebrew/3ds/ShadowNAND_Installer/secret_sector.bin";
         if(fileRead((void *)SECTOR_OFFSET, path) != 0x200)
             shutdown(1, "Error: secret_sector.bin doesn't exist or has\na wrong size");
         if(!verifyHash((void *)SECTOR_OFFSET, 0x200, sectorHash))
             shutdown(1, "Error: secret_sector.bin is invalid or corrupted");
    }

    if(!a9lhBoot || updatea9lh)
    {
        //Generate and encrypt a per-console A9LH key sector
        generateSector((u8 *)SECTOR_OFFSET, 0);

        //Read FIRM0
        path = "homebrew/3ds/ShadowNAND_Installer/firm0.bin";
        if(fileRead((void *)FIRM0_OFFSET, path) != FIRM0_SIZE)
            shutdown(1, "Error: firm0.bin doesn't exist or has a wrong size");

        if(!verifyHash((void *)FIRM0_OFFSET, FIRM0_SIZE, firm0Hash))
            shutdown(1, "Error: firm0.bin is invalid or corrupted");
    }

    if(!a9lhBoot)
    {
        //Read FIRM1
        path = "homebrew/3ds/ShadowNAND_Installer/firm1.bin";
        if(fileRead((void *)FIRM1_OFFSET, path) != FIRM1_SIZE)
            shutdown(1, "Error: firm1.bin doesn't exist or has a wrong size");

        if(!verifyHash((void *)FIRM1_OFFSET, FIRM1_SIZE, firm1Hash))
            shutdown(1, "Error: firm1.bin is invalid or corrupted");
    }

    //Inject stage1
    memset32((void *)STAGE1_OFFSET, 0, MAX_STAGE1_SIZE);
    path = "homebrew/3ds/ShadowNAND_Installer/payload_stage1.bin";
    u32 size = fileRead((void *)STAGE1_OFFSET, path);
    if(!size || size > MAX_STAGE1_SIZE)
        shutdown(1, "Error: payload_stage1.bin doesn't exist or\nexceeds max size");

    const u8 zeroes[688] = {0};
    if(memcmp(zeroes, (void *)STAGE1_OFFSET, 688) == 0)
        shutdown(1, "Error: the payload_stage1.bin you're attempting\nto install is not compatible");

    //Read stage2
    memset32((void *)STAGE2_OFFSET, 0, MAX_STAGE2_SIZE);
    path = "homebrew/3ds/ShadowNAND_Installer/payload_stage2.bin";
    size = fileRead((void *)STAGE2_OFFSET, path);
    if(!size || size > MAX_STAGE2_SIZE)
        shutdown(1, "Error: payload_stage2.bin doesn't exist or\nexceeds max size");

    //Read alt_stage2
    memset32((void *)ALTSTAGE2_OFFSET, 0, MAX_ALTSTAGE2_SIZE);
    path = "homebrew/3ds/ShadowNAND_Installer/payload_altstage2.bin";
    size = fileRead((void *)ALTSTAGE2_OFFSET, path);
    if(!size || size > MAX_ALTSTAGE2_SIZE)
        shutdown(1, "Error: payload_altstage2.bin doesn't exist or\nexceeds max size");

    posY = drawString("All checks passed, installing...", 10, posY + SPACING_Y, COLOR_WHITE);

    //Point of no return, install stuff in the safest order
    sdmmc_nand_writesectors(0x5A000, 0x20, (vu8 *)ALTSTAGE2_OFFSET);
    sdmmc_nand_writesectors(0x5C000, 0x20, (vu8 *)STAGE2_OFFSET);
    if(!a9lhBoot) writeFirm((u8 *)FIRM1_OFFSET, 1, FIRM1_SIZE);
    if(!a9lhBoot || updatea9lh) sdmmc_nand_writesectors(0x96, 1, (vu8 *)SECTOR_OFFSET);
    writeFirm((u8 *)FIRM0_OFFSET, 0, FIRM0_SIZE);

    shutdown(2, a9lhBoot ? "Update: success!" : "Full install: success!");
}