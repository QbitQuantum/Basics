void indri::file::BulkTreeWriter::flush() {
  _flushAll();
  _write.flush();
}