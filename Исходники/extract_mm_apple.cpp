void ExtractMMApple::execute() {
	int i, j;
	unsigned short signature;
	char fname[256];

	Common::Filename inpath1(_inputPaths[0].path);
	Common::Filename inpath2(_inputPaths[1].path);
	Common::Filename &outpath = _outputPath;

	if (outpath.empty())
		// Standard output path
		outpath.setFullPath("out/");

	Common::File input1(inpath1, "rb");
	Common::File input2(inpath2, "rb");

	input1.seek(142080, SEEK_SET);
	input2.seek(143104, SEEK_SET);

	/* check signature */
	signature = input1.readUint16LE();
	if (signature != 0x0A31)
		error("Signature not found in disk 1!");

	signature = input2.readUint16LE();
	if (signature != 0x0032)
		error("Signature not found in disk 2!");

	outpath.setFullName("00.LFL");
	Common::File output(outpath, "wb");
	// All output should be xored
	output.setXorMode(0xFF);
	print("Creating 00.LFL...\n");

	/* write signature */
	output.writeUint16LE(signature);

	/* copy object flags */
	for (i = 0; i < 256; i++)
		output.writeByte(input1.readByte());

	/* copy room offsets */
	for (i = 0; i < NUM_ROOMS; i++) {
		room_disks_apple[i] = input1.readByte();
		output.writeByte(room_disks_apple[i]);
	}
	for (i = 0; i < NUM_ROOMS; i++) {
		room_sectors_apple[i] = input1.readByte();
		output.writeByte(room_sectors_apple[i]);
		room_tracks_apple[i] = input1.readByte();
		output.writeByte(room_tracks_apple[i]);
	}

	/* copy costume offsets */
	for (i = 0; i < 25; i++)
		output.writeByte(input1.readByte());
	for (i = 0; i < 25; i++)
		output.writeUint16LE(input1.readUint16LE());

	/* copy script offsets */
	for (i = 0; i < 160; i++)
		output.writeByte(input1.readByte());
	for (i = 0; i < 160; i++)
		output.writeUint16LE(input1.readUint16LE());

	/* copy sound offsets */
	for (i = 0; i < 70; i++)
		output.writeByte(input1.readByte());
	for (i = 0; i < 70; i++)
		output.writeUint16LE(input1.readUint16LE());

	/* NOTE: Extra 92 bytes of unknown data */

	for (i = 0; i < NUM_ROOMS; i++) {
		Common::File *input;

		if (room_disks_apple[i] == '1')
			input = &input1;
		else if (room_disks_apple[i] == '2')
			input = &input2;
		else
			continue;

		sprintf(fname, "%02i.LFL", i);
		outpath.setFullName(fname);
		output.open(outpath, "wb");

		print("Creating %s...\n", fname);
		input->seek((SectorOffset[room_tracks_apple[i]] + room_sectors_apple[i]) * 256, SEEK_SET);

		for (j = 0; j < ResourcesPerFile[i]; j++) {
			unsigned short len = input->readUint16LE();
			output.writeUint16LE(len);

			for (len -= 2; len > 0; len--)
				output.writeByte(input->readByte());
		}
		input->rewind();
	}
	print("All done!");
}