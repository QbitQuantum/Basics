CURLntlm Curl_input_ntlm(struct connectdata *conn,
                         bool proxy,   /* if proxy or not */
                         const char *header) /* rest of the www-authenticate:
                                                header */
{
  /* point to the correct struct with this */
  struct ntlmdata *ntlm;
#ifndef USE_WINDOWS_SSPI
  static const char type2_marker[] = { 0x02, 0x00, 0x00, 0x00 };
#endif

#ifdef USE_NSS
  if(CURLE_OK != Curl_nss_force_init(conn->data))
    return CURLNTLM_BAD;
#endif

  ntlm = proxy?&conn->proxyntlm:&conn->ntlm;

  /* skip initial whitespaces */
  while(*header && ISSPACE(*header))
    header++;

  if(checkprefix("NTLM", header)) {
    header += strlen("NTLM");

    while(*header && ISSPACE(*header))
      header++;

    if(*header) {
      /* We got a type-2 message here:

         Index   Description         Content
         0       NTLMSSP Signature   Null-terminated ASCII "NTLMSSP"
                                     (0x4e544c4d53535000)
         8       NTLM Message Type   long (0x02000000)
         12      Target Name         security buffer(*)
         20      Flags               long
         24      Challenge           8 bytes
         (32)    Context (optional)  8 bytes (two consecutive longs)
         (40)    Target Information  (optional) security buffer(*)
         32 (48) start of data block
      */
      size_t size;
      unsigned char *buffer;
      size = Curl_base64_decode(header, &buffer);
      if(!buffer)
        return CURLNTLM_BAD;

      ntlm->state = NTLMSTATE_TYPE2; /* we got a type-2 */

#ifdef USE_WINDOWS_SSPI
      ntlm->type_2 = malloc(size+1);
      if(ntlm->type_2 == NULL) {
        free(buffer);
        return CURLE_OUT_OF_MEMORY;
      }
      ntlm->n_type_2 = size;
      memcpy(ntlm->type_2, buffer, size);
#else
      ntlm->flags = 0;

      if((size < 32) ||
         (memcmp(buffer, NTLMSSP_SIGNATURE, 8) != 0) ||
         (memcmp(buffer+8, type2_marker, sizeof(type2_marker)) != 0)) {
        /* This was not a good enough type-2 message */
        free(buffer);
        return CURLNTLM_BAD;
      }

      ntlm->flags = readint_le(&buffer[20]);
      memcpy(ntlm->nonce, &buffer[24], 8);

      DEBUG_OUT({
        fprintf(stderr, "**** TYPE2 header flags=0x%08.8lx ", ntlm->flags);
        print_flags(stderr, ntlm->flags);
        fprintf(stderr, "\n                  nonce=");
        print_hex(stderr, (char *)ntlm->nonce, 8);
        fprintf(stderr, "\n****\n");
        fprintf(stderr, "**** Header %s\n ", header);
      });
#endif
      free(buffer);
    }