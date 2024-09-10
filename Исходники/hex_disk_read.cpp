int disk_dump_hex_data(int drive_number, long total_sectors_to_read, LP_PROGRAM_DATA PData)
{
	unsigned int buffer[512];
	char letra;
	DWORD bytes_por_setor;
    char const *unidade = "";
	long long tam_disco;
	int falhas = 0, sector_index;
	FILE *inputFile;
	FILE *outputFile;
	struct conversion_data a1;
	struct conversion_mode a2;
	CONVERSION_DATA StructConv = &a1;
	CONVERSION_MODE StructMode = &a2;
	short res;
	HANDLE DiscoRigido;
    CHAR nome_hd[16], cmdLine[MAX_PATH], localAtual[MAX_PATH], currentFile[MAX_PATH], HexFile2[MAX_PATH], HexFile[MAX_PATH];
	DWORD ptr;
	NTFS_VOLUME_DATA_BUFFER disk_data_buffer;
	DWORD bytesLidos, totalBytesLidos = 0;
	
	letra = convert_disk_number_to_letter(drive_number);
	if(letra == 0) return 0x83;
	
	if(!IsUserAnAdmin()) 
	{	
		msgaviso("You are not admin ... Changing privileges ...\n");
        if(GetCurrentDirectoryA(MAX_PATH, (LPSTR)localAtual))
		{
            sprintf(cmdLine, "%s %s %s %s", PData->command_line[1], PData->command_line[2], PData->command_line[3], PData->command_line[4]);
            sprintf(currentFile, "%s\\hexdumper.exe", localAtual);
            ShellExecuteA(0, "runas", currentFile, cmdLine, (char const *)localAtual, SW_SHOW);
		}
		exit(GetLastError());
	}
	
	sprintf(nome_hd, "\\\\.\\%c:", letra);
	DiscoRigido = CreateFileA( nome_hd, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	
	if(DiscoRigido == INVALID_HANDLE_VALUE) 
		return 0x81;
	
	if(!DeviceIoControl(DiscoRigido, FSCTL_GET_NTFS_VOLUME_DATA, 0, 0, &disk_data_buffer, sizeof(disk_data_buffer), &ptr, NULL))
	{
		if(DiscoRigido) CloseHandle(DiscoRigido);
		return 0x80;
	}
	
	bytes_por_setor = disk_data_buffer.BytesPerSector;
	tam_disco = disk_data_buffer.NumberSectors.QuadPart * disk_data_buffer.BytesPerSector;
	
    unidade = "";

	assert(tam_disco > 0);
	
	if(tam_disco <= _1KB)
		unidade = "Bytes";
	else if(tam_disco <= _1MB) {
		tam_disco /= _1KB;
		unidade = "KB";
	}
	else if(tam_disco <= _1GB) {
		tam_disco /= _1MB;
		unidade = "MB";
	}
	else {
		tam_disco /= _1GB;
		unidade = "GB";
	}
	
	long long conversion_size = total_sectors_to_read * bytes_por_setor;

	if((conversion_size / _1GB) > (0xffffffff / _1GB)) {
		msgerro( "Data bigger than %.2lf GB aren´t supported yet\n", (double)(0xffffffff / _1GB));
		msgerro("Your conversion size is: %.2lf KB\n", (double)conversion_size / _1KB);
		return 0x86;
	}
	
	sprintf(HexFile, "hd%d.txt", drive_number);
	outputFile = fopen(HexFile, "wb");
	assert(outputFile != NULL);
	
	if(PData->verbose) 
	{
		fprintf(stdout, "\n");
		fprintf(stdout, "\t-> Disk size: %.2lf %s\n\t-> Bytes per sector %ld\n", (double)tam_disco, unidade, bytes_por_setor);
		fprintf(stdout, "\t-> Serial number: 0x%.8x\n\t-> MFT start address: 0x%.8x\n", disk_data_buffer.VolumeSerialNumber,
						disk_data_buffer.MftStartLcn);
		fprintf(stdout, "\t-> Number of sectors to read: %ld\n", total_sectors_to_read);
		fprintf(stdout, "\t-> Data length to read: %.2lf KB\n", (double)conversion_size / _1KB);
		fprintf(stdout, "\n");
	}

	if (!DeviceIoControl(DiscoRigido, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &ptr, NULL))
		if(PData->verbose)
			msgaviso( "failed to block volume ...\n");
		
	for(sector_index = 0; sector_index < total_sectors_to_read; sector_index++)
	{
		if(!DiscoRigido || DiscoRigido == INVALID_HANDLE_VALUE) break;
		
		bytesLidos = read_disk_sector(sector_index, bytes_por_setor, buffer, DiscoRigido);
		if(bytesLidos) 
		{
			fwrite(buffer, 1, bytesLidos, outputFile);
			totalBytesLidos += bytesLidos;
		} else {
			falhas++;
			if(falhas > 100)
				break;
		}
	}
	
	if(!DeviceIoControl(DiscoRigido, FSCTL_UNLOCK_VOLUME, 0, 0, NULL, 0, &ptr, NULL)) {
		if(PData->verbose)
			msgaviso( "Failed to unblock volume. Maybe it is already unblocked\n");
	}
	
	if(DiscoRigido) CloseHandle(DiscoRigido);
	if(outputFile) fclose(outputFile); 
	
	if (PData->verbose) {
		msginfo("Converting data to HEX format ...\n");
		msginfo("Opening %s ...\n", HexFile);
	}

	inputFile = fopen(HexFile, "rb");
	sprintf(HexFile2, "dump_of_%s", HexFile);
	
	outputFile = fopen(HexFile2, "wb");
	
	assert(inputFile != NULL);
	assert(outputFile != NULL);
	
	// agora descarregar o arquivo no formato hexadecimal ...
	
	StructConv->bytes_to_read = totalBytesLidos;
	StructMode->s_mode = DEFAULT_MODE;
	
	res = hex_file_write_data_in_specified_mode(StructConv, StructMode, inputFile, outputFile, DEFAULT_MODE);
	if(PData->verbose && res == 0xFF) {
		msgerro( "Cannot make HEX dump ...\n");
	}
	else if(PData->verbose && res == 0) 
		msgsucesso( "Hex dump completed ...\nOutput: %s\n", HexFile2);
	
	if(inputFile) fclose(inputFile);
	if(outputFile) fclose(outputFile);

	return 0;
}