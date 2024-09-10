bool TOCEntry::contains(int pgno) const {
  return pgno >= startPage()
    && pgno < startPage() + sheetCount();
}