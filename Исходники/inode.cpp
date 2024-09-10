void writeINODE(INODE * inodeP)
{
	//data.txt的区块偏移， 加上INODE节点区的偏移
	int offset = inodeP->inodeNumber * superBlockPointer->inodeSize + getInodeAreaOffset(superBlockPointer);
	if(fseek(dataFp, offset, SEEK_SET) == 0){
		int time_tmp = inodeP->aTime;
		Fwrite(&time_tmp, 4, 1, dataFp);
		//fwrite(&inodeP->aTime, 4, 1, dataFp);
		time_tmp = inodeP->cTime;
		Fwrite(&time_tmp, 4, 1, dataFp);
		//fwrite(&inodeP->cTime, 4, 1, dataFp);
		time_tmp = inodeP->mTime;
		Fwrite(&time_tmp, 4, 1, dataFp);
		//fwrite(&inodeP->mTime, 4, 1, dataFp);
		Fwrite(&inodeP->GID, 4, 1, dataFp);
		Fwrite(&inodeP->UID, 4, 1, dataFp);
		Fwrite(&inodeP->authority, 4, 1, dataFp);
		Fwrite(&inodeP->inodeNumber, 4, 1, dataFp);
		Fwrite(&inodeP->blockNumber, 4, 1, dataFp);
		Fwrite(&inodeP->length, 4, 1, dataFp);
		BLOCK block;
		block.blockNumber = inodeP->blockNumber;
		writeBlock(&block, inodeP->mem);
		//fwrite(inodeP, sizeof(INODE), 1, dataFp);
	}
	else{
		printf("文件指针偏移失败，请重新打开程序尝试，不成功则程序已崩溃……！\r\n");
		getchar();
		exit(-255);
	}
}