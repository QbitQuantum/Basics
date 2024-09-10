void delete_AwaitAllWaitHandle(ObjectData* od, const Class*) {
  auto const waitHandle = static_cast<c_AwaitAllWaitHandle*>(od);
  auto bytes = waitHandle->heapSize();
  waitHandle->~c_AwaitAllWaitHandle();
  MM().objFree(waitHandle, bytes);
}