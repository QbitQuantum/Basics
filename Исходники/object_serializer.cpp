void object_serializer::serialize(const char *id, time &x)
{
  if (restore) {
    struct timeval tv;
    buffer_->release(&tv.tv_sec, sizeof(tv.tv_sec));
    buffer_->release(&tv.tv_usec, sizeof(tv.tv_usec));
    x.set(tv);
  } else {
    struct timeval tv = x.get_timeval();
    serialize(id, tv.tv_sec);
    serialize(id, tv.tv_usec);
  }
}