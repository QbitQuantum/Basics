void Watch::close() {
  if (directory != NULL) {
    CancelIoEx(*directory, *this);
    directory->close();
    Directory::dec_ref(*directory);
    directory = NULL;
  }
}