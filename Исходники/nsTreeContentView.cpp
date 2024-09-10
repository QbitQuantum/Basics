int32_t
nsTreeContentView::EnsureSubtree(int32_t aIndex)
{
  Row* row = mRows[aIndex].get();

  nsIContent* child;
  child = nsTreeUtils::GetImmediateChild(row->mContent, nsGkAtoms::treechildren);
  if (!child || !child->IsXULElement()) {
    return 0;
  }

  AutoTArray<UniquePtr<Row>, 8> rows;
  int32_t index = 0;
  Serialize(child, aIndex, &index, rows);
  // Insert |rows| into |mRows| at position |aIndex|, by first creating empty
  // UniquePtr entries and then Move'ing |rows|'s entries into them. (Note
  // that we can't simply use InsertElementsAt with an array argument, since
  // the destination can't steal ownership from its const source argument.)
  UniquePtr<Row>* newRows = mRows.InsertElementsAt(aIndex + 1,
                                                   rows.Length());
  for (nsTArray<Row>::index_type i = 0; i < rows.Length(); i++) {
    newRows[i] = Move(rows[i]);
  }
  int32_t count = rows.Length();

  row->mSubtreeSize += count;
  UpdateSubtreeSizes(row->mParentIndex, count);

  // Update parent indexes, but skip newly added rows.
  // They already have correct values.
  UpdateParentIndexes(aIndex, count + 1, count);

  return count;
}