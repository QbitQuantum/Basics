unsigned long BloomFilter::hash2(const Key& key) {
    unsigned long hash = 0;
    for (unsigned i = 0; i < key.length(); i++) {
        hash = key.c_str()[i] + (hash << 6) + (hash << 16) - hash;
    }
    long double d_hash = (long double)hash;

    d_hash *= (0.5 * (sqrtl(5) - 1));
    d_hash = d_hash / 10.0 - floorl(d_hash / 10.0);
    d_hash *= (double)m_length;

    return (unsigned long)floorl(d_hash);
}