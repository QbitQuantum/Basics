void InputDataStream::WrapMemory(const Vector<BYTE> &stream)
{
    _data = stream.CArray();
    _dataLength = stream.Length();
    _readPtr = 0;
}