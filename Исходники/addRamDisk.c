int main(int argc, char **argv)
{
	char inbuf[4096];
	struct addr_range vmlinux;
	FILE *ramDisk;
	FILE *inputVmlinux;
	FILE *outputVmlinux;

	char *rd_name, *lx_name, *out_name;

	size_t i;
	unsigned long ramFileLen;
	unsigned long ramLen;
	unsigned long roundR;
	unsigned long offset_end;

	unsigned long kernelLen;
	unsigned long actualKernelLen;
	unsigned long round;
	unsigned long roundedKernelLen;
	unsigned long ramStartOffs;
	unsigned long ramPages;
	unsigned long roundedKernelPages;
	unsigned long hvReleaseData;
	u_int32_t eyeCatcher = 0xc8a5d9c4;
	unsigned long naca;
	unsigned long xRamDisk;
	unsigned long xRamDiskSize;
	long padPages;
  
  
	if (argc < 2) {
		fprintf(stderr, "Name of RAM disk file missing.\n");
		exit(1);
	}
	rd_name = argv[1];

	if (argc < 3) {
		fprintf(stderr, "Name of vmlinux file missing.\n");
		exit(1);
	}
	lx_name = argv[2];

	if (argc < 4) {
		fprintf(stderr, "Name of vmlinux output file missing.\n");
		exit(1);
	}
	out_name = argv[3];


	ramDisk = fopen(rd_name, "r");
	if ( ! ramDisk ) {
		fprintf(stderr, "RAM disk file \"%s\" failed to open.\n", rd_name);
		exit(1);
	}

	inputVmlinux = fopen(lx_name, "r");
	if ( ! inputVmlinux ) {
		fprintf(stderr, "vmlinux file \"%s\" failed to open.\n", lx_name);
		exit(1);
	}
  
	outputVmlinux = fopen(out_name, "w+");
	if ( ! outputVmlinux ) {
		fprintf(stderr, "output vmlinux file \"%s\" failed to open.\n", out_name);
		exit(1);
	}

	i = fread(inbuf, 1, sizeof(inbuf), inputVmlinux);
	if (i != sizeof(inbuf)) {
		fprintf(stderr, "can not read vmlinux file %s: %u\n", lx_name, i);
		exit(1);
	}

	i = check_elf64(inbuf, sizeof(inbuf), &vmlinux);
	if (i == 0) {
		fprintf(stderr, "You must have a linux kernel specified as argv[2]\n");
		exit(1);
	}

	/* Input Vmlinux file */
	fseek(inputVmlinux, 0, SEEK_END);
	kernelLen = ftell(inputVmlinux);
	fseek(inputVmlinux, 0, SEEK_SET);
	printf("kernel file size = %lu\n", kernelLen);

	actualKernelLen = kernelLen - ElfHeaderSize;

	printf("actual kernel length (minus ELF header) = %lu\n", actualKernelLen);

	round = actualKernelLen % 4096;
	roundedKernelLen = actualKernelLen;
	if ( round )
		roundedKernelLen += (4096 - round);
	printf("Vmlinux length rounded up to a 4k multiple = %ld/0x%lx \n", roundedKernelLen, roundedKernelLen);
	roundedKernelPages = roundedKernelLen / 4096;
	printf("Vmlinux pages to copy = %ld/0x%lx \n", roundedKernelPages, roundedKernelPages);

	offset_end = _ALIGN_UP(vmlinux.memsize, 4096);
	/* calc how many pages we need to insert between the vmlinux and the start of the ram disk */
	padPages = offset_end/4096 - roundedKernelPages;

	/* Check and see if the vmlinux is already larger than _end in System.map */
	if (padPages < 0) {
		/* vmlinux is larger than _end - adjust the offset to the start of the embedded ram disk */ 
		offset_end = roundedKernelLen;
		printf("vmlinux is larger than _end indicates it needs to be - offset_end = %lx \n", offset_end);
		padPages = 0;
		printf("will insert %lx pages between the vmlinux and the start of the ram disk \n", padPages);
	}
	else {
		/* _end is larger than vmlinux - use the offset to _end that we calculated from the system map */
		printf("vmlinux is smaller than _end indicates is needed - offset_end = %lx \n", offset_end);
		printf("will insert %lx pages between the vmlinux and the start of the ram disk \n", padPages);
	}



	/* Input Ram Disk file */
	// Set the offset that the ram disk will be started at.
	ramStartOffs = offset_end;  /* determined from the input vmlinux file and the system map */
	printf("Ram Disk will start at offset = 0x%lx \n", ramStartOffs);
  
	fseek(ramDisk, 0, SEEK_END);
	ramFileLen = ftell(ramDisk);
	fseek(ramDisk, 0, SEEK_SET);
	printf("%s file size = %ld/0x%lx \n", rd_name, ramFileLen, ramFileLen);

	ramLen = ramFileLen;

	roundR = 4096 - (ramLen % 4096);
	if ( roundR ) {
		printf("Rounding RAM disk file up to a multiple of 4096, adding %ld/0x%lx \n", roundR, roundR);
		ramLen += roundR;
	}

	printf("Rounded RAM disk size is %ld/0x%lx \n", ramLen, ramLen);
	ramPages = ramLen / 4096;
	printf("RAM disk pages to copy = %ld/0x%lx\n", ramPages, ramPages);



  // Copy 64K ELF header
	for (i=0; i<(ElfPages); ++i) {
		get4k( inputVmlinux, inbuf );
		put4k( outputVmlinux, inbuf );
	}

	/* Copy the vmlinux (as full pages). */
	fseek(inputVmlinux, ElfHeaderSize, SEEK_SET);
	for ( i=0; i<roundedKernelPages; ++i ) {
		get4k( inputVmlinux, inbuf );
		put4k( outputVmlinux, inbuf );
	}
  
	/* Insert pad pages (if appropriate) that are needed between */
	/* | the end of the vmlinux and the ram disk. */
	for (i=0; i<padPages; ++i) {
		memset(inbuf, 0, 4096);
		put4k(outputVmlinux, inbuf);
	}

	/* Copy the ram disk (as full pages). */
	for ( i=0; i<ramPages; ++i ) {
		get4k( ramDisk, inbuf );
		put4k( outputVmlinux, inbuf );
	}

	/* Close the input files */
	fclose(ramDisk);
	fclose(inputVmlinux);
	/* And flush the written output file */
	fflush(outputVmlinux);



	/* Fixup the new vmlinux to contain the ram disk starting offset (xRamDisk) and the ram disk size (xRamDiskSize) */
	/* fseek to the hvReleaseData pointer */
	fseek(outputVmlinux, ElfHeaderSize + 0x24, SEEK_SET);
	if (fread(&hvReleaseData, 4, 1, outputVmlinux) != 1) {
		death("Could not read hvReleaseData pointer\n", outputVmlinux, out_name);
	}
	hvReleaseData = ntohl(hvReleaseData); /* Convert to native int */
	printf("hvReleaseData is at %08lx\n", hvReleaseData);

	/* fseek to the hvReleaseData */
	fseek(outputVmlinux, ElfHeaderSize + hvReleaseData, SEEK_SET);
	if (fread(inbuf, 0x40, 1, outputVmlinux) != 1) {
		death("Could not read hvReleaseData\n", outputVmlinux, out_name);
	}
	/* Check hvReleaseData sanity */
	if (memcmp(inbuf, &eyeCatcher, 4) != 0) {
		death("hvReleaseData is invalid\n", outputVmlinux, out_name);
	}
	/* Get the naca pointer */
	naca = ntohl(*((u_int32_t*) &inbuf[0x0C])) - KERNELBASE;
	printf("Naca is at offset 0x%lx \n", naca);

	/* fseek to the naca */
	fseek(outputVmlinux, ElfHeaderSize + naca, SEEK_SET);
	if (fread(inbuf, 0x18, 1, outputVmlinux) != 1) {
		death("Could not read naca\n", outputVmlinux, out_name);
	}
	xRamDisk = ntohl(*((u_int32_t *) &inbuf[0x0c]));
	xRamDiskSize = ntohl(*((u_int32_t *) &inbuf[0x14]));
	/* Make sure a RAM disk isn't already present */
	if ((xRamDisk != 0) || (xRamDiskSize != 0)) {
		death("RAM disk is already attached to this kernel\n", outputVmlinux, out_name);
	}
	/* Fill in the values */
	*((u_int32_t *) &inbuf[0x0c]) = htonl(ramStartOffs);
	*((u_int32_t *) &inbuf[0x14]) = htonl(ramPages);

	/* Write out the new naca */
	fflush(outputVmlinux);
	fseek(outputVmlinux, ElfHeaderSize + naca, SEEK_SET);
	if (fwrite(inbuf, 0x18, 1, outputVmlinux) != 1) {
		death("Could not write naca\n", outputVmlinux, out_name);
	}
	printf("Ram Disk of 0x%lx pages is attached to the kernel at offset 0x%08lx\n",
	       ramPages, ramStartOffs);

	/* Done */
	fclose(outputVmlinux);
	/* Set permission to executable */
	chmod(out_name, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);

	return 0;
}