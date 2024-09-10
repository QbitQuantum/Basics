DBHandleRef DBHandle::getInstanceInMemory() {
  return getInstance("", true);
}