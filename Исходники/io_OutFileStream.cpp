bool OutFileStream::isReady(void) { return GetHandleInformation(fd(),NULL) != 0;
}