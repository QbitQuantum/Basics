int X509_CRL_match(const X509_CRL *a, const X509_CRL *b)
{
    return memcmp(a->sha1_hash, b->sha1_hash, 20);
}