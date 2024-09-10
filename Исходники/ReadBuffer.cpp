bool ReadBuffer::BeginsWith(ReadBuffer& other)
{
    if (length < other.length)
        return false;

    if (MEMCMP(buffer, other.length, other.buffer, other.length))
        return true;
    else
        return false;
}