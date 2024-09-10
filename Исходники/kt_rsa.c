static int  
xmlSecMSCryptoRsaPkcs1Process(xmlSecTransformPtr transform, xmlSecTransformCtxPtr transformCtx) {
    xmlSecMSCryptoRsaPkcs1CtxPtr ctx;
    xmlSecBufferPtr in, out;
    xmlSecSize inSize, outSize;
    xmlSecSize keySize;
    int ret;
    HCRYPTKEY hKey = 0;
    DWORD dwInLen;
    DWORD dwBufLen;
    DWORD dwOutLen;
    BYTE * outBuf;
    BYTE * inBuf;
    int i;

    xmlSecAssert2(xmlSecTransformCheckId(transform, xmlSecMSCryptoTransformRsaPkcs1Id), -1);
    xmlSecAssert2((transform->operation == xmlSecTransformOperationEncrypt) || (transform->operation == xmlSecTransformOperationDecrypt), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecMSCryptoRsaPkcs1Size), -1);
    xmlSecAssert2(transformCtx != NULL, -1);

    ctx = xmlSecMSCryptoRsaPkcs1GetCtx(transform);
    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->data != NULL, -1);
    
    keySize = xmlSecKeyDataGetSize(ctx->data) / 8;
    xmlSecAssert2(keySize > 0, -1);
    
    in = &(transform->inBuf);
    out = &(transform->outBuf);
	
    inSize = xmlSecBufferGetSize(in);
    outSize = xmlSecBufferGetSize(out);    
    xmlSecAssert2(outSize == 0, -1);
	
    /* the encoded size is equal to the keys size so we could not
     * process more than that */
    if((transform->operation == xmlSecTransformOperationEncrypt) && (inSize >= keySize)) {
        xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    NULL,
                    XMLSEC_ERRORS_R_INVALID_SIZE,
                    "%d when expected less than %d", inSize, keySize);
        return(-1);
    } else if((transform->operation == xmlSecTransformOperationDecrypt) && (inSize != keySize)) {
        xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    NULL,
                    XMLSEC_ERRORS_R_INVALID_SIZE,
                    "%d when expected %d", inSize, keySize);
        return(-1);
    }
	
    outSize = keySize; 
    ret = xmlSecBufferSetMaxSize(out, outSize);
    if(ret < 0) {
        xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    "xmlSecBufferSetMaxSize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", outSize);
        return(-1);
    }

    if(transform->operation == xmlSecTransformOperationEncrypt) {
	BYTE ch;

	if(inSize > outSize) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
			xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
			NULL,
			XMLSEC_ERRORS_R_INVALID_SIZE,
			"inSize=%d;outSize=%d", 
			inSize, outSize);
	    return(-1);
	}

	ret = xmlSecBufferSetData(out, xmlSecBufferGetData(in), inSize);
	if(ret < 0) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
			xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
			"xmlSecBufferSetData",
			XMLSEC_ERRORS_R_XMLSEC_FAILED,
			"size=%d", inSize);
	    return(-1);
	}

        dwInLen = inSize;
        dwBufLen = outSize;
	if (0 == (hKey = xmlSecMSCryptoKeyDataGetKey(ctx->data, xmlSecKeyDataTypePublic))) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecMSCryptoKeyDataGetKey",
                        XMLSEC_ERRORS_R_CRYPTO_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return (-1);
	}
        
	outBuf = xmlSecBufferGetData(out);
	xmlSecAssert2(outBuf != NULL, -1);
	if (!CryptEncrypt(hKey, 0, TRUE, 0, outBuf, &dwInLen, dwBufLen)) {
            xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
                        NULL,
                        "CryptEncrypt",
                        XMLSEC_ERRORS_R_CRYPTO_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return (-1);
        }

	/* The output of CryptEncrypt is in little-endian format, so we have to convert to
	 * big-endian first.
	 */
	for(i = 0; i < outSize / 2; i++) {
	    ch = outBuf[i];
	    outBuf[i] = outBuf[outSize - (i + 1)];
	    outBuf[outSize - (i + 1)] = ch;
	}
    } else {
	dwOutLen = inSize;

	/* The input of CryptDecrypt is expected to be little-endian, 
	 * so we have to convert from big-endian to little endian.
	 */
	inBuf	= xmlSecBufferGetData(in);
	outBuf	= xmlSecBufferGetData(out);

	xmlSecAssert2(inBuf != 0, -1);
	xmlSecAssert2(outBuf != 0, -1);
	for (i = 0; i < inSize; i++) {
	    outBuf[i] = inBuf[inSize - (i + 1)];
	}

	if (0 == (hKey = xmlSecMSCryptoKeyDataGetDecryptKey(ctx->data))) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecMSCryptoKeyDataGetKey",
                        XMLSEC_ERRORS_R_CRYPTO_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return (-1);
	}
	if (!CryptDecrypt(hKey, 0, TRUE, 0, outBuf, &dwOutLen)) {
            xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
                        xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                        "CryptDecrypt",
                        XMLSEC_ERRORS_R_CRYPTO_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return(-1);
        }

        outSize = dwOutLen;
    }

    ret = xmlSecBufferSetSize(out, outSize);
    if(ret < 0) {
        xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    "xmlSecBufferSetSize",		    
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", outSize);
        return(-1);
    }

    ret = xmlSecBufferRemoveHead(in, inSize);
    if(ret < 0) {
        xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE, 
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    "xmlSecBufferRemoveHead",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", inSize);
        return(-1);
    }

    return(0);
}