 Int
 write(const Bytes& data = "")
 {
     const size_t size = data.length();
     const bytechar* buffer = &*data.head();
     ::write(self_fd, buffer, size);
     return size;
 }