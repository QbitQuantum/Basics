/** Compute md5 of a buffer.
  * @param data unsigned chat pointer to data buffer.
  * @param len size of buffer.
  */
void MD5Utils::md5Buffer(unsigned char *data , int len) {
    MD5_CTX context;

    memset(digest , 0 , sizeof(digest));
    MD5_Init(&context);
    MD5_Update(&context , data , len);
    MD5_Final(digest , &context);

    memset(digestStr , 0 , sizeof(digestStr));
    char digit[6];
    for (int i = 0 ; i < 16 ; i++) {
        snprintf(digit, sizeof(digit), "%.2x" , digest[i]);
        digit[2] = 0;
        StrCat(digestStr , digit);
    }
}