void initializeFSM() {
	LOADED_IMAGE image;
	PSTR imageFilename;
	//imageFilename = argv[1];
	//imageFilename = "test_short_instruction.exe";
	//imageFilename = "test_prefix.exe";
	//imageFilename = "prefix_4_opcode_1.exe";
	imageFilename = "prefix_2_opcode_1_modRM_SIB_imm.exe";
	//imageFilename = "opcode_1_modRM_SIB_imm.exe";
	
	if (!MapAndLoad(imageFilename, NULL, &image, FALSE, TRUE)) {
		PRINT_ERROR("MapAndLoad", __FILE__, __LINE__);
		return;
	}
	g_va = ImageRvaToVa(image.FileHeader, image.MappedAddress,
						  image.FileHeader->OptionalHeader.BaseOfCode, NULL);
}