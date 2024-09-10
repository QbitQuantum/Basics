void NcrackOutputTable::addItemFormatted(unsigned int row, 
					  unsigned int column,
					  bool fullrow,
					  const char *fmt, ...) {
  struct NcrackOutputTableCell *cell;
  int mc = maxColLen[column];
  unsigned int res;
  va_list ap; 
  va_start(ap,fmt);
  char buf[4096];
  res = Vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  if (res > sizeof(buf))
    fatal("NcrackOutputTable only supports adding up to 4096 to a cell via %s.", __func__);

  addItem(row, column, fullrow, true, buf, res);

  if(fullrow) {
    maxColLen[column] = mc;
    cell = getCellAddy(row, column);
    cell->fullrow = fullrow;
  }
}