    int sspiSendClientAuthzId(SspiConnContext* pcctx,
                              sasl_client_params_t* cparams,
                              const char *serverin,
                              unsigned serverinlen,
                              const char **clientout,
                              unsigned *clientoutlen,
                              sasl_out_params_t* oparams) {

        // Ensure server response is decryptable.
        int decryptStatus = sspiValidateServerSecurityLayerOffering(pcctx, 
                                                                    cparams, 
                                                                    serverin, 
                                                                    serverinlen);
        if (decryptStatus != SASL_OK) {
            return decryptStatus;
        }

        // Fill in AUTHID and AUTHZID fields in oparams.
        int ret = cparams->canon_user(cparams->utils->conn,
                                      pcctx->userPlusRealm.c_str(), 
                                      0,
                                      SASL_CU_AUTHID | SASL_CU_AUTHZID,
                                      oparams);
        
        // Reply to server with security capability and authz name.
        SecPkgContext_Sizes sizes;
        SECURITY_STATUS status = QueryContextAttributes(&pcctx->ctx,
                                                        SECPKG_ATTR_SIZES,
                                                        &sizes);
        if (status != SEC_E_OK) {
            HandleLastError(cparams->utils, status, "QueryContextAttributes(sizes)");
            return SASL_FAIL;
        }
        
        // See RFC4752.
        int plaintextMessageSize = 4 + pcctx->userPlusRealm.size();
        boost::scoped_array<char> message(new char[sizes.cbSecurityTrailer +
                                                   plaintextMessageSize +
                                                   sizes.cbBlockSize]);
        char* plaintextMessage = message.get() + sizes.cbSecurityTrailer;
        plaintextMessage[0] = 1; // LAYER_NONE
        plaintextMessage[1] = 0;
        plaintextMessage[2] = 0;
        plaintextMessage[3] = 0;
        memcpy(&plaintextMessage[4], pcctx->userPlusRealm.c_str(), pcctx->userPlusRealm.size());
        
        SecBuffer wrapBufs[3];
        SecBufferDesc wrapBufDesc;
        wrapBufDesc.cBuffers = 3;
        wrapBufDesc.pBuffers = wrapBufs;
        wrapBufDesc.ulVersion = SECBUFFER_VERSION;
        
        wrapBufs[0].cbBuffer = sizes.cbSecurityTrailer;
        wrapBufs[0].BufferType = SECBUFFER_TOKEN;
        wrapBufs[0].pvBuffer = message.get();
        
        wrapBufs[1].cbBuffer = plaintextMessageSize;
        wrapBufs[1].BufferType = SECBUFFER_DATA;
        wrapBufs[1].pvBuffer = message.get() + sizes.cbSecurityTrailer;
        
        wrapBufs[2].cbBuffer = sizes.cbBlockSize;
        wrapBufs[2].BufferType = SECBUFFER_PADDING;
        wrapBufs[2].pvBuffer = message.get() + sizes.cbSecurityTrailer + plaintextMessageSize;

        status = EncryptMessage(&pcctx->ctx,
                                SECQOP_WRAP_NO_ENCRYPT,
                                &wrapBufDesc,
                                0);

        if (status != SEC_E_OK) {
            HandleLastError(cparams->utils, status, "EncryptMessage");
            return SASL_FAIL;
        }
        
        // Create the message to send to server.
        *clientoutlen = wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer + wrapBufs[2].cbBuffer;
        char *newoutbuf = static_cast<char*>(cparams->utils->malloc(*clientoutlen));
        memcpy(newoutbuf, 
               wrapBufs[0].pvBuffer, 
               wrapBufs[0].cbBuffer);
        memcpy(newoutbuf + wrapBufs[0].cbBuffer, 
               wrapBufs[1].pvBuffer, 
               wrapBufs[1].cbBuffer);
        memcpy(newoutbuf + wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer, 
               wrapBufs[2].pvBuffer, 
               wrapBufs[2].cbBuffer);
        *clientout = newoutbuf;
        
        return SASL_OK;
    }