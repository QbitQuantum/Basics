/*
*
* Uncipher 64 bits of the KDBG with 3 keys
*
* @param data data to uncipher
* @param KiWaitNever one key
* @param KiWaitAlways one key
* @param KdpDataBlockEncoded one key
* @return data data unciphered
*/
__inline uint64_t uncipherData(uint64_t Data, uint64_t KiWaitNever, uint64_t KiWaitAlways, uint64_t KdpDataBlockEncoded)
{
    Data = Data^KiWaitNever;
    Data = _rotl64(Data, KiWaitNever & 0xFF);
    Data = Data^KdpDataBlockEncoded;
    Data = _byteswap_uint64(Data);
    Data = Data^KiWaitAlways;
    return Data;
}