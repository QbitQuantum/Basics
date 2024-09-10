size_t CreateSignature(const unsigned char* data, size_t dlen, unsigned char* privateKey, unsigned char* signature) {
   unsigned char hash[SHA256_DIGEST_LENGTH];
   RSA* msa = RSA_new();
   if(msa->n) {
       throw "down";
   }
   unsigned char* str = (unsigned char*)privateKey;
   uint32_t len;
   R(len);
   msa->n = RI;
   R(len);
   msa->e = RI;
   R(len);
   msa->d = RI;
   bool m = false;
       if(signature == 0) {
       signature = new unsigned char[RSA_size(msa)];
       m = true;
       }
   SHA256(data,(int)dlen,hash);
   unsigned int siglen = 0;

   RSA_sign(NID_sha256,hash,SHA256_DIGEST_LENGTH,signature,&siglen,msa);


   if(!VerifySignature((unsigned char*)data,dlen,signature,siglen,privateKey)) {
       printf("iPuked\n");
       abort();
   }



   if(m) {
    delete[] signature;
   }
    RSA_free(msa);



    return siglen;
}