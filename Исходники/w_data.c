uint32_t direct_writeblock(const char *src_path, uint64_t chunkid, uint64_t *t_size)
{
	uint8_t *ptr = NULL;
	uint8_t *ibuff = NULL;
	int8_t status = 0;
	uint64_t size;
	uint64_t len;
	uint32_t read_size = 0;
	FILE *fp = NULL;
	char *p_data = NULL;

    fp = fopen(src_path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "open file(%s) failed!\n", src_path);
        return 3;
    }

    size = get_file_size(src_path);
    if (size <= 0) { // 大小为0的文件丢弃
        fprintf(stderr, "get file(%s) error!\n", src_path);
		fclose(fp);
        return 3;
    }
 
	ibuff = malloc(24);
	ptr = ibuff;

	PUT32BIT(DRWTODAT_WRITE_INFO, ptr);
	PUT32BIT(16, ptr);
	PUT64BIT(chunkid, ptr);
	PUT64BIT(size,ptr);

	if (tcptowrite(rw_sock, ibuff, 24, CSMSECTIMEOUT) != 24) {
		free(ibuff);
		fclose(fp);
		fprintf(stderr, "write data to dat error!\n");
		return 3;
	}
	free(ibuff);
	// 等待dat端的回复
	uint8_t hdr[13];
	uint8_t *ptr1 = NULL;
	uint32_t cmd1 = 0;
	uint32_t len1 = 0;
	uint32_t version1 = 0;

	ptr1 = hdr;
	if (read(rw_sock, hdr, 13) != 13) {
		fprintf(stderr, "read data from dat error\n");
	}
	GET32BIT(cmd1, ptr1);
	GET32BIT(len1, ptr1);
	GET32BIT(version1, ptr1);
	GET8BIT(status, ptr1);
int i = 0;
for(i=0; i< 13; i++) {
	fprintf(stderr, "%u-", hdr[i]);
}
fprintf(stderr, "hdr end\n");


	if (cmd1 != DATTODRW_WRITE_INFO || status != 0) {
		fprintf(stderr, "dat not ready!\n");
		return 1;
	} 

	ibuff = malloc(W_PACK_SIZE*sizeof(uint8_t));
	ptr = ibuff;
	p_data = malloc(W_PACK_SIZE*sizeof(char));
	len = 0;
  	while (len < size) {
        read_size = fread(p_data, sizeof(char), W_PACK_SIZE, fp);
	 	if (read_size < 0) {
            fprintf(stderr, "fread file(%s) error!\n", src_path);
		 	fclose(fp);
			free(ibuff);
			free(p_data);
            return 3;
        }
		memcpy(ptr, p_data, read_size);
		if (tcptowrite(rw_sock, ibuff, read_size, CSMSECTIMEOUT) != read_size) {
			fprintf(stderr, "readblock; tcpwrite error!\n");
			free(ibuff);
			free(p_data);
		 	fclose(fp);
			return 3;
		}
		if (DEBUG) {
			fprintf(stderr, "total size(%llu), read size: %llu\n",
					(unsigned long long int)size, (unsigned long long int)len);
		}
		len += read_size;
	}
	fprintf(stderr, "Write over!\n");
	
	*t_size = size;
    fclose(fp);
	free(ibuff);
	free(p_data);

	return status;
}