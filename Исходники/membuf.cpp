int MemoryBuffer::Load(const void *buf, __MEMBUF_INT__ bytes) 
// Load this object with a unique copy of the specified buffer.
// Returns true if successful or false if an error occurs.
{   
  if(!mptr) { // Ensure that this buffer has been initialized
    if(!Alloc(bytes)) return 0;
  }

  if(d_length < bytes) { // Ensure enough byte have been allocated
    if(!Realloc(bytes, 0, 0)) return 0;
  }
  else { // Reuse the current memory segment
    l_length = bytes;
  }

  // PC-lint 09/14/2005: Possible use of null pointer
  if(!mptr) return 0;

  memmove(mptr, (unsigned char *)buf, l_length);
  return 1;
}