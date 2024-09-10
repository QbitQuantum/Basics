// read_boot_code_data
static uint8 *
read_boot_code_data(const char* programPath)
{
	// open our executable
	BFile executableFile;
	status_t error = executableFile.SetTo(programPath, B_READ_ONLY);
	if (error != B_OK) {
		fprintf(stderr, "Error: Failed to open my executable file (\"%s\": "
			"%s\n", programPath, strerror(error));
		exit(1);
	}

	uint8 *bootCodeData = new uint8[kBootCodeSize];

	// open our resources
	BResources resources;
	error = resources.SetTo(&executableFile);
	const void *resourceData = NULL;
	if (error == B_OK) {
		// read the boot block from the resources
		size_t resourceSize;
		resourceData = resources.LoadResource(B_RAW_TYPE, 666, &resourceSize);

		if (resourceData && resourceSize != (size_t)kBootCodeSize) {
			resourceData = NULL;
			printf("Warning: Something is fishy with my resources! The boot "
				"code doesn't have the correct size. Trying the attribute "
				"instead ...\n");
		}
	}

	if (resourceData) {
		// found boot data in the resources
		memcpy(bootCodeData, resourceData, kBootCodeSize);
	} else {
		// no boot data in the resources; try the attribute
		ssize_t bytesRead = executableFile.ReadAttr("BootCode", B_RAW_TYPE,
			0, bootCodeData, kBootCodeSize);
		if (bytesRead < 0) {
			fprintf(stderr, "Error: Failed to read boot code from resources "
				"or attribute.\n");
			exit(1);
		}
		if (bytesRead != kBootCodeSize) {
			fprintf(stderr, "Error: Failed to read boot code from resources, "
				"and the boot code in the attribute has the wrong size!\n");
			exit(1);
		}
	}

	return bootCodeData;
}