void compressUtil(unsigned long originalDataLen) {
	//get compress buffer bound
	int rv;
	int compressBufBound = compressBound(originalDataLen);
	compressedBuf = (unsigned char*) malloc(sizeof(unsigned char)*compressBufBound);
	unsigned long compressedDataLen = compressBufBound;
	//compress
	rv = compress2(compressedBuf, &compressedDataLen, dataBuf, originalDataLen, 6);
	if (Z_OK != rv) {
		LOGE(1, "compression error");
		free(compressedBuf);
		return;
	}
	LOGI(1, "upper bound:%d; input: %d; compressed: %d",
			compressBufBound, originalDataLen, compressedDataLen);
	//decompress and verify result
	unsigned long decompressedDataLen = S_BUF_SIZE;
	rv = uncompress(decompressedBuf, &decompressedDataLen, compressedBuf, compressedDataLen);
	if (Z_OK != rv) {
		LOGE(1, "decompression error");
		free(compressedBuf);
		return;
	}
	LOGI(1, "decompressed: %d", decompressedDataLen);
	if (0 == memcmp(dataBuf, decompressedBuf, originalDataLen)) {
		LOGI(1, "decompressed data same as original data");
	} else {
		LOGI(1, "decompressed data different from original data");
	}
	//free resource
	free(compressedBuf);
}