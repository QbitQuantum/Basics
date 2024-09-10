void ExtractZakC64::execute() {
    int i, j;
    unsigned short signature;
    char fname[256];

    // Two disks...
    Common::Filename inpath1(_inputPaths[0].path);
    Common::Filename inpath2(_inputPaths[1].path);
    Common::Filename &outpath = _outputPath;

    if (outpath.empty())
        // Standard output path
        outpath.setFullPath("out/");

    Common::File input1(inpath1, "rb");
    Common::File input2(inpath2, "rb");

    /* check signature */
    signature = input1.readUint16LE();
    if (signature != 0x0A31)
        error("Signature not found in disk 1!");
    signature = input2.readUint16LE();
    if (signature != 0x0132)
        error("Signature not found in disk 2!");

    outpath.setFullName("00.LFL");
    Common::File output(outpath, "wb");
    output.setXorMode(0xFF);
    print("Creating 00.LFL...");

    /* write signature */
    output.writeUint16LE(signature);

    /* copy object flags */
    for (i = 0; i < 775; i++)
        output.writeByte(input1.readByte());

    /* copy room offsets */
    for (i = 0; i < NUM_ROOMS; i++) {
        room_disks_c64[i] = input1.readByte();
        output.writeByte(room_disks_c64[i]);
    }
    for (i = 0; i < NUM_ROOMS; i++) {
        room_sectors_c64[i] = input1.readByte();
        output.writeByte(room_sectors_c64[i]);
        room_tracks_c64[i] = input1.readByte();
        output.writeByte(room_tracks_c64[i]);
    }

    /* copy costume offsets */
    for (i = 0; i < 38; i++)
        output.writeByte(input1.readByte());
    for (i = 0; i < 38; i++)
        output.writeUint16LE(input1.readUint16LE());

    /* copy script offsets */
    for (i = 0; i < 155; i++)
        output.writeByte(input1.readByte());
    for (i = 0; i < 155; i++)
        output.writeUint16LE(input1.readUint16LE());

    /* copy sound offsets */
    for (i = 0; i < 127; i++)
        output.writeByte(input1.readByte());
    for (i = 0; i < 127; i++)
        output.writeUint16LE(input1.readUint16LE());

    output.close();

    for (i = 0; i < NUM_ROOMS; i++) {
        Common::File *input;

        if (room_disks_c64[i] == '1')
            input = &input1;
        else if (room_disks_c64[i] == '2')
            input = &input2;
        else
            continue;

        sprintf(fname, "%02i.LFL", i);
        outpath.setFullName(fname);
        output.open(outpath, "wb");

        print("Creating %s...", fname);
        input->seek((SectorOffset[room_tracks_c64[i]] + room_sectors_c64[i]) * 256, SEEK_SET);

        for (j = 0; j < ResourcesPerFile[i]; j++) {
            unsigned short len;

            do {
                len = input->readUint16LE();
                output.writeUint16LE(len);
            } while (len == 0xffff);

            for (len -= 2; len > 0; len--) {
                output.writeByte(input->readByte());
            }
        }

        input->rewind();
    }

    print("All done!");
}