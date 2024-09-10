//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{
    //Patched for Safir SDK Core
    const boost::uint32_t val = *mem;
    _ReadWriteBarrier();
    return val;
}