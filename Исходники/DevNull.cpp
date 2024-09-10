//!
//! Construct a null device.
//!
DevNull::DevNull()
{
    orig_ = INVALID_FD;
    clone_ = INVALID_FD;

#pragma warning(push)
#pragma warning(disable: 4996)
    null_ = _wopen(DEV_NULL, _O_RDWR);
#pragma warning(pop)
}