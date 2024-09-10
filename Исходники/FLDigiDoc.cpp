int FLDigiDoc::verifySignatureData(const QByteArray &data, QByteArray &signResult,
                                   const QString &certfile)
{
  X509 *pCert = 0;
  int err = ReadCertificate(&pCert, certfile.latin1());
  if (!err && pCert) {
    int sigLen = SIGNATURE_LEN;
    byte buf[sigLen * sizeof(char)];
    byte buf1[sigLen * sizeof(char) * 2];
    err = verifySignature((const char *)data, data.size() * sizeof(char),
                          DIGEST_SHA1, buf, sigLen, pCert);
    signResult = encodeBase64(buf, SIGNATURE_LEN);
  }
  if (pCert) {
    X509_free(pCert);
    pCert = 0;
  }
  return err;
}