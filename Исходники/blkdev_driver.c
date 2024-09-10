block_datastr *blkdev_write_block(UID id,char *data)		
{
	int size;
	char *copy_ptr;
	block_datastr *ret;
	block_datastr *bp;

	char *temp;

	int i=0;

	ret = bp = find_freeblock();	 // get free block pointer
	printf("%x\n", ret);

	size = get_datasize(data); // get size of data
	printf("%d\n", size);

	while(size > 0){
		if(bcb.blocksleft <= 0)
		{
			printf("No have empty block");
			return NULL;
		}
		bp->next = (unsigned int)(bp->next)|(0x1);	// check block to be used
		if(size > BLOCK_SIZE)
		{
			MemCpy(bp->data, data, BLOCK_SIZE);
			bp->next = (unsigned int)(bp->next)|(unsigned int)find_freeblock();
			bp = (unsigned int)(bp->next)&0xFFFFFFFE;
		}
		else
		{
			MemCpy(bp->data, data, size);
		}
		size = size - BLOCK_SIZE;
		bcb.blocksleft--;
	}


	return ret;
}