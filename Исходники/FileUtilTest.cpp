ssize_t Reader::operator()(int fd, const iovec* iov, int count, off_t offset) {
  EXPECT_EQ(offset_, offset);
  return operator()(fd, iov, count);
}