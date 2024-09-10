int64_t message::svarint()
{
    uint64_t n = varint();
    return (n >> 1) ^ -static_cast<int64_t>((n & 1));
}