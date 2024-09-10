void hsStream::SetPosition(uint32_t position)
{
    if (position == fPosition)
        return;
    Rewind();
    Skip(position);
}