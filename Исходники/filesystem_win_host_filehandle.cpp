size_t
HostFileHandle::read(uint8_t *data,
                     size_t size,
                     size_t count)
{
   decaf_check(mHandle);
   decaf_check((mMode & File::Read) || (mMode & File::Update));
   return fread_s(data, size * count, size, count, mHandle);
}