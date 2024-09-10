void setRandomData(AlignedArray& buf, Rand& rand)
{
    size_t off = 0;
    while (off < buf.size()) {
        const size_t size = std::min<size_t>(buf.size() - off, 16);
        rand.fill(buf.data() + off, size);
        off += 512;
    }
}