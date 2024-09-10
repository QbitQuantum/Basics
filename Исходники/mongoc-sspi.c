int
_mongoc_sspi_auth_sspi_client_wrap (mongoc_sspi_client_state_t *state,
                                    SEC_CHAR *data,
                                    SEC_CHAR *user,
                                    ULONG ulen,
                                    int protect)
{
   SECURITY_STATUS status;
   SecPkgContext_Sizes sizes;
   SecBuffer wrapBufs[3];
   SecBufferDesc wrapBufDesc;
   SEC_CHAR *decodedData = NULL;
   SEC_CHAR *inbuf;
   SIZE_T inbufSize;
   SEC_CHAR *outbuf;
   DWORD outbufSize;
   SEC_CHAR *plaintextMessage;
   ULONG plaintextMessageSize;

   if (state->response != NULL) {
      free (state->response);
      state->response = NULL;
   }

   if (!state->haveCtx) {
      return MONGOC_SSPI_AUTH_GSS_ERROR;
   }

   status = QueryContextAttributes (&state->ctx, SECPKG_ATTR_SIZES, &sizes);
   if (status != SEC_E_OK) {
      _mongoc_sspi_set_gsserror (status, "QueryContextAttributes");
      return MONGOC_SSPI_AUTH_GSS_ERROR;
   }

   if (user) {
      /* Length of user + 4 bytes for security layer (see below). */
      plaintextMessageSize = ulen + 4;
   } else {
      decodedData = _mongoc_sspi_base64_decode (data, &plaintextMessageSize);
      if (!decodedData) {
         return MONGOC_SSPI_AUTH_GSS_ERROR;
      }
   }

   inbufSize =
      sizes.cbSecurityTrailer + plaintextMessageSize + sizes.cbBlockSize;
   inbuf = (SEC_CHAR *) malloc (inbufSize);
   if (inbuf == NULL) {
      free (decodedData);
      return MONGOC_SSPI_AUTH_GSS_ERROR;
   }

   plaintextMessage = inbuf + sizes.cbSecurityTrailer;
   if (user) {
      /* Authenticate the provided user. Unlike pykerberos, we don't
       * need any information from "data" to do that.
       * */
      plaintextMessage[0] = 1; /* No security layer */
      plaintextMessage[1] = 0;
      plaintextMessage[2] = 0;
      plaintextMessage[3] = 0;
      memcpy_s (plaintextMessage + 4,
                inbufSize - sizes.cbSecurityTrailer - 4,
                user,
                strlen (user));
   } else {
      /* No user provided. Just rewrap data. */
      memcpy_s (plaintextMessage,
                inbufSize - sizes.cbSecurityTrailer,
                decodedData,
                plaintextMessageSize);
      free (decodedData);
   }

   wrapBufDesc.cBuffers = 3;
   wrapBufDesc.pBuffers = wrapBufs;
   wrapBufDesc.ulVersion = SECBUFFER_VERSION;

   wrapBufs[0].cbBuffer = sizes.cbSecurityTrailer;
   wrapBufs[0].BufferType = SECBUFFER_TOKEN;
   wrapBufs[0].pvBuffer = inbuf;

   wrapBufs[1].cbBuffer = (ULONG) plaintextMessageSize;
   wrapBufs[1].BufferType = SECBUFFER_DATA;
   wrapBufs[1].pvBuffer = inbuf + sizes.cbSecurityTrailer;

   wrapBufs[2].cbBuffer = sizes.cbBlockSize;
   wrapBufs[2].BufferType = SECBUFFER_PADDING;
   wrapBufs[2].pvBuffer =
      inbuf + (sizes.cbSecurityTrailer + plaintextMessageSize);

   status = EncryptMessage (
      &state->ctx, protect ? 0 : SECQOP_WRAP_NO_ENCRYPT, &wrapBufDesc, 0);
   if (status != SEC_E_OK) {
      free (inbuf);
      _mongoc_sspi_set_gsserror (status, "EncryptMessage");
      return MONGOC_SSPI_AUTH_GSS_ERROR;
   }

   outbufSize =
      wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer + wrapBufs[2].cbBuffer;
   outbuf = (SEC_CHAR *) malloc (sizeof (SEC_CHAR) * outbufSize);
   memcpy_s (outbuf, outbufSize, wrapBufs[0].pvBuffer, wrapBufs[0].cbBuffer);
   memcpy_s (outbuf + wrapBufs[0].cbBuffer,
             outbufSize - wrapBufs[0].cbBuffer,
             wrapBufs[1].pvBuffer,
             wrapBufs[1].cbBuffer);
   memcpy_s (outbuf + wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer,
             outbufSize - wrapBufs[0].cbBuffer - wrapBufs[1].cbBuffer,
             wrapBufs[2].pvBuffer,
             wrapBufs[2].cbBuffer);
   state->response = _mongoc_sspi_base64_encode (outbuf, outbufSize);
   if (!state->response) {
      status = MONGOC_SSPI_AUTH_GSS_ERROR;
   } else {
      status = MONGOC_SSPI_AUTH_GSS_COMPLETE;
   }
   free (inbuf);
   free (outbuf);
   return status;
}