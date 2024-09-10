// Faz a reposicao (Restore) ou guarda uma copia do ficheiro (Backup), conforme o bool recebido.
// backupNrestore = true -> Backup
// backupNrestore = false -> Restore
BOOL CopyFile(BOOL backupNrestore, HBACKUPENTRY copyRequest){
	
	FILE * origin; FILE * destiny;
	CHAR auxBuffer[MAX_PATH];
	DWORD i, ofnIdx; //ofnIdx serve para copiar todos os chars para um char* local, com o nome do ficheiro original
	CHAR* separator = "\\", *terminator = "\0";
	SIZE_T sz, filePathSize = strlen((CHAR*)backupService->fileStoragePath) + strlen(separator) + strlen((CHAR*)copyRequest->file) + 1;
	CHAR*repoFileName, *originalFileName;
	
	repoFileName = (CHAR*)malloc(filePathSize);
	originalFileName = (CHAR*)malloc(strlen((CHAR*)copyRequest->file) + 1);

	sz = strlen((CHAR*)backupService->fileStoragePath) + 1;
	strcpy_s(repoFileName, sz, (CHAR*)backupService->fileStoragePath);

	sz += strlen(separator);
	strcat_s(repoFileName, filePathSize, separator);

	ofnIdx = 0;
	for (i = 0; i < STR_MAX_SIZE; i++){
		CHAR * part = (CHAR*)(copyRequest->file + i*sizeof(CHAR));
		if (strcmp(part, terminator) == 0)
			break;
		sz++; ofnIdx++;
		strcat_s(repoFileName, sz, part);

		if (ofnIdx == 1)
			strcpy_s(originalFileName, ofnIdx + 1, part);
		else
			strcat_s(originalFileName, ofnIdx + 1, part);
	}

	if (fopen_s(&origin, backupNrestore?originalFileName : repoFileName, "rb") != 0){// abrir ficheiro origem para ler
		printf("\nERRO... O ficheiro %s nao existe!", backupNrestore ? originalFileName : repoFileName);
		return FALSE;
	}

	if (fopen_s(&destiny, backupNrestore ? repoFileName : originalFileName, "wb+") != 0){
		printf("\nERRO... Nao foi possivel criar o ficheiro %s ! Verifique se o caminho existe!", backupNrestore ? repoFileName : originalFileName);
		return FALSE;
	}

	while (fgets(auxBuffer, sizeof(auxBuffer), origin) != NULL){
		fprintf_s(destiny, auxBuffer);
	}

	fclose(origin);
	fclose(destiny);
	return TRUE;
}