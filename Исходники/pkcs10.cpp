X509_REQ* UPKCS10::readPKCS10(const UString& x, const char* format)
{
   U_TRACE(1, "UPKCS10::readPKCS10(%.*S,%S)", U_STRING_TO_TRACE(x), format)

   BIO* in;
   UString tmp        = x;
   X509_REQ* _request = 0;

   if (format == 0) format = (x.isBinary() ? "DER" : "PEM");

   if (U_STREQ(format, "PEM") &&
       U_STRNCMP(x.data(), "-----BEGIN CERTIFICATE REQUEST-----"))
      {
      unsigned length = x.size();

      UString buffer(length);

      if (UBase64::decode(x.data(), length, buffer) == false) goto next;

      tmp    = buffer;
      format = "DER";
      }

next:
   in = (BIO*) U_SYSCALL(BIO_new_mem_buf, "%p,%d", U_STRING_TO_PARAM(tmp));

   _request = (X509_REQ*) (U_STREQ(format, "PEM") ? U_SYSCALL(PEM_read_bio_X509_REQ, "%p,%p,%p,%p", in, 0, 0, 0)
                                                  : U_SYSCALL(d2i_X509_REQ_bio,      "%p,%p",       in, 0));

   (void) U_SYSCALL(BIO_free, "%p", in);

   U_RETURN_POINTER(_request, X509_REQ);
}