void print_all(PageArena<char> &allocer, MemTable &mt)
{
  ObScanParam scan_param;
  read_scan_param("./test_cases/print_memtable_all.ini", "SCAN_PARAM_SECTION", allocer, scan_param);

  MemTableTransHandle handle;
  MemTableIterator iter;
  mt.start_transaction(READ_TRANSACTION, handle);
  bool reverse = false;
  mt.scan(handle, *(scan_param.get_range()), reverse, iter);
  while (OB_SUCCESS == iter.next_cell())
  {
    ObCellInfo *ci = NULL;
    iter.get_cell(&ci);
    ::print_cellinfo(ci);
  }
  mt.end_transaction(handle);
}